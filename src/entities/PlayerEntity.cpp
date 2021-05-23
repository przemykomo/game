#include "entities/PlayerEntity.h"
#include <algorithm>

PlayerEntity::PlayerEntity() : Entity() {}

void PlayerEntity::tick(double deltaTime) {
    Entity::tick(deltaTime);

    moveRight = std::clamp(moveRight, -20.0f, 20.0f);
    moveUp = std::clamp(moveUp, -20.0f, 20.0f);

    x += moveRight;
    y += moveUp;

    moveRight *= 0.9f;
    moveUp *= 0.9f;
}
