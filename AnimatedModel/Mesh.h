#ifndef VERTEX_H
#define VERTEX_H

#include "glm\glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm\gtx\transform.hpp>
#include "glm\gtx\quaternion.hpp"
#include "..\Utils\obj_loader.h"
#include "nlohmann\json.hpp"

using json = nlohmann::json;

class Vertex 
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal = glm::vec3(0.0,0.0,0.0)) 
	{ 
		this->pos = pos; 
		this->texCoord = texCoord;
		this->normal = normal;
	}
	inline glm::vec3* GetPos() { return &pos; }
	inline glm::vec2* GetTexCoord() { return &texCoord; }
	inline glm::vec3* GetNormal() { return &normal; }
private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
};
#endif



#ifndef MESH_H
#define MESH_H

#include <GL\glew.h>
#include <unordered_map>

struct BoneData
{
	glm::mat4 offsetMatrix;
	glm::mat4 finalTransformation;
};

class Mesh 
{
public:
	Mesh(Vertex* vertices, unsigned int nVertices, unsigned int *indices, unsigned int nIndices);
	Mesh(const std::string& filename);
	Mesh(const json& jsonObj);
	Mesh(const IndexedModel& model);
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

	void initModel(IndexedModel model);

	GLuint _vao;
	GLuint _vbo[NUM_BUFFERS];
	unsigned int _drawCount;
};
#endif