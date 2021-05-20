#include "SquareModel.h"
#include "TextureAtlas.h"
#include <glbinding/gl/gl.h>

using namespace gl;

SquareModel::SquareModel(const TextureAtlas& textureAtlas, const std::string& texture) {
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    TextureCoords textureCoords = textureAtlas.getTextureCoords(texture);

    float vertices[] = {
        0.5f,  0.5f, 0.0f, textureCoords.right, textureCoords.top,  // top right
        0.5f, -0.5f, 0.0f, textureCoords.right, textureCoords.bottom, // bottom right
        -0.5f, -0.5f, 0.0f, textureCoords.left, textureCoords.bottom,  // bottom left
        -0.5f,  0.5f, 0.0f, textureCoords.left, textureCoords.top   // top left 
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void SquareModel::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

void SquareModel::draw() {
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
