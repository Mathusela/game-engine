#include "game_engine_application.hpp"
#include "extern/json.hpp"

#include <iostream>

#include <extern/glad/glad.h>
#include <extern/GLFW/glfw3.h>

using namespace GameEngine;

GameEngineApplication::GameEngineApplication(Object*(*object_factory)(const json& data)): object_factory(object_factory) {
	glfwInit();

	std::cout << "APPLICATION CONSTRUCTED\n";
}

GameEngineApplication::~GameEngineApplication() noexcept {
	join();
	for (auto ptr : objects) delete ptr;
	std::cout << "APPLICATION DESTROYED\n";
}

void GameEngineApplication::initScene(const json& data) {
	for (auto objectJson : data.at("Objects")) {
		std::cout << objectJson << "\n";
		objects.push_back(object_factory(objectJson));
	}
} 

void renderStep() {
	glClear(GL_COLOR_BUFFER_BIT);
}

void physicsStep() {

}

void loopThreadFunction(int width, int height, std::string title) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	
	glClearColor(0.0, 0.0, 1.0, 1.0);
	while(!glfwWindowShouldClose(window)) {
        physicsStep();	// TODO: Make its own thread
		renderStep();	// TODO: Pass delta time
		
		glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void GameEngineApplication::run(int width, int height, std::string title) {
	executionThreads.push_back(new std::thread(loopThreadFunction, width, height, title));
}

void GameEngineApplication::join() {
	for (auto thread : executionThreads) {
		thread->join();
		delete thread;
	}
	executionThreads = {};
}