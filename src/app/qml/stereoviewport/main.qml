import Qt3D 2.0
import Qt3D.Shapes 2.0
import QtQuick 2.0
import StereoViewport 1.0

Rectangle {
    id: rectRoot
    width: 1280
    height: 800
    StereoViewport {
        id: viewportRoot
        fillColor: "black"
        anchors.fill: parent
        stereoType: StereoViewport.RightLeft

        light: Light {
            position: Qt.vector3d(2.0, 1.0, 3.0)
        }

        camera: Camera {
            eyeSeparation: 0.5
        }

        Cube {
            effect: Effect {
                color: "yellow"
            }
        }

        Cube {
            x: 1.5
            effect: Effect {
                color: "yellow"
            }
        }

        Cube {
            y: 1.5
            effect: Effect {
                color: "yellow"
            }
        }

        Cube {
            z: 1.5
            effect: Effect {
                color: "yellow"
            }
        }

        Cube {
            x: -4
            effect: Effect {
                color: "yellow"
            }
        }

        Cube {
            x: -1.5
            effect: Effect {
                color: "yellow"
            }
        }

        Cube {
            y: -1.5
            effect: Effect {
                color: "yellow"
            }
        }

        Cube {
            z: -1.5
            effect: Effect {
                color: "yellow"
            }
        }
    }
}
