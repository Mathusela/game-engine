#include "game_engine_application.hpp"

#include <iostream>

using namespace GameEngine;

GameEngineApplication::GameEngineApplication() {
	std::cout << "Constructed\n";
}

GameEngineApplication::~GameEngineApplication() noexcept {
	std::cout << "Destructed\n";
}