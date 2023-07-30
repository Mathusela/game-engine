#include <game_engine_application.hpp>
#include <object.hpp>
#include <shader.hpp>
#include <json.hpp>

#include <iostream>

// USER DEFINED CLASS
class UserObject : public GameEngine::Object {
public:
	static const std::string id;

	UserObject(glm::vec3 position, glm::vec3 rotation) {
		setPosition(position);
		setRotation(rotation);

		float verts[] = {
			-0.5, -0.5, 0.0,
			-0.5, 0.5, 0.0,
			0.5, -0.5, 0.0,

			-0.5, 0.5, 0.0,
			0.5, -0.5, 0.0,
			0.5, 0.5, 0.0
		};

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	    glEnableVertexAttribArray(0);

		std::cout << "USER OBJECT CONSTRUCTED\n";
	}

	~UserObject() noexcept {
		std::cout << "USER OBJECT DESTROYED\n";
	}

	void draw(GameEngine::Shader* shader) {
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	void tick() {

	}
};
const std::string UserObject::id = "UserClass";

// USER DEFINED FACTORY FUNCTION
GameEngine::Object* factory(const GameEngine::json& data) {
	const std::string id = data.at("id").get<std::string>();
	auto positionArray = data.at("position").get<std::array<float, 3>>();
	auto position = glm::vec3(positionArray[0], positionArray[1], positionArray[2]);
	auto rotationArray = data.at("rotation").get<std::array<float, 3>>();
	auto rotation = glm::vec3(rotationArray[0], rotationArray[1], rotationArray[2]);

	if (id == UserObject::id)
		return new UserObject {position, rotation};

	std::cout << "Invalid Object\n";
	return nullptr;
}

// MAIN ENTRY POINT
int main() {
	GameEngine::GameEngineApplication app(500, 500, "Game Engine", factory);

	GameEngine::json sceneJson = GameEngine::loadScene("../../test/leveldat.json");
	app.initScene(sceneJson);
	app.run();

	return 0;
}

// TODO: Add set union method to Shader
// TODO: Add Camera
// TODO: Add Textures
// TODO: Add Framebuffers to RenderLayers and pass output Textures between RenderLayers
// TODO: Add geometry import for objects
// TODO: Add serialization of levels (ability to save a level to JSON and read it back into the Engine)