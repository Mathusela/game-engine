#include "camera.hpp"

#include <extern/glm/gtc/matrix_transform.hpp>

#include <iostream>

using namespace GameEngine;

Camera::Camera(glm::vec3 position, glm::vec3 forward) {
	// TODO: offload these parameters to JSON
	projectionMatrix = glm::perspective(90.0, 500.0/500.0, 0.1, 100.0);
	setPosition(position);
	setForward(forward);
	std::cout << "CAMERA CONSTRUCTED\n";
}

Camera::~Camera() {
	std::cout << "CAMERA DESTROYED\n";
}

void Camera::updateViewMatrix() {
	viewMatrix = glm::lookAt(position, forward, up);
}

void Camera::setPosition(const glm::vec3& pos) {
	position = pos;
	updateViewMatrix();
}
glm::vec3 Camera::getPosition() {
	return position;
}

void Camera::setForward(const glm::vec3& vec) {
	forward = position + vec;
	updateViewMatrix();
}
glm::vec3 Camera::getForward() {
	return forward;
}

glm::mat4 Camera::getViewMatrix() {
	return viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix() {
	return projectionMatrix;
}