#ifndef GAME_ENGINE_APPLICATION_HPP
#define GAME_ENGINE_APPLICATION_HPP

#include "object.hpp"
#include "json_internal.hpp"

#include <vector>

namespace GameEngine {

class GameEngineApplication {
private:
	Object*(*object_factory)(const json& data);
	// TODO: Shaders
	std::vector<Object*> objects;
	// TODO: Render layers
	// TODO: Physics handler

public:
	GameEngineApplication(Object*(*object_factory)(const json& data));
	~GameEngineApplication() noexcept;

	void initScene(const json& data);
};

}	// namespace GameEngine

#endif