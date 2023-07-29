#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <string>
#include <memory>
#include <vector>

namespace GameEngine {

class Object {
protected:

public:
	virtual void draw() = 0;
};

}	// namespace GameEngine

#endif