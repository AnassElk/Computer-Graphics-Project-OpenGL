#include "scene_multiple_vbos.h"

#include "vertices_data.h"
#include <ostream>
#include <iostream>
SceneMultipleVbos::SceneMultipleVbos(Resources &res)
    : Scene(res), m_positionX(0.0f), m_positionY(0.0f), m_deltaX(0.019f), m_deltaY(0.0128f), m_onlyColorTriVertices{1.0f, 0.0f, 0.0f,
                                                                                                                    1.0f, 0.0f, 0.0f,
                                                                                                                    1.0f, 0.0f, 0.0f},
      m_coloredTriangleMultipleVbosVao(),
      m_coloredTriangleColorBuffer(GL_ARRAY_BUFFER, sizeof(colorTriVertices), m_onlyColorTriVertices, GL_STATIC_DRAW),
      m_coloredTrianglePositionBuffer(GL_ARRAY_BUFFER, sizeof(colorTriVertices), colorTriVertices, GL_STATIC_DRAW),
      m_coloredTriangleMultipleVbosDraw(m_coloredTriangleMultipleVbosVao, 3)
{
    // TODO
    m_coloredTriangleMultipleVbosVao.specifyAttribute(m_coloredTrianglePositionBuffer, 0, 3, 6, 0);
    m_coloredTriangleMultipleVbosVao.specifyAttribute(m_coloredTriangleColorBuffer, 1, 3, 3, 0);
}

void SceneMultipleVbos::run(Window &w)
{
    changeRGB(&m_onlyColorTriVertices[0]);
    changeRGB(&m_onlyColorTriVertices[3]);
    changeRGB(&m_onlyColorTriVertices[6]);
    // TODO mise a jour de la couleur
    m_coloredTriangleColorBuffer.bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(m_onlyColorTriVertices), m_onlyColorTriVertices);

    // TODO mise a jour de la position
    m_coloredTrianglePositionBuffer.bind();
    GLfloat *posPtr = (GLfloat *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    if (posPtr != nullptr)
    {
        // Modify the vertex positions directly in the mapped buffer
        changePos(posPtr, m_positionX, m_positionY, m_deltaX, m_deltaY);

        glUnmapBuffer(GL_ARRAY_BUFFER);
    }
    else
    {
        // Handle error if buffer mapping fails
        std::cerr << "Error: Failed to map buffer for position update." << std::endl;
    }
    // TODO dessin
    m_coloredTriangleMultipleVbosVao.bind();
    m_resources.color.use();
    m_coloredTriangleMultipleVbosDraw.draw();

    m_coloredTriangleMultipleVbosVao.unbind();
}

void SceneMultipleVbos::changeRGB(GLfloat *color)
{
    unsigned char r = color[0] * 255;
    unsigned char g = color[1] * 255;
    unsigned char b = color[2] * 255;

    if (r > 0 && b == 0)
    {
        r--;
        g++;
    }
    if (g > 0 && r == 0)
    {
        g--;
        b++;
    }
    if (b > 0 && g == 0)
    {
        r++;
        b--;
    }
    color[0] = r / 255.0f;
    color[1] = g / 255.0f;
    color[2] = b / 255.0f;
}

void SceneMultipleVbos::changePos(GLfloat *pos, float &cx, float &cy, float &dx, float &dy)
{
    if ((cx < -1 && dx < 0) || (cx > 1 && dx > 0))
        dx = -dx;
    pos[0] += dx;
    pos[6] += dx;
    pos[12] += dx;
    cx += dx;
    if ((cy < -1 && dy < 0) || (cy > 1 && dy > 0))
        dy = -dy;
    pos[1] += dy;
    pos[7] += dy;
    pos[13] += dy;
    cy += dy;
}