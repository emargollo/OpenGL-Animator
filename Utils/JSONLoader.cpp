#include "JSONLoader.h"
#include <fstream>
#include <iterator>
#include <iostream>

JSONLoader::JSONLoader(const std::string & filename)
{
	json obj;
	std::ifstream file(filename);
	file >> obj;
	file.close();

	for (json j : obj["meshes"])
	{
		IndexedModel model;
		model.indices = j["indices"].get<std::vector<unsigned int>>();
		for (json vertex : j["vertices"]) {
			glm::vec3 pos(vertex["pos"]["x"], vertex["pos"]["y"], vertex["pos"]["z"]);
			glm::vec2 texcoord(vertex["texcoord"]["x"], vertex["texcoord"]["y"]);
			glm::vec3 normal(vertex["normal"]["x"], vertex["normal"]["y"], vertex["normal"]["z"]);
			model.positions.push_back(pos);
			model.texCoords.push_back(texcoord);
			model.normals.push_back(normal);
		}
		_models.push_back(model);
	}
	
}

std::vector<IndexedModel> JSONLoader::getIndexedModels()
{
	return _models;
}
