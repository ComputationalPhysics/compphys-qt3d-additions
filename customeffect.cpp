#include "customeffect.h"

#include <QOpenGLShaderProgram>

CustomEffect::CustomEffect() :
    QGLShaderProgramEffect()
{
}

bool CustomEffect::beforeLink() {
    QByteArray geometryString =
            "#version 330 core\n"
            "\n"
            "layout( points ) in;\n"
            "layout( triangle_strip, max_vertices = 4 ) out;\n"
            "uniform mat4 qt_ProjectionMatrix;"
            "out vec2 texCoord;"
            "\n"
            "void main(void) {\n"
            "       float scale = 0.1;"
            "       vec4 pos = gl_in[0].gl_Position;"
            "       gl_Position = pos + qt_ProjectionMatrix*vec4(-scale, -scale, 0.0, 0.0);\n"
            "       texCoord = vec2(0.0, 0.0);"
            "       EmitVertex();\n"
            "       gl_Position = pos + qt_ProjectionMatrix*vec4(-scale, scale, 0.0, 0.0);\n"
            "       texCoord = vec2(0.0, 1.0);"
            "       EmitVertex();\n"
            "       gl_Position = pos + qt_ProjectionMatrix*vec4(scale, -scale, 0.0, 0.0);\n"
            "       texCoord = vec2(1.0, 0.0);"
            "       EmitVertex();\n"
            "       gl_Position = pos + qt_ProjectionMatrix*vec4(scale, scale, 0.0, 0.0);\n"
            "       texCoord = vec2(1.0, 1.0);"
            "       EmitVertex();\n"
            "    EndPrimitive();\n"
            "}\n";
    if(!program()->addShaderFromSourceCode(QOpenGLShader::Geometry,
                                       geometryString)) {
        qCritical() << "Could not compile geometry shader! Log: \n"
                    << program()->log();
    }
    return true;
}