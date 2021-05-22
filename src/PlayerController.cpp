#include "PlayerController.h"

PlayerController::PlayerController(const std::shared_ptr<PlayerEntity>& playerEntity) : playerEntity(playerEntity) {}

void PlayerController::tick(GLFWwindow* window, double deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_A)) {
        playerEntity->moveRight -= 0.2 * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_D)) {
        playerEntity->moveRight += 0.2 * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_S)) {
        playerEntity->moveUp -= 0.2 * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_W)) {
        playerEntity->moveUp += 0.2 * deltaTime;
    }
}
