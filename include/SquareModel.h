#pragma once

#include "TextureAtlas.h"
#include <string>

class SquareModel {
    private:
        unsigned int VBO, EBO;

    public:
        SquareModel(const TextureAtlas& textureAtlas, const std::string& texture);
        void bind();
        void draw();
};
