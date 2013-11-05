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
            radius: 0.2
            x: -0.1
            y: 0.3
            effect: Effect {
                color: "red"
            }
        }
        Sphere {
            radius: 0.5
            x: 0.5
            y: -0.7
            z: 1
            effect: Effect {
                color: "red"
            }
        }
        Sphere {
            radius: 0.6
            z: -0.8
            effect: Effect {
                color: "yellow"
            }
        }
        Sphere {
            radius: 0.5
            z: 0.1
            y: -1
            effect: Effect {
                color: "green"
            }
        }
    }
    FlyModeNavigator {
        camera: viewportRoot.camera
    }
}
