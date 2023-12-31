#include "object.hpp"

#include "json.hpp"

#include <extern/glm/gtc/matrix_transform.hpp>

using namespace GameEngine;

const std::string GameEngine::Object::id = "Object";

void Object::updateWorldMatrix() {
	worldMatrix = positionMatrix * rotationMatrix;
}

void Object::setPosition(const glm::vec3& pos) {
	position = pos;
	positionMatrix = glm::translate(glm::identity<glm::mat4>(), pos);
	updateWorldMatrix();
}

glm::vec3 Object::getPosition() {
	return position;
}
	
void Object::setRotation(const glm::vec3& rot) {
	rotation = rot;
	auto mat = glm::identity<glm::mat4>();
	mat = glm::rotate(mat, glm::radians(rotation.x), glm::vec3(1.0, 0.0, 0.0));
	mat = glm::rotate(mat, glm::radians(rotation.y), glm::vec3(0.0, 1.0, 0.0));
	mat = glm::rotate(mat, glm::radians(rotation.z), glm::vec3(0.0, 0.0, 1.0));
	rotationMatrix = mat;
	updateWorldMatrix();
}

glm::vec3 Object::getRotation() {
	return rotation;
}

glm::mat4 Object::getWorldMatrix() {
	return worldMatrix;
}