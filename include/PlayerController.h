#pragma once

#include "entities/PlayerEntity.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <memory>

class PlayerController {
    private:
        std::shared_ptr<PlayerEntity> playerEntity;
    public:
        PlayerController(const std::shared_ptr<PlayerEntity>& playerEntity);
        void tick(GLFWwindow* window, double deltaTime);
};
