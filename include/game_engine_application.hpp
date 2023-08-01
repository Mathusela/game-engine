#ifndef GAME_ENGINE_APPLICATION_HPP
#define GAME_ENGINE_APPLICATION_HPP

#include "object.hpp"
#include "render_layer.hpp"
#include "shader.hpp"
#include "json.hpp"

#include <vector>
#include <thread>

#include <extern/glad/glad.h>
#include <extern/GLFW/glfw3.h>

namespace GameEngine {

class GameEngineApplication {
private:
	GLFWwindow* window;
	std::vector<Shader*> shaders;
	std::vector<Object*> objects;
	std::vector<RenderLayer*> renderLayers;
	// TODO: Physics handler

	std::vector<std::thread*> executionThreads {};

	template <class CustomClass>
	Object* objectFactory(const json& data) {
		const std::string id = data.at("id").get<std::string>();
		
		if (CustomClass::id == id) return new CustomClass(data);
		return nullptr;
	}

	template <class CustomClass, class CustomClass2, class... CustomClasses>
	Object* objectFactory(const json& data) {
		const std::string id = data.at("id").get<std::string>();
		
		if (CustomClass::id == id) return new CustomClass(data);
		return objectFactory<CustomClass2, CustomClasses...>(data);
	}

public:
	GameEngineApplication(int width, int height, std::string title);
	~GameEngineApplication() noexcept;

	template <class... CustomClasses>
	void initScene(const json& data) {
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
			renderLayers[renderLayerJson.at("id").get<int>()] = new RenderLayer(shaders[renderLayerJson.at("shaderId").get<int>()]);
		}

		for (auto objectJson : data.at("Objects")) {
			std::cout << objectJson << "\n";
			Object* object;
			objects.push_back(object = objectFactory<CustomClasses...>(objectJson));
			renderLayers[objectJson.at("renderLayerId").get<int>()]->attachObject(object);
		}
	}

	void run();
	void join();
};

}	// namespace GameEngine

#endif