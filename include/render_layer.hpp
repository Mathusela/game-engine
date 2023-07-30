#ifndef RENDER_LAYER_HPP
#define RENDER_LAYER_HPP

#include "object.hpp"
#include "shader.hpp"

#include <vector>

namespace GameEngine {

class RenderLayer {
private:
	std::vector<Object*> objects;
	Shader* shader;
	// CAMERA

public:
	RenderLayer(Shader* shader, const std::vector<Object*>& objects = std::vector<Object*> {});
	// Should return and take texture
	void draw();
	void attachObject(Object* object);
};

}	// namespace GameEngine

#endif