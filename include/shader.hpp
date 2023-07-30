#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

#include "extern/glm/glm.hpp"

namespace GameEngine {

class Shader {
private:
	unsigned int glId;
	std::string vertexPath;
	std::string fragmentPath;

public:
	Shader(std::string vertexPath, std::string fragmentPath);
	~Shader() noexcept;
	void bind();

	void setUniform(std::string location, int x);
	void setUniform(std::string location, float x);
	void setUniform(std::string location, glm::vec2 x);
	void setUniform(std::string location, glm::vec3 x);
	void setUniform(std::string location, glm::mat3 x);
	void setUniform(std::string location, glm::mat4 x);
};

}	// namespace GameEngine

#endif