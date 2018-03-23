#include "Mesh.h"
#include <vector>
#include <iostream>

Mesh::Mesh(Vertex* vertices, unsigned int nVertices)
{
	_drawCount = nVertices;

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texcoords;

	positions.reserve(nVertices);
	texcoords.reserve(nVertices);

	for (unsigned int i = 0; i < nVertices; ++i)
	{
		positions.push_back(*vertices[i].GetPos());
		texcoords.push_back(*(vertices[i].GetTexCoord()));
	}

	glGenBuffers(NUM_BUFFERS, _vbo);
	
	//Position
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[vbo::POSITION]);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), &positions.front(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Texture Coordinates
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[vbo::TEX_COORD]);
	glBufferData(GL_ARRAY_BUFFER, texcoords.size() * sizeof(glm::vec2), &texcoords.front(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &_vao);
}

void Mesh::Draw()
{
	glBindVertexArray(_vao);

	glDrawArrays(GL_TRIANGLES, 0, _drawCount);

	glBindVertexArray(0);
}
