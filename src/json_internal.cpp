#include "json_internal.hpp"

#include <string>
#include <fstream>
#include <iostream>

using namespace GameEngine;

json GameEngine::loadScene(std::string path) {
	std::ifstream ifstream(path);
	auto json = json::parse(ifstream);
	return json;
}