#ifndef JOINT_H
#define JOINT_H

#include <glm\glm.hpp>
#include <vector>
#include <memory>

class Joint : public std::enable_shared_from_this<Joint>
{
public:
	inline glm::mat4					getTransform() { return _jointTransform; }
	inline void							setTransform(glm::mat4 transform) { _jointTransform = transform; }
	inline void							setName(std::string name) { _name = name; }
	inline std::string					getName() { return _name; }
	std::vector<std::shared_ptr<Joint>>	getChildren() { return _children; }
	void								addChild(std::shared_ptr<Joint> j) { _children.push_back(j); }

	Joint() {}

	std::shared_ptr<Joint> Find(const std::string& name)
	{
		if (_name == name) return shared_from_this();
		for (auto joint : _children)
		{
			std::shared_ptr<Joint> j = joint->Find(name);
			if (j != nullptr) return j;
		}
		return nullptr;
	}

private:
	glm::mat4 _jointTransform;
	std::vector<std::shared_ptr<Joint>> _children;
	std::string _name;
};

#endif

#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "Mesh.h"
#include "..\Animator\Transform.h"
#include "..\Render\Camera.h"
#include "..\Render\AnimationShader.h"
#include "..\Animator\Animator.h"
#include "Texture.h"
#include <memory>


class Model : public std::enable_shared_from_this<Model>
{
public:

	Model();
	virtual ~Model() {}

	void LoadModel(const std::string& filename);
	void LoadJointHierarchy(json root);

	void InitJointHierarchy(std::shared_ptr<Joint> root, const glm::mat4 &parentTransform);
	void UpdateMeshBone(std::string jointName, const glm::mat4& globalTransform);

	void Update(double elapsedTime);

	void Draw(Transform position, Camera camera);

	std::shared_ptr<Animator> getAnimator() { return _animator; }
	std::shared_ptr<Joint> getRootJoint() { return _rootJoint; }

	std::shared_ptr<Joint> FindJoint(const std::string& jointName);

private:
	AnimationShader						_shader;
	glm::mat4							_inverseModelMatrix;

	std::vector<std::shared_ptr<Mesh>>	_meshes;
	std::shared_ptr<Texture>			_texture;
	std::shared_ptr<Joint>				_rootJoint;
	std::shared_ptr<Animator>			_animator;

	std::shared_ptr<Joint>				LoadJoint(json joint);
};
#endif