#include "scene_square.h"

#include "vertices_data.h"

SceneSquare::SceneSquare(Resources &res)
    : Scene(res), m_squareVao(), m_squareBuffer(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW),
      m_squareDraw(m_squareVao, 6)
{
    // TODO
    m_squareVao.specifyAttribute(m_squareBuffer, 0, 2, 0, 0);
}

void SceneSquare::run(Window &w)
{
    // TODO
    m_squareVao.bind();
    m_squareBuffer.bind();
    m_resources.basic.use();
    m_squareDraw.draw();
    m_squareVao.unbind();
}