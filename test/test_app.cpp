#include <game_engine_application.hpp>
#include <object.hpp>
#include <json_internal.hpp>

#include <iostream>

GameEngine::Object* factory(GameEngine::json data) {
	return nullptr;
}

int main() {
	GameEngine::GameEngineApplication app(factory);

	GameEngine::json sceneJson = GameEngine::loadScene("../../test/leveldat.json");
	std::cout << sceneJson << "\n";

	return 0;
}