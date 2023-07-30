#include "game_engine_application.hpp"
#include "extern/json.hpp"

#include <iostream>

#include <extern/glad/glad.h>
#include <extern/GLFW/glfw3.h>

using namespace GameEngine;

GameEngineApplication::GameEngineApplication(int width, int height, std::string title, Object*(*object_factory)(const json& data)): object_factory(object_factory) {
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

void GameEngineApplication::initScene(const json& data) {
	auto shadersArray = data.at("Shaders");
	for (int i=0; i<shadersArray.size(); i++) shaders.push_back(nullptr);
	for (auto shaderJson : shadersArray) {
		std::cout << shaderJson << "\n";
		shaders[shaderJson.at("id").get<int>()] = new Shader(shaderJson.at("vertexPath").get<std::string>(), shaderJson.at("fragmentPath").get<std::string>());
	}
	
	auto renderLayersArray = data.at("RenderLayers");
	for (int i=0; i<renderLayersArray.size(); i++) renderLayers.push_back(nullptr);
	for (auto renderLayerJson : renderLayersArray) {
		std::cout << renderLayerJson << "\n";
		renderLayers[renderLayerJson.at("id").get<int>()] = new RenderLayer(std::vector<Object*> {});
	}

	for (auto objectJson : data.at("Objects")) {
		std::cout << objectJson << "\n";
		Object* object;
		objects.push_back(object = object_factory(objectJson));
		renderLayers[objectJson.at("renderLayerId").get<int>()]->attachObject(object);
	}
} 

void renderStep(const std::vector<RenderLayer*>& renderLayers) {
	glClear(GL_COLOR_BUFFER_BIT);

	for (auto renderLayer : renderLayers) renderLayer->draw();
}

void physicsStep() {

}

void GameEngineApplication::run() {
	glClearColor(0.0, 0.0, 1.0, 1.0);
	while(!glfwWindowShouldClose(window)) {
        physicsStep();	// TODO: Make its own thread
		renderStep(renderLayers);	// TODO: Pass delta time
		
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