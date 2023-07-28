#include "game_engine_application.hpp"
#include "extern/json.hpp"

#include <iostream>

using namespace GameEngine;

GameEngineApplication::GameEngineApplication(Object*(*object_factory)(json data)) {
	std::cout << "Constructed\n";
}

GameEngineApplication::~GameEngineApplication() noexcept {
	std::cout << "Destructed\n";
}