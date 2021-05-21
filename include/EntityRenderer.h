#pragma once
#include "BatchRenderer.h"
#include "Entity.h"
#include "SquareModel.h"
#include "TextureAtlas.h"
#include <memory>

class EntityRenderer {
    private:
        SquareModel model;
    public:
        EntityRenderer(TextureAtlas& textureAtlas, const std::string& currentDirectory);
        void render(BatchRenderer& batchRenderer, std::shared_ptr<Entity> entity);
};
