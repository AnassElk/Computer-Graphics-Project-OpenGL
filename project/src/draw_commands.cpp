#include "draw_commands.h"

DrawArraysCommand::DrawArraysCommand(VertexArrayObject &vao, GLsizei count)
    : m_vao(vao), m_count(count)
{
    // TODO
}

void DrawArraysCommand::draw()
{
    // TODO
    m_vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, m_count);
}

void DrawArraysCommand::setCount(GLsizei count)
{
    // TODO
    m_count = count;
}

DrawElementsCommand::DrawElementsCommand(VertexArrayObject &vao, GLsizei count, GLenum type)
    : m_vao(vao), m_count(count)
{
    // TODO
    m_type = type;
}

void DrawElementsCommand::draw()
{
    // TODO
    m_vao.bind();
    glDrawElements(GL_TRIANGLES, m_count, m_type, 0);
}

void DrawElementsCommand::setCount(GLsizei count)
{
    // TODO
    m_count = count;
}