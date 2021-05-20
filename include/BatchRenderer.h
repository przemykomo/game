#pragma once

#include "Vertex.h"
#include <vector>

class BatchRenderer {
    private:
        unsigned int programID, VAO, VBO, EBO;
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

    public:
        BatchRenderer(const char* vertexShaderSource, const char* fragmentShaderSource);
        void reset();
        void addModel(Vertex* modelVertices, int verticesSize, unsigned int* modelIndices, int modelIndicesSize);
        void flush();
};
