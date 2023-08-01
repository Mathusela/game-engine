#include <game_engine_application.hpp>
#include <object.hpp>
#include <shader.hpp>
#include <json.hpp>

#include <iostream>

#include <extern/glm/gtx/string_cast.hpp>

glm::vec3 arrToVec3(const std::array<float, 3>& arr) {
	return glm::vec3(arr[0], arr[1], arr[2]);
}

// USER DEFINED CLASS
class UserObject : public GameEngine::Object {
public:
	static const std::string id;

	UserObject(const GameEngine::json& data) {
		auto position = arrToVec3(data.at("position").get<std::array<float, 3>>());
		auto rotation = arrToVec3(data.at("rotation").get<std::array<float, 3>>());

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
		shader->setUniform("world", getWorldMatrix());

		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	void tick(float deltaTime) {
		auto newRot = getRotation() + deltaTime*glm::vec3(20.0, 20.0, 0.0);
		setRotation(newRot);
	}
};
const std::string UserObject::id = "UserClass";

// MAIN ENTRY POINT
int main() {
	GameEngine::GameEngineApplication app(500, 500, "Game Engine");

	GameEngine::json sceneJson = GameEngine::loadScene("../../test/leveldat.json");
	app.initScene<UserObject>(sceneJson);
	app.run();

	return 0;
}

// TODO: Add Camera
// TODO: Add Textures
// TODO: Add Framebuffers to RenderLayers and pass output Textures between RenderLayers
// TODO: Add geometry import for objects
// TODO: Add serialization of levels (ability to save a level to JSON and read it back into the Engine)
// TODO: Put physics on its own thread