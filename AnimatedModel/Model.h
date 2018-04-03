#ifndef JOINT_H
#define JOINT_H

#include <glm\glm.hpp>
#include <vector>

class Joint
{
public:
	inline glm::mat4	getTransform() { return _jointTransform; }
	inline void			setTransform(glm::mat4 transform) { _jointTransform = transform; }
	inline void			setName(std::string name) { _name = name; }
	inline std::string	getName() { return _name; }
	std::vector<Joint>	getChildren() { return _children; }
	void				addChild(Joint j) { _children.push_back(j); }

private:
	glm::mat4 _jointTransform;
	std::vector<Joint> _children;
	std::string _name;
};

#endif

#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "Mesh.h"
#include "..\Animation\Transform.h"
#include "..\Camera\Camera.h"
#include "AnimationShader.h"


class Model
{
public:

	Model();
	virtual ~Model() {}

	void LoadModel(const std::string& filename);
	void LoadJointHierarchy(json root);

	void InitJointHierarchy(Joint root, const glm::mat4 &parentTransform);
	void UpdateMeshBone(std::string jointName, const glm::mat4& globalTransform);

	void Draw(Transform position, Camera camera);

	std::vector<Mesh>	_meshes;
private:
	glm::mat4			_inverseModelMatrix;
	Joint				_rootJoint;
	AnimationShader		_shader;

	Joint				LoadJoint(json joint);

};

#endif