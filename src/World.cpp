#include "World.h"
#include "Game.h"

World::World() {
    /*
    entities.push_back(playerEntity);
    entities.push_back(std::make_shared<Entity>());
    */
}

void World::render(BatchRenderer& batchRenderer, Game& game) {
    for (std::shared_ptr<Entity> entity : entities) {
        game.entityRenderers[typeid(*entity).name()]->render(batchRenderer, entity); // NOLINT
    }
}

/*
std::shared_ptr<PlayerEntity> World::getPlayer() {
    return playerEntity;
}*/

void World::tick(double deltaTime) {
    for (std::shared_ptr<Entity> entity : entities) {
        entity->tick(deltaTime);
    }
}

void World::addEntity(std::shared_ptr<Entity> entity) {
    entity->worldWeakPtr = weak_from_this();
    entities.push_back(entity);
}
