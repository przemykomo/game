#include "ShaderProgram.h"
#include <stdexcept>
#include <glbinding/gl/gl.h>

using namespace gl;

unsigned int createShader(GLenum type, const char* source) {
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        throw std::runtime_error(std::string("Cannot compile shader!\n") + infoLog);
    }

    return shader;
}

ShaderProgram::ShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource) {
    unsigned int vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    glID = glCreateProgram();
    glAttachShader(glID, vertexShader);
    glAttachShader(glID, fragmentShader);
    glLinkProgram(glID);

    int success;
    char infoLog[512];
    glGetProgramiv(glID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(glID, 512, NULL, infoLog);
        throw std::runtime_error(std::string("Cannot link shader program!\n") + infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

ShaderProgram::~ShaderProgram() {
    //glDeleteProgram(glID); causes segfault on program exit
}

void ShaderProgram::bind() {
    glUseProgram(glID);
}
