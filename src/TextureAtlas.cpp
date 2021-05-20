#include "TextureAtlas.h"
#include "stb_image.h"

#include <cmath>
#include <cstring>
#include <iostream>
#include <memory>
#include <stdexcept>

#include <glbinding/gl/enum.h>
#include <glbinding/gl/functions.h>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_int2.hpp>

using namespace gl;

TextureAtlas::TextureAtlas() noexcept :
    glTextureID(0), atlasWidth(-1), atlasHeight(-1),
    stitchedTextureMap(), fileNames() {}

TextureAtlas::~TextureAtlas() {
    //glDeleteTextures(1, &glTextureID); causes segfault, I guess because it's called after destroying the window?
}

void TextureAtlas::addTexture(const std::string &fileName) {
    fileNames.insert(fileName);
}

void TextureAtlas::stitch() {
    stbi_set_flip_vertically_on_load(true);

    atlasHeight = atlasWidth = std::ceil(std::sqrt(fileNames.size())) * 16;

    std::unique_ptr<unsigned char[]> atlasData(new unsigned char[atlasHeight * atlasWidth * 4]);

    glm::ivec2 textureBegin(0, 0);
    for (const std::string& fileName : fileNames) {
        int x, y, comp;
        unsigned char* data = stbi_load(fileName.c_str(), &x, &y, &comp, STBI_rgb_alpha);
        if (data == nullptr || x != 16 || y != 16) {
            throw std::runtime_error(fileName + " cannot be read!");
        }

        for (int i = 0; i < 16; i++) {
            std::memcpy(atlasData.get() + ((textureBegin.y + i) * atlasWidth + textureBegin.x) * 4, data + i * 16 * 4, 16 * 4);
        }

        stitchedTextureMap[fileName] = glm::vec2(textureBegin.x / (float)atlasWidth, textureBegin.y / (float)atlasHeight);

        textureBegin.x += 16;
        if (textureBegin.x >= atlasWidth) {
            textureBegin.x = 0;
            textureBegin.y += 16;
        }

        stbi_image_free(data);
    }

    glGenTextures(1, &glTextureID);
    glBindTexture(GL_TEXTURE_2D, glTextureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, atlasWidth, atlasHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, atlasData.get());
}

TextureCoords TextureAtlas::getTextureCoords(const std::string &fileName) const {
    glm::vec2 begin;
    try {
        begin = stitchedTextureMap.at(fileName);
    } catch (std::out_of_range& e) {
        throw std::runtime_error(fileName + " doesn't exist in the texture atlas!");
    }
    return { begin.x, begin.y, begin.x + 16.0f / atlasWidth, begin.y + 16.0f / atlasHeight };
}

void TextureAtlas::bind() {
    glBindTexture(GL_TEXTURE_2D, glTextureID);
}
