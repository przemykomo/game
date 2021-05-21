#include "WindowCallbacks.h"
#include "PlayerController.h"
#include <GLFW/glfw3.h>

using namespace gl;

void initCallbacks(GLFWwindow* window) {
    glfwSetKeyCallback(window, keyCallback);
    glfwSetWindowSizeCallback(window, windowSizeCallback);
}

void keyCallback(GLFWwindow *window, int key, int scanCode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        if (key == GLFW_KEY_ESCAPE) {
            glfwSetWindowShouldClose(window, true);
        }
    }
}

void windowSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}
