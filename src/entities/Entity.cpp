#include "entities/Entity.h"
#include "World.h"
#include <memory>

Entity::Entity() : lastX(0.0), lastY(0.0),  x(0.0), y(0.0), motionX(0.0), motionY(0.0), aabb(0.0f, 0.0f, 1.0f, 1.0f) {}

void Entity::tick() {
    lastX = x;
    lastY = y;

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
                this->motionX += (this->x - entity->x) * 3.0 / 20.0;
                this->motionY += (this->y - entity->y) * 3.0 / 20.0;
            }
        }
    }

    x += motionX;
    y += motionY;
    motionX *= 0.9;
    motionY *= 0.9;
}
