#ifndef JSON_LOADER_H
#define JSON_LOADER_H

#include "nlohmann\json.hpp"
#include "..\AnimatedModel\Mesh.h"

using json = nlohmann::json;

class RiggedModel
{
public:
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec4> jointIds;
	std::vector<glm::vec4> jointWeights;
	std::vector<unsigned int> indices;
};

class JSONLoader
{
public:
	JSONLoader(const std::string& filename);

	std::vector<IndexedModel> getIndexedModels();
private:
	std::vector<IndexedModel> _models;
};

#endif