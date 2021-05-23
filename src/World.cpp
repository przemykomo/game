#include "World.h"
#include "Game.h"

World::World() {}

void World::render(BatchRenderer& batchRenderer, Game& game, double partialTicks) {
    for (std::shared_ptr<Entity> entity : entities) {
        game.entityRenderers[typeid(*entity).name()]->render(batchRenderer, entity, partialTicks); // NOLINT
    }
}

void World::tick() {
    for (std::shared_ptr<Entity> entity : entities) {
        entity->tick();
    }
}

void World::addEntity(std::shared_ptr<Entity> entity) {
    entity->worldWeakPtr = weak_from_this();
    entities.push_back(entity);
}
