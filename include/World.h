#pragma once

#include "BatchRenderer.h"
#include "entities/Entity.h"
#include "entities/PlayerEntity.h"
#include <memory>
#include <vector>

class Game;

class World : public std::enable_shared_from_this<World> {
    public:
        std::vector<std::shared_ptr<Entity>> entities;
        World();
        void render(BatchRenderer& batchRenderer, Game& game, double partialTicks);
        void tick();
        void addEntity(std::shared_ptr<Entity> entity);
};
