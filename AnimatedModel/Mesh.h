#ifndef VERTEX_H
#define VERTEX_H

#include "glm\glm.hpp"
#include "..\Utils\obj_loader.h"

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

namespace vbo {
	enum MeshBufferPositions {
		POSITION,
		TEX_COORD,
		NORMAL,
		INDEX,
		NUM_BUFFERS
	};
}

#ifndef MESH_H
#define MESH_H

#include <GL\glew.h>

class Mesh 
{
public:
	Mesh(Vertex* vertices, unsigned int nVertices, unsigned int *indices, unsigned int nIndices);
	Mesh(const std::string& filename);
	virtual ~Mesh();

	void Draw();

private:
	void initModel(IndexedModel model);

	GLuint _vao;
	GLuint _vbo[vbo::NUM_BUFFERS];
	unsigned int _drawCount;
};
#endif