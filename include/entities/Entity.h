#pragma once
#include "AxisAlignedBB.h"
#include <memory>

class World;

class Entity {
    public:
        float x, y;
        const AxisAlignedBB aabb;
        std::weak_ptr<World> worldWeakPtr;
        Entity();
        virtual void tick(double deltaTime);
};
