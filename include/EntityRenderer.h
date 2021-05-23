#pragma once
#include "BatchRenderer.h"
#include "entities/Entity.h"
#include "SquareModel.h"
#include "TextureAtlas.h"
#include <memory>

class EntityRenderer {
    private:
        SquareModel model;
    public:
        EntityRenderer(TextureAtlas& textureAtlas, const std::string& currentDirectory);
        EntityRenderer(SquareModel&& model);
        void render(BatchRenderer& batchRenderer, std::shared_ptr<Entity> entity, double partialTicks);
};
