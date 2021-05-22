#include "World.h"
#include "Game.h"

World::World() : playerEntity(std::make_shared<PlayerEntity>()) {
    entities.push_back(playerEntity);
    entities.push_back(std::make_shared<Entity>());
}

void World::render(BatchRenderer& batchRenderer, Game& game) {
    for (std::shared_ptr<Entity> entity : entities) {
        game.entityRenderers[typeid(*entity).name()]->render(batchRenderer, entity);
    }
}

std::shared_ptr<PlayerEntity> World::getPlayer() {
    return playerEntity;
}

void World::tick(double deltaTime) {
    for (std::shared_ptr<Entity> entity : entities) {
        entity->tick(deltaTime);
    }
}
