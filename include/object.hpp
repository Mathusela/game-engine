#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "shader.hpp"
#include "json.hpp"
#include "camera.hpp"

#include <string>
#include <memory>
#include <vector>
#include <iostream>

#include <extern/glm/glm.hpp>

namespace GameEngine {

class Object {
protected:
	unsigned int VAO;
	unsigned int VBO;
	// Must be in this class for physics (to be handled by physics handler)
	glm::mat4 worldMatrix;
	glm::mat4 positionMatrix;
	glm::mat4 rotationMatrix;
	glm::vec3 position;
	glm::vec3 rotation;

	void updateWorldMatrix();

public:
	static const std::string id;
	virtual ~Object() noexcept {}
	virtual void draw(Shader* shader, Camera* camera) = 0;
	virtual void tick(float deltaTime) = 0;
	
	void setPosition(const glm::vec3& pos);
	glm::vec3 getPosition();
	
	void setRotation(const glm::vec3& rot);
	glm::vec3 getRotation();

	glm::mat4 getWorldMatrix();
};

}	// namespace GameEngine

#endif