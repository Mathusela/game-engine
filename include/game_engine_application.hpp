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
	// TODO: Default object_factory
	Object*(*object_factory)(const json& data);
	std::vector<Shader*> shaders;
	std::vector<Object*> objects;
	std::vector<RenderLayer*> renderLayers;
	// TODO: Physics handler

	std::vector<std::thread*> executionThreads {};

public:
	GameEngineApplication(int width, int height, std::string title, Object*(*object_factory)(const json& data));
	~GameEngineApplication() noexcept;

	void initScene(const json& data);
	void run();
	void join();
};

}	// namespace GameEngine

#endif