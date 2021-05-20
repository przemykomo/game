#include "BatchRenderer.h"
#include <glbinding/gl/gl.h>

using namespace gl;

BatchRenderer::BatchRenderer() {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 1000, nullptr, GL_DYNAMIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 6000, nullptr, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texturePosition));
    glEnableVertexAttribArray(1);
}

void BatchRenderer::reset() {
    vertices.clear();
    indices.clear();
}

void BatchRenderer::addModel(Vertex *modelVertices, int verticesSize, unsigned int *modelIndices, int modelIndicesSize) {
    int pos = vertices.size();
    vertices.insert(vertices.end(), modelVertices, modelVertices + verticesSize);

    for (int i = 0; i < modelIndicesSize; i++) {
        indices.push_back(modelIndices[i] + pos);
    }

    //TODO: flush if needed
}

void BatchRenderer::flush() {
    if (vertices.empty()) {
        return;
    }

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(unsigned int), indices.data());

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
