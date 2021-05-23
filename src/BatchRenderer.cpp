#include "BatchRenderer.h"
#include <glbinding/gl/gl.h>
#include <glm/detail/qualifier.hpp>
#include <stdexcept>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace gl;

static constexpr int MAX_BUFFER_COUNT = 1024;

static unsigned int createShader(GLenum type, const char* source) {
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

void BatchRenderer::init(const char* vertexShaderSource, const char* fragmentShaderSource) {

    unsigned int vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);

    int success;
    char infoLog[512];
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(programID, 512, NULL, infoLog);
        throw std::runtime_error(std::string("Cannot link shader program!\n") + infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * MAX_BUFFER_COUNT, nullptr, GL_DYNAMIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * MAX_BUFFER_COUNT, nullptr, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texturePosition));
    glEnableVertexAttribArray(1);
}

BatchRenderer::BatchRenderer() {}

void BatchRenderer::reset() {
    vertices.clear();
    indices.clear();
}

void BatchRenderer::addModel(Vertex *modelVertices, int verticesSize, unsigned int *modelIndices, int modelIndicesSize) {
    if (vertices.size() + verticesSize > MAX_BUFFER_COUNT || indices.size() + modelIndicesSize > MAX_BUFFER_COUNT) {
        flush();
    }

    int pos = vertices.size();
    vertices.insert(vertices.end(), modelVertices, modelVertices + verticesSize);

    indices.reserve(indices.size() + modelIndicesSize);
    for (int i = 0; i < modelIndicesSize; i++) {
        indices.push_back(modelIndices[i] + pos);
    }
}

void BatchRenderer::flush() {
    if (vertices.empty()) {
        return;
    }

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(unsigned int), indices.data());

    glUseProgram(programID);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    reset();
}

void BatchRenderer::updateWindowSize(int width, int height) {
    float horizontal = static_cast<float>(width) / 100.0f;
    float vertical = static_cast<float>(height) / 100.0f;

    glm::mat4 projection = glm::ortho<float>(- horizontal, horizontal, -vertical, vertical, -1.0f, 1.0f);

    glUseProgram(programID);
    glUniformMatrix4fv(glGetUniformLocation(programID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
}
