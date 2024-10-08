#include "scene_shared_vao.h"

#include "vertices_data.h"

SceneSharedVao::SceneSharedVao(Resources &m_resources)
    : Scene(m_resources), m_sharedVao(), m_coloredTriangleSharedDraw(m_sharedVao, 3), m_coloredSquareSharedDraw(m_sharedVao, 6)
{
    // TODO
}

void SceneSharedVao::run(Window &w)
{
    // Exceptionnellement, cette méthode n'est pas utilisée
}

void SceneSharedVao::runTriangle()
{
    // TODO
    m_resources.color.use();
    m_sharedVao.bind();
    m_resources.coloredTriangleBuffer.bind();

    m_sharedVao.specifyAttribute(m_resources.coloredTriangleBuffer, 0, 3, 6, 0);
    m_sharedVao.specifyAttribute(m_resources.coloredTriangleBuffer, 1, 3, 6, 3);
    m_coloredTriangleSharedDraw.draw();

    m_sharedVao.unbind();
}

void SceneSharedVao::runSquare()
{
    // TODO
    m_resources.color.use();
    m_sharedVao.bind();
    m_resources.coloredSquareReduceBuffer.bind();
    m_resources.coloredSquareReduceIndicesBuffer.bind();

    m_sharedVao.specifyAttribute(m_resources.coloredSquareReduceBuffer, 0, 3, 6, 0);
    m_sharedVao.specifyAttribute(m_resources.coloredSquareReduceBuffer, 1, 3, 6, 3);
    m_coloredSquareSharedDraw.draw();

    m_sharedVao.unbind();
}