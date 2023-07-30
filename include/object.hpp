#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "shader.hpp"

#include <string>
#include <memory>
#include <vector>
#include <iostream>

namespace GameEngine {

class Object {
protected:
	unsigned int VAO;
	unsigned int VBO;
	// Must be in this class for physics (to be handled by physics handler)
	// TODO: Position
	// TODO: Rotation

public:
	static const std::string id;
	virtual ~Object() noexcept {}
	virtual void draw(Shader* shader) = 0;
};

}	// namespace GameEngine

#endif