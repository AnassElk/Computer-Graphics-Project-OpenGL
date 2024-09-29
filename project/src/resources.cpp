#include "resources.h"

#include "utils.h"

#include "shader_object.h"

#include "vertices_data.h"

Resources::Resources()
    : coloredSquareReduceBuffer(GL_ARRAY_BUFFER, sizeof(colorSquareVerticesReduced), colorSquareVerticesReduced, GL_STATIC_DRAW),
      coloredSquareReduceIndicesBuffer(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW),
      coloredTriangleBuffer(GL_ARRAY_BUFFER, sizeof(colorTriVertices), colorTriVertices, GL_STATIC_DRAW)
{
    // TODO
    initShaderProgram(basic, "./shaders/basic.vs.glsl", "./shaders/basic.fs.glsl");

    initShaderProgram(color, "./shaders/color.vs.glsl", "./shaders/color.fs.glsl");

    initShaderProgram(transformColorAttrib, "./shaders/transform.vs.glsl", "./shaders/transform.fs.glsl");
    mvpLocationTransformColorAttrib = transformColorAttrib.getUniformLoc("mvp");

    initShaderProgram(transformSolidColor, "./shaders/model.vs.glsl", "./shaders/model.fs.glsl");
    mvpLocationTransformSolidColor = transformSolidColor.getUniformLoc("mvp");
    colorLocationTransformSolidColor = transformSolidColor.getUniformLoc("uniformColor");
}

void Resources::initShaderProgram(ShaderProgram &program, const char *vertexSrcPath, const char *fragmentSrcPath)
{
    // TODO
    std::string vertexSrcData = readFile(vertexSrcPath);
    std::string fragmentSrcData = readFile(fragmentSrcPath);

    ShaderObject vertices(GL_VERTEX_SHADER, vertexSrcData.c_str());
    ShaderObject fragments(GL_FRAGMENT_SHADER, fragmentSrcData.c_str());
    program.attachShaderObject(vertices);
    program.attachShaderObject(fragments);

    program.link();
}