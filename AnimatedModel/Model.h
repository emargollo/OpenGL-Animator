#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "Mesh.h"


class Model
{
public:
	bool LoadModel(const std::string& filename);

	void Draw();

private:
	std::vector<Mesh> _meshes;

};

#endif