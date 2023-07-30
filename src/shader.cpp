#include "shader.hpp"

#include <fstream>
#include <iostream>

#include <extern/glad/glad.h>
#include <extern/GLFW/glfw3.h>
#include <extern/glm/gtc/type_ptr.hpp>

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

void getShaderCompilationErrors(unsigned int shader, std::string type) {
	int success;
    char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        throw std::runtime_error(type + " shader compilation failed\n" + std::string(infoLog));
    };
}

Shader::Shader(std::string vertexPath, std::string fragmentPath) : vertexPath(vertexPath), fragmentPath(fragmentPath) {
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	
	auto _vertexSource = loadShaderSource(vertexPath);
	auto _fragmentSource = loadShaderSource(fragmentPath);
	auto vertexSource = _vertexSource.c_str();
	auto fragmentSource = _fragmentSource.c_str();
	
	auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
	auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);

	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	try {
		getShaderCompilationErrors(vertexShader, "Vertex");
		getShaderCompilationErrors(fragmentShader, "Fragment");
	} catch (std::exception e) {
		std::cout << e.what() << "\n";
		throw e;
	}

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

void Shader::setUniform(std::string location, int x) {
	glUniform1i(glGetUniformLocation(glId, location.c_str()), x);
}
void Shader::setUniform(std::string location, float x) {
	glUniform1f(glGetUniformLocation(glId, location.c_str()), x);
}
void Shader::setUniform(std::string location, glm::vec2 x) {
	glUniform2fv(glGetUniformLocation(glId, location.c_str()), 1, glm::value_ptr(x));
}
void Shader::setUniform(std::string location, glm::vec3 x) {
	glUniform3fv(glGetUniformLocation(glId, location.c_str()), 1, glm::value_ptr(x));
}
void Shader::setUniform(std::string location, glm::mat3 x) {
	glUniformMatrix3fv(glGetUniformLocation(glId, location.c_str()), 1, GL_FALSE, glm::value_ptr(x));
}
void Shader::setUniform(std::string location, glm::mat4 x) {
	glUniformMatrix4fv(glGetUniformLocation(glId, location.c_str()), 1, GL_FALSE, glm::value_ptr(x));
}