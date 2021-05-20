#pragma once

#include "Vertex.h"
#include <vector>

class BatchRenderer {
    private:
        unsigned int VAO, VBO, EBO;
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

    public:
        BatchRenderer();
        void reset();
        void addModel(Vertex* modelVertices, int verticesSize, unsigned int* modelIndices, int modelIndicesSize);
        void flush();
};
