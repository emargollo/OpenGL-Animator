#include "Mesh.h"
#include <vector>
#include <iostream>

Mesh::Mesh(Vertex* vertices, unsigned int nVertices, unsigned int *indices, unsigned int nIndices)
{
	IndexedModel model;
	for (unsigned int i = 0; i < nVertices; ++i)
	{
		model.positions.push_back(*vertices[i].GetPos());
		model.texCoords.push_back(*(vertices[i].GetTexCoord()));
		model.normals.push_back(*(vertices[i].GetNormal()));
	}

	for (unsigned int i = 0; i < nIndices; ++i) 
	{
		model.indices.push_back(indices[i]);
	}

	initModel(model);
}

Mesh::Mesh(const std::string & filename)
{
	IndexedModel model = OBJModel(filename).ToIndexedModel();
	initModel(model);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &_vao);
}

void Mesh::Draw()
{
	glBindVertexArray(_vao);

	//glDrawArrays(GL_TRIANGLES, 0, _drawCount);
	glDrawElements(GL_TRIANGLES, _drawCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void Mesh::initModel(IndexedModel model)
{
	_drawCount = model.indices.size();

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(vbo::NUM_BUFFERS, _vbo);

	//Position
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[vbo::POSITION]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(glm::vec3), &model.positions.front(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Texture Coordinates
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[vbo::TEX_COORD]);
	glBufferData(GL_ARRAY_BUFFER, model.texCoords.size() * sizeof(glm::vec2), &model.texCoords.front(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//Normals
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[vbo::NORMAL]);
	glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(glm::vec3), &model.normals.front(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo[vbo::INDEX]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}
