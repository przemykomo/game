#include "entities/PlayerEntity.h"
#include <algorithm>

PlayerEntity::PlayerEntity() : Entity() {}

void PlayerEntity::tick(double deltaTime) {
    moveRight = std::clamp(moveRight, -1.0f, 1.0f);
    moveUp = std::clamp(moveUp, -1.0f, 1.0f);

    x += moveRight;
    y += moveUp;

    moveRight *= 0.9f;
    moveUp *= 0.9f;
}
