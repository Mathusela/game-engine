#ifndef GAME_ENGINE_APPLICATION_HPP
#define GAME_ENGINE_APPLICATION_HPP

#include "object.hpp"
#include "json.hpp"

#include <vector>
#include <thread>

namespace GameEngine {

class GameEngineApplication {
private:
	// TODO: Default object_factory
	Object*(*object_factory)(const json& data);
	// TODO: Shaders
	std::vector<Object*> objects;
	// TODO: Render layers
	// TODO: Physics handler

	std::vector<std::thread*> executionThreads {};

public:
	GameEngineApplication(Object*(*object_factory)(const json& data));
	~GameEngineApplication() noexcept;

	void initScene(const json& data);
	void run();
	void join();
};

}	// namespace GameEngine

#endif