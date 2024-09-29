#include "scene_colored_square.h"

#include "vertices_data.h"

SceneColoredSquare::SceneColoredSquare(Resources &res)
    : Scene(res), m_coloredSquareVao(), m_coloredSquareBuffer(GL_ARRAY_BUFFER, sizeof(colorSquareVertices), colorSquareVertices, GL_STATIC_DRAW), m_coloredSquareDraw(m_coloredSquareVao, 6)
{
    // TODO
    m_coloredSquareVao.specifyAttribute(m_coloredSquareBuffer, 0, 3, 6, 0);
    m_coloredSquareVao.specifyAttribute(m_coloredSquareBuffer, 1, 3, 6, 3);
}

void SceneColoredSquare::run(Window &w)
{
    // TODO
    m_coloredSquareVao.bind();
    m_resources.color.use();
    m_coloredSquareDraw.draw();
    m_coloredSquareVao.unbind();
}
