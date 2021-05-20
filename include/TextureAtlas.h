#pragma once

#include <glm/ext/vector_float2.hpp>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

struct TextureCoords {
    float left, bottom, right, top;
};

// Currently every texture is expected to be 16x16px
class TextureAtlas {
    private:
        unsigned int glTextureID;
        int atlasWidth;
        int atlasHeight;

        std::unordered_map<std::string, glm::vec2> stitchedTextureMap;

        std::unordered_set<std::string> fileNames;
    public:
        TextureAtlas() noexcept;
        ~TextureAtlas();
        void addTexture(const std::string& fileName);
        void stitch();
        TextureCoords getTextureCoords(const std::string& fileName) const;
        void bind();
};
