#include "BatchRenderer.h"
#include "Entity.h"
#include "EntityRenderer.h"
#include "SquareModel.h"
#include "TextureAtlas.h"
#include "WindowCallbacks.h"
#include "Debug.h"
#include "Shaders.h"

#include <cstddef>
#include <iostream>

#define GLFW_INCLUDE_NONE
#include <glbinding/gl/enum.h>
#include <glbinding/gl/functions.h>
#include <glbinding/AbstractFunction.h>
#include <glbinding/FunctionCall.h>
#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>
#include <GLFW/glfw3.h>

using namespace gl;

int main(int argc, char* argv[]) {
    const std::string_view programName(argv[0]);
    const std::string currentDirectory(programName.substr(0, programName.find_last_of('/')));
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow* window = glfwCreateWindow(640, 480, "Game", NULL, NULL);
    glfwMakeContextCurrent(window);
    initCallbacks(window);
    glfwSwapInterval(1);
    
    glbinding::initialize(glfwGetProcAddress);
#ifdef DEBUG
        glbinding::setCallbackMask(glbinding::CallbackMask::After | glbinding::CallbackMask::ParametersAndReturnValue);
        glbinding::setAfterCallback(glCallback);
#endif

    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);

    TextureAtlas textureAtlas{};
    textureAtlas.addTexture(currentDirectory + "/a.png");
    textureAtlas.addTexture(currentDirectory + "/b.png");
    textureAtlas.addTexture(currentDirectory + "/c.png");
    textureAtlas.stitch();
    textureAtlas.bind();

    BatchRenderer batchRenderer(vertexShaderSource, fragmentShaderSource);

    Entity entity;
    Entity entity2;
    entity2.x = 0.2f;
    EntityRenderer entityRenderer(textureAtlas, currentDirectory);

    while (!glfwWindowShouldClose(window)) {
        glClear(gl::ClearBufferMask::GL_COLOR_BUFFER_BIT);
        entity.y += 0.1f / 60.0f;

        //shaderProgram.bind();
        batchRenderer.reset();

        entityRenderer.render(batchRenderer, entity);
        entityRenderer.render(batchRenderer, entity2);

        batchRenderer.flush();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
