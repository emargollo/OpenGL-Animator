#include "Model.h"
#include <fstream>
#include "nlohmann\json.hpp"
#include "Texture.h"
#include <iostream>

using json = nlohmann::json;

Model::Model() : _shader(".\\res\\animationShader")
{
}

void Model::LoadModel(const std::string & filename)
{
	json model;
	std::ifstream file(filename);
	file >> model;
	file.close();

	for (json jsonMesh : model["meshes"])
	{
		_meshes.push_back(std::make_shared<Mesh>(jsonMesh));
	}
	LoadJointHierarchy(model["rootnode"]);

	InitJointHierarchy(_rootJoint, glm::scale(glm::vec3(1)));
}

void Model::LoadJointHierarchy(json root)
{
	glm::vec3 pos(root["pos"]["x"], root["pos"]["y"], root["pos"]["z"]);
	glm::quat rot(root["rot"]["w"], root["rot"]["x"], root["rot"]["y"], root["rot"]["z"]);
	glm::vec3 scale(root["scale"]["x"], root["scale"]["y"], root["scale"]["z"]);

	glm::mat4 modelMatrix = glm::translate(pos) * glm::toMat4(rot) * glm::scale(scale);

	_inverseModelMatrix = glm::inverse(modelMatrix);

	_rootJoint.setTransform(modelMatrix);
	_rootJoint.setName(root["name"]);
	for (json child : root["children"])
	{
		_rootJoint.addChild(LoadJoint(child));
	}
}

Joint Model::LoadJoint(json joint)
{
	Joint j;

	glm::vec3 pos(joint["pos"]["x"], joint["pos"]["y"], joint["pos"]["z"]);
	glm::quat rot(joint["rot"]["w"], joint["rot"]["x"], joint["rot"]["y"], joint["rot"]["z"]);
	glm::vec3 scale(joint["scale"]["x"], joint["scale"]["y"], joint["scale"]["z"]);

	glm::mat4 jointMatrix = glm::translate(pos) * glm::toMat4(rot) * glm::scale(scale);

	j.setTransform(jointMatrix);
	j.setName(joint["name"]);

	for (json child : joint["children"])
	{
		j.addChild(LoadJoint(child));
	}

	return j;
}

void Model::InitJointHierarchy(Joint root, const glm::mat4 & parentTransform)
{
	glm::mat4 globalTransform = parentTransform * root.getTransform();

	//Insert configure bones final transforms for each mesh
	UpdateMeshBone(root.getName(), globalTransform);

	for (Joint j : root.getChildren())
	{
		InitJointHierarchy(j, globalTransform);
	}
}

void Model::UpdateMeshBone(std::string jointName, const glm::mat4 & globalTransform)
{
	for (auto mesh : _meshes)
	{
		if (mesh->_boneIdMap.find(jointName) == mesh->_boneIdMap.end()) continue;
		unsigned int id = mesh->_boneIdMap[jointName];
		mesh->_boneDataMap[id].finalTransformation = _inverseModelMatrix * globalTransform * mesh->_boneDataMap[id].offsetMatrix;
	}
}

void Model::Draw(Transform position, Camera camera)
{
	_shader.Bind();
	for (auto mesh : _meshes)
	{
		_shader.Update(position, camera, mesh->GetBoneArray());
		mesh->Draw();
	}
}

