#include "Debug.h"
#include <iostream>
#include <glbinding/AbstractFunction.h>
#include <glbinding/gl/gl.h>

using namespace gl;

#ifdef DEBUG
    void glCallback(const glbinding::FunctionCall& call) {
        if (std::string_view(call.function->name()).compare("glGetError")) {
            std::cout << call.function->name() << "(";
            for (unsigned i = 0; i < call.parameters.size(); ++i) {
                std::cout << call.parameters[i];
                if (i < call.parameters.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << ")";

            if (call.returnValue) {
                std::cout << " -> " << call.returnValue.get();
            }

            std::cout << "; glGetError() -> " << (unsigned int)glGetError() << std::endl; 
        }
    }
#endif
