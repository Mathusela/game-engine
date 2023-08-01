#include "game_engine_application.hpp"
#include "extern/json.hpp"

#include <iostream>
#include <ctime>

#include <extern/glad/glad.h>
#include <extern/GLFW/glfw3.h>

using namespace GameEngine;

GameEngineApplication::GameEngineApplication(int width, int height, std::string title) {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	std::cout << "APPLICATION CONSTRUCTED\n";
}

GameEngineApplication::~GameEngineApplication() noexcept {
	join();
	for (auto ptr : objects) delete ptr;
	for (auto ptr : renderLayers) delete ptr;
	for (auto ptr : shaders) delete ptr;
	glfwTerminate();
	std::cout << "APPLICATION DESTROYED\n";
}

// void GameEngineApplication::initScene(const json& data) 

void renderStep(const std::vector<RenderLayer*>& renderLayers) {
	glClear(GL_COLOR_BUFFER_BIT);

	for (auto renderLayer : renderLayers) renderLayer->draw();
}

void physicsStep() {

}

void GameEngineApplication::run() {
	glClearColor(0.0, 0.0, 1.0, 1.0);
	
	float deltaTime = 0.0;
	float prevFrame = 0.0;

	while(!glfwWindowShouldClose(window)) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - prevFrame;
		prevFrame = currentFrame;
		
		for (auto object : objects) object->tick(deltaTime);
        physicsStep();	// TODO: Make its own thread
		renderStep(renderLayers);
		
		glfwSwapBuffers(window);
        glfwPollEvents();
    }

	// executionThreads.push_back(new std::thread(loopThreadFunction, window, renderLayers));
}

void GameEngineApplication::join() {
	for (auto thread : executionThreads) {
		thread->join();
		delete thread;
	}
	executionThreads = {};
}