#ifndef MESH_H
#define MESH_H

#include "glm\glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm\gtx\transform.hpp>
#include "glm\gtx\quaternion.hpp"
#include "nlohmann\json.hpp"
#include <GL\glew.h>
#include <unordered_map>

using json = nlohmann::json;

struct BoneData
{
	glm::mat4 offsetMatrix;
	glm::mat4 finalTransformation;
};

class Mesh 
{
public:
	Mesh(const json& jsonObj);
	virtual ~Mesh();

	void Draw();

	std::vector<glm::mat4> GetBoneArray();

	std::unordered_map<std::string, unsigned int> _boneIdMap;
	std::unordered_map<unsigned int, BoneData> _boneDataMap;

private:

	enum MeshBufferPositions {
		POSITION,
		TEX_COORD,
		NORMAL,
		JOINT_IDS,
		JOINT_WEIGHTS,
		INDEX,
		NUM_BUFFERS
	};

	GLuint _vao;
	GLuint _vbo[NUM_BUFFERS];
	unsigned int _drawCount;
};
#endif