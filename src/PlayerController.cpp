#include "PlayerController.h"

PlayerController::PlayerController(const std::shared_ptr<Entity>& playerEntity) : playerEntity(playerEntity) {}

void PlayerController::tick(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_A)) {
            playerEntity->x -= 1.0f / 60.0f;
    }

    if (glfwGetKey(window, GLFW_KEY_D)) {
            playerEntity->x += 1.0f / 60.0f;
    }

    if (glfwGetKey(window, GLFW_KEY_S)) {
            playerEntity->y -= 1.0f / 60.0f;
    }

    if (glfwGetKey(window, GLFW_KEY_W)) {
            playerEntity->y += 1.0f / 60.0f;
    }
}
