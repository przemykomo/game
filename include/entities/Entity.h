#pragma once
#include "AxisAlignedBB.h"
#include <memory>

class World;

class Entity {
    public:
        double lastX, lastY;
        double x, y;
        double motionX, motionY;
        const AxisAlignedBB aabb;
        std::weak_ptr<World> worldWeakPtr;
        Entity();
        virtual void tick();
};
