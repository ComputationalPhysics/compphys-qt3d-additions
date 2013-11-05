import QtQuick 2.0
import Qt3D 2.0
import FlyModeNavigator 1.0

Item {
    id: navigatorRoot
    signal pressed(var mouse)
    signal released(var mouse)
    property real mouseSensitivity: 0.03
    property real moveSpeed: 0.03
    property real moveAcceleration: 0.1
    property bool _hyperSpeed: false
    property real _realMoveSpeed: moveSpeed * (_hyperSpeed ? 4.0 : 1.0)
    property bool _hasReportedMissingCamera: false
    property Camera camera: null
    anchors.fill: parent

    function _printMissingCameraMessage() {
        if(!_hasReportedMissingCamera) {
            console.log("Navigator's camera property is missing. Please set the camera before interacting with the navigator.");
        }
        _hasReportedMissingCamera = true;
    }

    MouseMover {
        id: mouseMover
    }

    MouseArea {
        id: mouseArea
        property bool _ignoreMouseMoverMove: false
        property bool _firstMove: true
        property bool _secondMove: false
        anchors.fill: parent
        hoverEnabled: navigatorRoot.activeFocus
        function mouseMoved(mouse) {
            if(_ignoreMouseMoverMove) {
                return;
            }
            if(!camera) {
                _printMissingCameraMessage();

                return;
            }
            if(_firstMove) {
                _firstMove = false
                _secondMove = true
                return
            }
            if(_secondMove) {
                _secondMove = false
                return
            }
            var mouseDeltaX = mouse.x - navigatorRoot.width / 2;
            var mouseDeltaY = mouse.y - navigatorRoot.height / 2;
            mouseDeltaX *= mouseSensitivity;
            mouseDeltaY *= mouseSensitivity;
            camera.tiltPanRollEye(-mouseDeltaY, -mouseDeltaX, 0);
            _ignoreMouseMoverMove = true;
            mouseMover.move(navigatorRoot.width / 2, navigatorRoot.height / 2);
            _ignoreMouseMoverMove = false;
        }
        onMouseXChanged: {
            mouseMoved(mouse)
        }
        onMouseYChanged: {
            mouseMoved(mouse)
        }
        onPressed: {
            navigatorRoot.forceActiveFocus()
            navigatorRoot.pressed(mouse)
            _firstMove = true;
            _ignoreMouseMoverMove = true;
            mouseMover.move(navigatorRoot.width / 2, navigatorRoot.height / 2);
            mouseMover.showCursor = false
            _ignoreMouseMoverMove = false;
//            hoverEnabled = true
        }
        onReleased: {
            navigatorRoot.released(mouse)
        }
    }
    Keys.onPressed: {
        if(event.modifiers & Qt.ShiftModifier) {
            _hyperSpeed = true
        } else {
            _hyperSpeed = false
        }

        if(event.key === Qt.Key_Escape) {
            navigatorRoot.focus = false
            mouseMover.showCursor = true
        }

        if(!event.isAutoRepeat) {
            if(event.key === Qt.Key_W) {
                moveTimer.forward = true
                event.accepted = true
            }
            if(event.key === Qt.Key_S) {
                moveTimer.backward = true
            }
            if(event.key === Qt.Key_A) {
                moveTimer.left = true
            }
            if(event.key === Qt.Key_D) {
                moveTimer.right = true
            }
        }
    }
    Keys.onReleased: {
        if(!event.isAutoRepeat) {
            if(event.key === Qt.Key_W) {
                moveTimer.forward = false
                event.accepted = true
            }
            if(event.key === Qt.Key_S) {
                moveTimer.backward = false
            }
            if(event.key === Qt.Key_A) {
                moveTimer.left = false
            }
            if(event.key === Qt.Key_D) {
                moveTimer.right = false
            }
        }
    }

    Timer {
        id: moveTimer
        property bool forward: false
        property bool backward: false
        property bool left: false
        property bool right: false
        property real forwardSpeed: 0.0
        property real rightSpeed: 0.0
        running: true
        repeat: true
        interval: 16

        onTriggered: {
            if(!camera) {
                _printMissingCameraMessage();
                return;
            }

            var forwardVector = camera.center.minus(camera.eye);
            var upVector = camera.upVector
            var a = forwardVector;
            var b = upVector;
            var rightVector = Qt.vector3d(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); // cross product, a x b
            var translation = Qt.vector3d(0,0,0);

            // Set up speeds
            var acceleration = moveAcceleration * interval / 1000;
            var deceleration = moveAcceleration * interval / 1000 * 2;

            // Decide what to do based on velocity
            if(forward) {
                forwardSpeed += acceleration;
            } else if(backward) {
                forwardSpeed -= acceleration;
            } else {
                if(forwardSpeed > 0) {
                    forwardSpeed = Math.max(forwardSpeed - deceleration, 0);
                } else {
                    forwardSpeed = Math.min(forwardSpeed + deceleration, 0);
                }
            }
            if(right) {
                rightSpeed += acceleration
            } else if(left) {
                rightSpeed -= acceleration
            } else {
                if(rightSpeed > 0) {
                    rightSpeed = Math.max(rightSpeed - deceleration, 0);
                } else {
                    rightSpeed = Math.min(rightSpeed + deceleration, 0);
                }
            }

            // Clamp the velocity
            forwardSpeed = Math.min(forwardSpeed, _realMoveSpeed)
            forwardSpeed = Math.max(forwardSpeed, -_realMoveSpeed)
            rightSpeed = Math.min(rightSpeed, _realMoveSpeed / 2)
            rightSpeed = Math.max(rightSpeed, -_realMoveSpeed / 2)

            translation = translation.plus(forwardVector.times(forwardSpeed))
            translation = translation.plus(rightVector.times(rightSpeed))

            camera.center = camera.center.plus(translation)
            camera.eye = camera.eye.plus(translation)
        }
    }
}
