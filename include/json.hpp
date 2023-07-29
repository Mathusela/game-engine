#ifndef JSON_HPP
#define JSON_HPP

#include "extern/json.hpp"

#include <vector>
#include <array>
#include <string>

namespace GameEngine {

using json = nlohmann::json;

// struct ShaderJsonData {
// 	using shaderId = std::string;
// 	shaderId id;
// 	std::string fragmentPath;
// 	std::string vertexPath;
// };

// struct ObjectJsonData {
// 	using objectId = std::string;
// 	objectId id;
// 	ShaderJsonData::shaderId shaderId;
// 	std::string geometryPath;
// 	std::array<float, 3> position;
// 	std::array<float, 3> rotation;
// };

// struct SceneJsonData {
// 	std::vector<ShaderJsonData> Shaders;
// 	std::vector<ObjectJsonData> Objects;
// };

json loadScene(std::string path);

}	// namespace GameEngine

#endif