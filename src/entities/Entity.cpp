#include "entities/Entity.h"
#include "World.h"
#include <memory>

Entity::Entity() : x(0.0f), y(0.0f), aabb(0.0f, 0.0f, 1.0f, 1.0f) {}

void Entity::tick(double deltaTime) {
    if (std::shared_ptr<World> world = worldWeakPtr.lock()) {
        for (std::shared_ptr<Entity> entity : world->entities) {
            if (entity.get() == this) {
                continue;
            }
            // if collides
            if (!(this->aabb.left + this->x > entity->aabb.right + entity->x ||
                        this->aabb.right + this->x < entity->aabb.left + entity->x ||
                        this->aabb.down + this->y > entity->aabb.up + entity->y ||
                        this->aabb.up + this->y < entity->aabb.down + entity->y)) {
                this->x += (this->x - entity->x) * deltaTime * 3;
                this->y += (this->y - entity->y) * deltaTime * 3;
            }
        }
    }
}
