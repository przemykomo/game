#pragma once

#include "BatchRenderer.h"
#include "entities/Entity.h"
#include "entities/PlayerEntity.h"
#include <memory>
#include <vector>

class Game;

class World : public std::enable_shared_from_this<World> {
    private:
        //std::shared_ptr<PlayerEntity> playerEntity;
    public:
        std::vector<std::shared_ptr<Entity>> entities;
        World();
        void render(BatchRenderer& batchRenderer, Game& game);
        //std::shared_ptr<PlayerEntity> getPlayer();
        void tick(double deltaTime); //TODO: tick shouldn't be called every frame so it should calculate it's own deltaTime
        void addEntity(std::shared_ptr<Entity> entity);
};
