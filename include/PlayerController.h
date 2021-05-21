#pragma once

#include "Entity.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <memory>

class PlayerController {
    private:
        std::shared_ptr<Entity> playerEntity;
    public:
        PlayerController(const std::shared_ptr<Entity>& playerEntity);
        void tick(GLFWwindow* window);
};
