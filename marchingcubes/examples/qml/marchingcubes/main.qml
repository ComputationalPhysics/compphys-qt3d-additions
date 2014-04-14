import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import CompPhys.MarchingCubes 1.0
import CompPhys.MarchingCubesDemo 1.0

Viewport  {
    id: rootViewport

    property real fps: 1
    property real lastDraw: 0

    width: 1280
    height: 720

    fillColor: "black"
    blending: true
    fovzoom: false

    Component.onCompleted: {
        forceActiveFocus()
    }

    light: Light {
        ambientColor: Qt.rgba(1,1,1,1)
        position.x: myCamera.eye.x
        position.y: myCamera.eye.y
        position.z: myCamera.eye.z
        linearAttenuation: 0.02
    }

    camera: Camera {
        id: myCamera
        eye: Qt.vector3d(20,20,20)
        nearPlane: 5
        farPlane: 5000
    }

    
    IsoSurface {
        id: isoSurface
        effect: Effect {
            color: "blue"
        }
    }

    Text {
        color: "white"
        text: "FPS: " + frameRate.fps.toFixed(2)
    }

    Timer {
        running: true
        repeat: true
        interval: 1
        onTriggered: {
            myCamera.tiltPanRollCenter(0,0.01,0)
        }
    }
}
