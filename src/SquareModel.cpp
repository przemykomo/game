#include "SquareModel.h"

SquareModel::SquareModel(TextureCoords textureCoords) :
    vertices{
        Vertex{0.5f, 0.5f, 0.0f, textureCoords.right, textureCoords.top},
        Vertex{0.5f, -0.5f, 0.0f, textureCoords.right, textureCoords.bottom},
        Vertex{-0.5f, -0.5f, 0.0f, textureCoords.left, textureCoords.bottom},
        Vertex{-0.5f, 0.5f, 0.0f, textureCoords.left, textureCoords.top}
    }, indices{
        0, 1, 3,
        1, 2, 3
    } {}
