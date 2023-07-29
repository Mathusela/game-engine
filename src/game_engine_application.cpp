#include "game_engine_application.hpp"
#include "extern/json.hpp"

#include <iostream>

#include <extern/glad/glad.h>
#include <extern/GLFW/glfw3.h>

using namespace GameEngine;

GameEngineApplication::GameEngineApplication(Object*(*object_factory)(const json& data)): object_factory(object_factory) {
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

}

void physicsStep() {

}

void loopThreadFunction() {
	glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);

    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	
	while(!glfwWindowShouldClose(window)) {
        physicsStep();	// Make its own thread
		renderStep();
		
		// glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void GameEngineApplication::run() {
	executionThreads.push_back(new std::thread(loopThreadFunction));
}

void GameEngineApplication::join() {
	for (auto thread : executionThreads) {
		thread->join();
		delete thread;
	}
	executionThreads = {};
}