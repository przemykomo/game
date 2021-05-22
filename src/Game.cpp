#include "Game.h"
#include "Shaders.h"

#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>

using namespace gl;

void Game::keyCallback(GLFWwindow *window, int key, int scanCode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void Game::windowSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

Game::Game(const std::string& currentDirectory) {
    glfwWindow = glfwCreateWindow(640, 480, "Game", NULL, NULL);
    glfwSetWindowUserPointer(glfwWindow, this);
    glfwMakeContextCurrent(glfwWindow);
    glfwSwapInterval(1);

    glbinding::initialize(glfwGetProcAddress);
#ifdef GL_DEBUG
    glbinding::setCallbackMask(glbinding::CallbackMask::After | glbinding::CallbackMask::ParametersAndReturnValue);
    glbinding::setAfterCallback(glCallback);
#endif

    batchRenderer.init(vertexShaderSource, fragmentShaderSource);

    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);

    textureAtlas.addTexture(currentDirectory + "/a.png");
    textureAtlas.addTexture(currentDirectory + "/b.png");
    textureAtlas.addTexture(currentDirectory + "/c.png");
    textureAtlas.stitch();
    textureAtlas.bind();

    glfwSetKeyCallback(glfwWindow, keyCallback);
    glfwSetWindowSizeCallback(glfwWindow, windowSizeCallback);

    entityRenderers.emplace(std::make_pair(typeid(Entity).name(), std::make_shared<EntityRenderer>(textureAtlas, currentDirectory)));
    entityRenderers.emplace(std::make_pair(typeid(PlayerEntity).name(), std::make_shared<EntityRenderer>(SquareModel(textureAtlas.getTextureCoords(currentDirectory + "/a.png")))));
}

void Game::loop() {
    double deltaTime = 1.0 / 60.0;
    double timeBegin = glfwGetTime();

    while (!glfwWindowShouldClose(glfwWindow)) {
        // ---- CONTROLS ----
        glfwPollEvents();
        std::shared_ptr<PlayerEntity> playerEntity = world.getPlayer();
        if (glfwGetKey(glfwWindow, GLFW_KEY_A)) {
            playerEntity->moveRight -= 0.2 * deltaTime;
        }

        if (glfwGetKey(glfwWindow, GLFW_KEY_D)) {
            playerEntity->moveRight += 0.2 * deltaTime;
        }

        if (glfwGetKey(glfwWindow, GLFW_KEY_S)) {
            playerEntity->moveUp -= 0.2 * deltaTime;
        }

        if (glfwGetKey(glfwWindow, GLFW_KEY_W)) {
            playerEntity->moveUp += 0.2 * deltaTime;
        }
        // ---- END CONTROLS ----

        // ---- TICK ----
        world.tick(deltaTime);
        // ---- END TICK ----

        // ---- RENDER ----
        glClear(GL_COLOR_BUFFER_BIT);
        batchRenderer.reset();               

        world.render(batchRenderer, *this);

        batchRenderer.flush();
        glfwSwapBuffers(glfwWindow);
        // ---- RENDER END ----

        // ---- CALCULATE FRAME DELTA TIME ----
        double timeNow = glfwGetTime();
        deltaTime = timeNow - timeBegin;
        timeBegin = timeNow;
        // ---- END CALCULATE FRAME DELTA TIME ----
    }
}