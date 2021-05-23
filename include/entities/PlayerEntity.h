#pragma once
#include "Entity.h"

class PlayerEntity : public Entity {
    public:
        float moveRight = 0.0f;
        float moveUp = 0.0f;
        PlayerEntity();
        void tick() override;
};
