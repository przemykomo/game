#pragma once
#include "BatchRenderer.h"
#include "EntityRenderer.h"
#include "TextureAtlas.h"
#include "World.h"

#include <memory>
#include <string>
#include <unordered_map>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class Game {
    private:
        GLFWwindow* glfwWindow;
        TextureAtlas textureAtlas;
        BatchRenderer batchRenderer;
        World world;
    public:
        std::unordered_map<std::string, std::shared_ptr<EntityRenderer>> entityRenderers;
        static void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
        static void windowSizeCallback(GLFWwindow* window, int width, int height);

        Game(const std::string& currentDirectory);
        void loop();
};
