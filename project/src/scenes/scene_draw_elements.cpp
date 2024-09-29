#include "scene_draw_elements.h"

#include "vertices_data.h"

SceneDrawElements::SceneDrawElements(Resources &res)
    : Scene(res), m_coloredSquareReduceVao(), m_coloredSquareReduceDraw(m_coloredSquareReduceVao, 6)
{
    // TODO
    m_coloredSquareReduceVao.specifyAttribute(m_resources.coloredSquareReduceBuffer, 0, 3, 6, 0);
    m_coloredSquareReduceVao.specifyAttribute(m_resources.coloredSquareReduceBuffer, 1, 3, 6, 3);
}

void SceneDrawElements::run(Window &w)
{
    // TODO
    m_coloredSquareReduceVao.bind();
    m_resources.coloredSquareReduceBuffer.bind();
    m_resources.coloredSquareReduceIndicesBuffer.bind();

    m_resources.color.use();
    m_coloredSquareReduceDraw.draw();
    m_coloredSquareReduceVao.unbind();
}
