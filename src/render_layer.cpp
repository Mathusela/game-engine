#include "render_layer.hpp"

using namespace GameEngine;

RenderLayer::RenderLayer(Shader* shader, const std::vector<Object*>& objects): shader(shader), objects(objects) {

}

void RenderLayer::draw() {
	for (auto object : objects) object->draw();
}

void RenderLayer::attachObject(Object* object) {
	objects.push_back(object);
}