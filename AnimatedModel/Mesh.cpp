#include "Mesh.h"
#include <vector>
#include <iostream>

Mesh::Mesh(const json & jsonObj)
{
	//create local variables to load json into
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;
	std::vector<glm::uvec4> jointIds;
	std::vector<glm::vec4> jointWeights;
	std::vector<unsigned int> indices;

	//Load indices array into vector
	indices = jsonObj["indices"].get<std::vector<unsigned int>>();

	//load each vertex data into each vector
	for (json vertex : jsonObj["vertices"]) 
	{
		glm::vec3 pos(vertex["pos"]["x"], vertex["pos"]["y"], vertex["pos"]["z"]);
		glm::vec2 texcoord(vertex["texcoord"]["x"], vertex["texcoord"]["y"]);
		glm::vec3 normal(vertex["normal"]["x"], vertex["normal"]["y"], vertex["normal"]["z"]);
		glm::uvec4 jointId(0);
		glm::vec4 jointWeight(0);

		for (unsigned int i = 0; i < vertex["joints"].size(); ++i)
		{
			json joint = vertex["joints"][i];
			switch (i)
			{
			case 0:
				jointId.x = joint["id"];
				jointWeight.x = joint["weight"];
				break;
			case 1:
				jointId.y = joint["id"];
				jointWeight.y = joint["weight"];
				break;
			case 2:
				jointId.z = joint["id"];
				jointWeight.z = joint["weight"];
				break;
			case 3:
				jointId.w = joint["id"];
				jointWeight.w = joint["weight"];
				break;
			default:
				std::cerr << "Too many joints, this shouldn't happen!";
			}
		}

		positions.push_back(pos);
		texCoords.push_back(texcoord);
		normals.push_back(normal);
		jointIds.push_back(jointId);
		jointWeights.push_back(jointWeight);
	}

	//load each bone data into two unordered maps to be used when needed to load 
	for (json bone : jsonObj["bones"])
	{
		BoneData data;

		glm::vec3 pos(bone["pos"]["x"], bone["pos"]["y"], bone["pos"]["z"]);
		glm::quat rot(bone["rot"]["w"], bone["rot"]["x"], bone["rot"]["y"], bone["rot"]["z"]);
		glm::vec3 scale(bone["scale"]["x"], bone["scale"]["y"], bone["scale"]["z"]);

		glm::mat4 offset = glm::translate(pos) * glm::toMat4(rot) * glm::scale(scale);

		unsigned int id = bone["id"].get<unsigned int>();
		std::string name = bone["name"].get<std::string>();

		data.offsetMatrix = offset;

		_boneIdMap.insert(std::make_pair(name, id));
		_boneDataMap.insert(std::make_pair(id, data));
	}


	_drawCount = indices.size();

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(NUM_BUFFERS, _vbo);

	//Position
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[POSITION]);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Texture Coordinates
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[TEX_COORD]);
	glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//Normals
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[NORMAL]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(normals[0]), &normals[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Joint Ids
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[JOINT_IDS]);
	glBufferData(GL_ARRAY_BUFFER, jointIds.size() * sizeof(glm::uvec4), &jointIds.front(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(3);
	glVertexAttribIPointer(3, 4, GL_UNSIGNED_INT, 0, 0);

	//Joint Weights
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[JOINT_WEIGHTS]);
	glBufferData(GL_ARRAY_BUFFER, jointWeights.size() * sizeof(glm::vec4), &jointWeights.front(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 0, 0);

	//Indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo[INDEX]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);

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

std::vector<glm::mat4> Mesh::GetBoneArray()
{
	std::vector<glm::mat4> boneArray;

	boneArray.assign(_boneDataMap.size(), glm::mat4());
	for (auto i : _boneDataMap)
	{
		boneArray[i.first] = i.second.finalTransformation;
	}

	return boneArray;
}