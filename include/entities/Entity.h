#pragma once

class Entity {
    public:
        float x, y;
        Entity();
        virtual void tick(double deltaTime);
};
