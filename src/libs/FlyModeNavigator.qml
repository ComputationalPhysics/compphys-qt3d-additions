import QtQuick 2.0
import Qt3D 2.0
import CompPhys.FlyModeNavigator 1.0

Item {
    id: navigatorRoot
    signal pressed(var mouse)
    signal released(var mouse)
    property bool activateOnPressed: true
    property real mouseSensitivity: 0.03
    property real moveSpeed: 3.0
    property real hyperSpeedFactor: 4.0
    property real moveAcceleration: 0.1
    property bool _hyperSpeed: false
    property real _realMoveSpeed: moveSpeed * (_hyperSpeed ? 4.0 : 1.0)
    property bool _hasReportedMissingCamera: false
    property bool _ignoreMouseMoverMove: false
    property bool _firstMove: true
    property bool _secondMove: false
    property Camera camera: null
    anchors.fill: parent

    function _printMissingCameraMessage() {
        if(!_hasReportedMissingCamera) {
            console.log("Navigator's camera property is missing. Please set the camera before interacting with the navigator.");
        }
        _hasReportedMissingCamera = true;
    }

    function activate() {
        navigatorRoot.forceActiveFocus()
        _firstMove = true;
        _ignoreMouseMoverMove = true;
        mouseMover.move(navigatorRoot.width / 2, navigatorRoot.height / 2);
        mouseMover.showCursor = false
        _ignoreMouseMoverMove = false;
    }

    function deactivate() {
        navigatorRoot.focus = false
        mouseMover.showCursor = true
    }

    MouseMover {
        id: mouseMover
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: navigatorRoot.activeFocus
        function mouseMoved(mouse) {
            if(!navigatorRoot.activeFocus) {
                return;
            }

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
            if(activateOnPressed) {
                navigatorRoot.activate()
            }
            navigatorRoot.pressed(mouse)
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
            deactivate()
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
        property real lastTime: 0
        running: true
        repeat: true
        interval: 16

        onTriggered: {
            var currentTime = Date.now();
            var timeDifference = currentTime-lastTime;
            timeDifference /= 1000.0;
            lastTime = currentTime;
            if(timeDifference > 1.0) {
                return;
            }

            if(!camera) {
                _printMissingCameraMessage();
                return;
            }

            var forwardVector = camera.center.minus(camera.eye);
            forwardVector = forwardVector.normalized();
            var upVector = camera.upVector
            upVector = upVector.normalized();
            var a = forwardVector;
            var b = upVector;
            var rightVector = Qt.vector3d(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); // cross product, a x b
            rightVector = rightVector.normalized();
            var translation = Qt.vector3d(0,0,0);

            var speed = moveSpeed;
            if(_hyperSpeed) {
                speed *= hyperSpeedFactor;
            }

            // Decide what to do based on velocity
            if(forward) {
                forwardSpeed = speed*timeDifference;
            } else if(backward) {
                forwardSpeed = -speed*timeDifference;
            } else {
                forwardSpeed = 0;
            }

            if(right) {
                rightSpeed = speed*timeDifference;
            } else if(left) {
                rightSpeed = -speed*timeDifference;
            } else {
                rightSpeed = 0;
            }

            translation = translation.plus(forwardVector.times(forwardSpeed))
            translation = translation.plus(rightVector.times(rightSpeed))

            camera.center = camera.center.plus(translation)
            camera.eye = camera.eye.plus(translation)
        }
    }
}
