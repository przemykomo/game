#pragma once

#include "BatchRenderer.h"
#include "entities/Entity.h"
#include "entities/PlayerEntity.h"
#include <memory>
#include <vector>

class Game;

class World {
    private:
        std::vector<std::shared_ptr<Entity>> entities;
        std::shared_ptr<PlayerEntity> playerEntity;
    public:
        World();
        void render(BatchRenderer& batchRenderer, Game& game);
        std::shared_ptr<PlayerEntity> getPlayer();
        void tick(double deltaTime); //TODO: tick shouldn't be called every frame so it should calculate it's own deltaTime
};
