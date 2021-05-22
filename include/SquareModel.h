#pragma once

#include "TextureAtlas.h"
#include "Vertex.h"

class SquareModel {
    public:
        Vertex vertices[4];
        unsigned int indices[6];
        SquareModel(TextureCoords textureCoords);
};
