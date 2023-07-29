#include "render_layer.hpp"

using namespace GameEngine;

RenderLayer::RenderLayer(): objects(std::vector<Object*> {}) {

}

RenderLayer::RenderLayer(const std::vector<Object*>& objects): objects(objects) {

}

void RenderLayer::draw() {
	for (auto object : objects) object->draw();
}

void RenderLayer::attachObject(Object* object) {
	objects.push_back(object);
}