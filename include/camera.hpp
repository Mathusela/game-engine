#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <extern/glm/glm.hpp>

namespace GameEngine {

// TODO: tick()
class Camera {
private:
	glm::vec3 position;
	glm::vec3 up = glm::vec3(0.0, 1.0, 0.0);
	glm::vec3 forward;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	void updateViewMatrix();

public:
	Camera(glm::vec3 position, glm::vec3 forward);
	~Camera();
	
	void setPosition(const glm::vec3& pos);
	glm::vec3 getPosition();

	void setForward(const glm::vec3& vec);
	glm::vec3 getForward();

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
};

}	// namespace GameEngine

#endif