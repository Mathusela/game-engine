#ifndef RENDER_LAYER_HPP
#define RENDER_LAYER_HPP

#include "object.hpp"

#include <vector>

namespace GameEngine {

class RenderLayer {
private:
	std::vector<Object*> objects;
	// SHADER
	// CAMERA

public:
	RenderLayer();
	RenderLayer(const std::vector<Object*>& objects);
	// Should return and take texture
	void draw();
	void attachObject(Object* object);
};

}	// namespace GameEngine

#endif