#include <game_engine_application.hpp>
#include <object.hpp>
#include <json_internal.hpp>

#include <iostream>

class UserObject : public GameEngine::Object {

};

GameEngine::Object* factory(const GameEngine::json& data) {
	const std::string id = data.at("id").get<std::string>();
	if (id == "UserClass") {
		std::cout << "UserObject\n";
		return new UserObject {};
	}
	std::cout << "DefaultObject\n";
	return new GameEngine::Object {};
}

int main() {
	GameEngine::GameEngineApplication app(factory);

	GameEngine::json sceneJson = GameEngine::loadScene("../../test/leveldat.json");
	app.initScene(sceneJson);

	return 0;
}