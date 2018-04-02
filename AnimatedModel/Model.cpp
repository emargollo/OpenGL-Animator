#include "Model.h"
#include "fstream"
#include "nlohmann\json.hpp"

using json = nlohmann::json;

bool Model::LoadModel(const std::string & filename)
{
	json model;
	std::ifstream file(filename);
	file >> model;
	file.close();

	for (json jsonMesh : model["meshes"])
	{
		Mesh mesh(jsonMesh);
		_meshes.push_back(mesh);
	}

	return false;
}

void Model::Draw()
{
	for (Mesh mesh : _meshes)
	{
		mesh.Draw();
	}
}
