/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt3D examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import Dragly 1.0

Viewport  {
    id: rootViewport

    fillColor: "black"
    blending: true
    fovzoom: false

    light: Light {
        ambientColor: Qt.rgba(1,1,1,1)
        position.x: myCamera.eye.normalized().x * 70
        position.y: myCamera.eye.normalized().y * 70
        position.z: myCamera.eye.normalized().z * 70
        quadraticAttenuation: 0.0001
    }

    camera: Camera {
        id: myCamera
        eye: Qt.vector3d(175,175,45)
        nearPlane: 5
        farPlane: 5000
    }

    MultiBillboard {
        id: multiSphere
//        cullFaces: Item3D.CullBackFaces
//        sortPoints: Item3D.BackToFront
        effect: Effect {
            texture: "particle.png"
            blending: true
            useLighting: true
        }
    }

    Text {
        color: "white"
        text: "FPS: " + multiSphere.fps.toFixed(2)
    }

    Timer {
        running: true
        repeat: true
        interval: 1
        onTriggered: {
            camera.tiltPanRollCenter(0,0.01,0)
        }
    }
}
