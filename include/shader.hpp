#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

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
};

}	// namespace GameEngine

#endif