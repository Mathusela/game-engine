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
	for (auto ptr : cameras) delete ptr;
	glfwTerminate();
	std::cout << "APPLICATION DESTROYED\n";
}

// Was throwing a redefinition error without the underscore, who knows why!
glm::vec3 _arrToVec3(const std::array<float, 3>& arr) {
	return glm::vec3(arr[0], arr[1], arr[2]);
}

glm::vec3 jsonToVec3(const json& data) {
	return _arrToVec3(data.get<std::array<float, 3>>());
}


void GameEngineApplication::loadNonObjects(const json& data) {
	auto camerasArray = data.at("Cameras");
	for (int i=0; i<camerasArray.size(); i++) cameras.push_back(nullptr);
	for (auto cameraJson : camerasArray) {
		std::cout << cameraJson << "\n";
		cameras[cameraJson.at("id").get<int>()] = new Camera(jsonToVec3(cameraJson.at("position")), jsonToVec3(cameraJson.at("forward")));
	}

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
		renderLayers[renderLayerJson.at("id").get<int>()] = new RenderLayer(shaders[renderLayerJson.at("shaderId").get<int>()], cameras[renderLayerJson.at("cameraId").get<int>()]);
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