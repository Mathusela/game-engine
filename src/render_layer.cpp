#include "render_layer.hpp"

using namespace GameEngine;

RenderLayer::RenderLayer(Shader* shader, const std::vector<Object*>& objects): shader(shader), objects(objects) {

}

void RenderLayer::draw() {
	shader->bind();
	for (auto object : objects) object->draw(shader);
}

void RenderLayer::attachObject(Object* object) {
	objects.push_back(object);
}