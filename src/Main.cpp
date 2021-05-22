#include "Game.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

int main(int argc, char* argv[]) {
    const std::string_view programName(argv[0]);
    const std::string currentDirectory(programName.substr(0, programName.find_last_of('/')));
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    Game game(currentDirectory);

    game.loop();

    glfwTerminate();
    return 0;
}
