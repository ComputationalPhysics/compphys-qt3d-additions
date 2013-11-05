import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import FlyModeNavigator 1.0

Rectangle {
    width: 1280
    height: 800
    color: "black"
    Viewport {
        id: viewportRoot
        anchors.fill: parent
        navigation: false
        Sphere {
            effect: Effect {
                color: "red"
            }
        }
        Sphere {
            x: 1
            y: 1
            effect: Effect {
                color: "red"
            }
        }
        Sphere {
            z: 1
            effect: Effect {
                color: "red"
            }
        }
        FlyModeNavigator {
            focus: true
            camera: viewportRoot.camera
        }
    }
    MouseMover {

    }
}
