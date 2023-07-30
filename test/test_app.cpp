#include <game_engine_application.hpp>
#include <object.hpp>
#include <json.hpp>

#include <iostream>

// USER DEFINED CLASS
class UserObject : public GameEngine::Object {
public:
	static const std::string id;

	UserObject() {
		std::cout << "USER OBJECT CONSTRUCTED\n";
	}

	~UserObject() noexcept {
		std::cout << "USER OBJECT DESTROYED\n";
	}

	void draw() {

	}
	
};
const std::string UserObject::id = "UserClass";

// USER DEFINED FACTORY FUNCTION
GameEngine::Object* factory(const GameEngine::json& data) {
	const std::string id = data.at("id").get<std::string>();

	if (id == UserObject::id)
		return new UserObject {};

	std::cout << "Invalid Object\n";
	return nullptr;
}

// MAIN ENTRY POINT
int main() {
	GameEngine::GameEngineApplication app(500, 500, "Game Engine", factory);

	GameEngine::json sceneJson = GameEngine::loadScene("../../test/leveldat.json");
	app.initScene(sceneJson);
	app.run();

	std::cout << "Do more stuff\n";

	return 0;
}

// TODO: Add Shaders
// TODO: Test draw once shaders are implemented
// TODO: Add Camera
// TODO: Add Textures
// TODO: Add Framebuffers to RenderLayers and pass output Textures between RenderLayers
// TODO: Add geometry import for objects
// TODO: Add serialization of levels (ability to save a level to JSON and read it back into the Engine)