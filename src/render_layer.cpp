#include "render_layer.hpp"

using namespace GameEngine;

RenderLayer::RenderLayer(Shader* shader, Camera* camera, const std::vector<Object*>& objects): shader(shader), camera(camera), objects(objects) {

}

void RenderLayer::draw() {
	shader->bind();
	for (auto object : objects) object->draw(shader, camera);
}

void RenderLayer::attachObject(Object* object) {
	objects.push_back(object);
}