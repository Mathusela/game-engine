#include <game_engine_application.hpp>
#include <object.hpp>
#include <json.hpp>

#include <iostream>

#include <extern/glad/glad.h>
#include <extern/GLFW/glfw3.h>

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
	GameEngine::GameEngineApplication app(factory);

	GameEngine::json sceneJson = GameEngine::loadScene("../../test/leveldat.json");
	app.initScene(sceneJson);

	glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);

    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	while(!glfwWindowShouldClose(window)) {
        // glfwSwapBuffers(window);
        glfwPollEvents();
    }

	return 0;
}