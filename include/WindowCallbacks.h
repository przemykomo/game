#pragma once

#define GLFW_INCLUDE_NONE
#include <glbinding/gl/gl.h>
#include <GLFW/glfw3.h>

void initCallbacks(GLFWwindow* window);
void keyCallback(GLFWwindow *window, int key, int scanCode, int action, int mods);
void windowSizeCallback(GLFWwindow *window, int width, int height);
