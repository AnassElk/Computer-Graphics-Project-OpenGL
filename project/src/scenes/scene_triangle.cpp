#include "scene_triangle.h"

#include "vertices_data.h"

SceneTriangle::SceneTriangle(Resources &res)
    : Scene(res), m_triangleVao(), m_triangleBuffer(GL_ARRAY_BUFFER, sizeof(triVertices), triVertices, GL_STATIC_DRAW),
      m_triangleDraw(m_triangleVao, 3)
{
    // TODO
    m_triangleVao.specifyAttribute(m_triangleBuffer, 0, 2, 0, 0);
}

void SceneTriangle::run(Window &w)
{
    m_triangleVao.bind();
    m_resources.basic.use();
    m_triangleDraw.draw();
    m_triangleVao.unbind();
}