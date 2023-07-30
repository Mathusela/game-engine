#include "shader.hpp"

#include <fstream>
#include <iostream>

#include <extern/glad/glad.h>
#include <extern/GLFW/glfw3.h>

using namespace GameEngine;

std::string loadShaderSource(std::string inputPath) {
    std::ifstream input(inputPath);
	if (!input) {
		throw std::runtime_error("Failed to import shader source from file: " + inputPath);
	}

    std::string inputText = "";

    for (std::string line; getline(input, line);) {
        inputText = inputText + "\n" + line;
    }

    inputText += "\0";

    input.close();
    input.clear();


    return inputText;
}

Shader::Shader(std::string vertexPath, std::string fragmentPath) : vertexPath(vertexPath), fragmentPath(fragmentPath) {
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	
	auto vertexSource = loadShaderSource(vertexPath).c_str();
	auto fragmentSource = loadShaderSource(fragmentPath).c_str();
	
	auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
	auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);

	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	glId = glCreateProgram();
	glAttachShader(glId, vertexShader);
	glAttachShader(glId, fragmentShader);
	glLinkProgram(glId);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	std::cout << "SHADER CONSTRUCTED\n";
}

Shader::~Shader() noexcept {
	glDeleteProgram(glId);
	std::cout << "SHADER DESTROYED\n";
}

void Shader::bind() {
	glUseProgram(glId);
}