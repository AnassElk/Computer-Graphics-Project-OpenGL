#include "shader_object.h"

#include <iostream>

ShaderObject::ShaderObject(GLenum type, const char *code)
{
    // TODO
    m_id = glCreateShader(type);
    glShaderSource(m_id, 1, &code, nullptr);
    glCompileShader(m_id);
    checkCompilingError();
}

ShaderObject::~ShaderObject()
{
    // TODO
    if (m_id != 0)
    {
        glDeleteShader(m_id);
    }
}

GLuint ShaderObject::id()
{
    // TODO
    return m_id;
}

void ShaderObject::checkCompilingError()
{
    GLint success;
    GLchar infoLog[1024];

    glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(m_id, 1024, nullptr, infoLog);
        glDeleteShader(m_id);
        std::cout << "Shader compile error: " << infoLog << std::endl;
    }
}