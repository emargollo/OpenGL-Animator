#ifndef VERTEX_H
#define VERTEX_H

#include "glm\glm.hpp"

class Vertex 
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord) 
	{ 
		this->pos = pos; 
		this->texCoord = texCoord; 
	}
	inline glm::vec3* GetPos() { return &pos; }
	inline glm::vec2* GetTexCoord() { return &texCoord; }
private:
	glm::vec3 pos;
	glm::vec2 texCoord;
};
#endif

namespace vbo {
	enum MeshBufferPositions {
		POSITION,
		TEX_COORD,
		INDEX
	};
}

#ifndef MESH_H
#define MESH_H

#include <GL\glew.h>

class Mesh 
{
public:
	Mesh(Vertex* vertices, unsigned int nVertices);
	virtual ~Mesh();

	void Draw();

private:
	static const unsigned int NUM_BUFFERS = 4;

	GLuint _vao;
	GLuint _vbo[NUM_BUFFERS];
	unsigned int _drawCount;
};
#endif