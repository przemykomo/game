#pragma once

#include "Vertex.h"
#include <vector>

class BatchRenderer {
    private:
        unsigned int programID, VAO, VBO, EBO;
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        friend class Game;
        void init(const char* vertexShaderSource, const char* fragmentShaderSource);
    public:
        BatchRenderer();
        void reset();
        void addModel(Vertex* modelVertices, int verticesSize, unsigned int* modelIndices, int modelIndicesSize);
        void flush();
};
