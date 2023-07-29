#include "game_engine_application.hpp"
#include "extern/json.hpp"

#include <iostream>

using namespace GameEngine;

GameEngineApplication::GameEngineApplication(Object*(*object_factory)(const json& data)): object_factory(object_factory) {
	std::cout << "APPLICATION CONSTRUCTED\n";
}

GameEngineApplication::~GameEngineApplication() noexcept {
	for (auto ptr : objects) delete ptr;
	std::cout << "APPLICATION DESTROYED\n";
}

void GameEngineApplication::initScene(const json& data) {
	for (auto objectJson : data.at("Objects")) {
		std::cout << objectJson << "\n";
		objects.push_back(object_factory(objectJson));
	}
} 