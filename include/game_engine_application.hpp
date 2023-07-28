#ifndef GAME_ENGINE_APPLICATION_HPP
#define GAME_ENGINE_APPLICATION_HPP

#include "object.hpp"
#include "json_internal.hpp"

namespace GameEngine {

class GameEngineApplication {
public:
	GameEngineApplication(Object*(*object_factory)(json data));
	~GameEngineApplication() noexcept;
};

}	// namespace GameEngine

#endif