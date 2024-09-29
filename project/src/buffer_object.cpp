#include "buffer_object.h"
#include "utils.h"
#include "iostream"

BufferObject::BufferObject() : m_id(0), m_type(GL_ARRAY_BUFFER)
{
    // TODO
    glGenBuffers(1, &m_id);
}

BufferObject::BufferObject(GLenum type, GLsizeiptr dataSize, const void *data, GLenum usage)
    : BufferObject()
{
    // TODO
    this->m_type = type;
    this->bind();
    this->allocate(m_type, dataSize, data, usage);
    glBufferData(m_type, dataSize, data, usage);
}

BufferObject::~BufferObject()
{
    // TODO
    glDeleteBuffers(1, &m_id);
}

void BufferObject::bind()
{
    // TODO
    glBindBuffer(m_type, m_id);
}

void BufferObject::allocate(GLenum type, GLsizeiptr dataSize, const void *data, GLenum usage)
{
    // TODO
    CHECK_GL_ERROR;
    this->m_type = type;
    bind();
    CHECK_GL_ERROR;

    glBufferData(m_type, dataSize, data, usage);
}

void BufferObject::update(GLsizeiptr dataSize, const void *data)
{
    // TODO
    this->bind();
    glBufferSubData(m_type, 0, dataSize, data);
}

void *BufferObject::mapBuffer()
{
    // TODO
    this->bind();
    void *result = glMapBuffer(m_type, GL_READ_WRITE);
    return result;
}

void BufferObject::unmapBuffer()
{
    // TODO
    bind();
    glUnmapBuffer(m_type);
}