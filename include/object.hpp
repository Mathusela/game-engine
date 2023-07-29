#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <string>
#include <memory>
#include <vector>
#include <iostream>

namespace GameEngine {

class Object {
protected:
	// Must be in this class for physics (to be handled by physics handler)
	// TODO: Position
	// TODO: Rotation

public:
	virtual ~Object() noexcept {}
	virtual void draw() = 0;
};

}	// namespace GameEngine

#endif