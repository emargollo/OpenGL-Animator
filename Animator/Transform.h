#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm\glm.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm\gtx\transform.hpp>
#include <glm\gtx\quaternion.hpp>

class Transform
{
public:
	//Transform(const glm::vec3& pos = glm::vec3(), 
	//		  const glm::quat& rot = glm::quat(),
	//		  const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
	//{
	//	_pos = pos;
	//	_rot = rot;
	//	_scale = scale;
	//}

	Transform(const glm::vec3& pos = glm::vec3(),
		const glm::vec3& rot = glm::vec3(),
		const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
	{
		_pos = pos;
		_rot = glm::quat(rot);
		_scale = scale;
	}

	inline glm::mat4 getModel() const 
	{
		glm::mat4 posMat = glm::translate(_pos);
		glm::mat4 rotMat = glm::toMat4(_rot);
		glm::mat4 scaleMat = glm::scale(_scale);

		return posMat * rotMat * scaleMat;
	}

	inline glm::vec3& GetPos() { return _pos; }
	inline glm::quat& GetRot() { return _rot; }
	inline glm::vec3& GetScale() { return _scale; }

	inline void SetPos(const glm::vec3& pos) { _pos = pos; }
	inline void SetRot(const glm::quat& rot) { _rot = rot; }
	inline void SetScale(const glm::vec3& scale) { _scale = scale; }

private:
	glm::vec3 _pos;
	glm::quat _rot;
	glm::vec3 _scale;
};

#endif