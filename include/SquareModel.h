#pragma once

#include "TextureAtlas.h"
#include "Vertex.h"
#include "BatchRenderer.h"
#include <string>

class SquareModel {
    public:
        Vertex vertices[4];
        unsigned int indices[6];
        SquareModel(TextureCoords textureCoords);
};
