#pragma once

class ShaderProgram {
    private:
        unsigned int glID;
    public:
        ShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);
        ~ShaderProgram();
        void bind();
};
