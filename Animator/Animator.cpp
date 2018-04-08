#include "Animator.h"
#include "..\AnimatedModel\Model.h"
#include <iostream>

Animator::Animator(Model *model)
{
	_model = model;
}

void Animator::startAnimation(const std::string & animationName)
{
	for (auto animation : _animations)
	{
		if (animation->getName() == animationName)
		{
			_animationTime = 0;
			_currentAnimation = animation;
		}
	}	
}

void Animator::addAnimation(const json & jsonAnimation)
{
	_animations.push_back(std::make_shared<Animation>(jsonAnimation));
}

void Animator::Update(double elapsedTime)
{
	if (_currentAnimation == nullptr) {
		return;
	}
	_animationTime += elapsedTime;
	if (_animationTime > _currentAnimation->getDuration()) _animationTime -= _currentAnimation->getDuration();

	std::unordered_map<std::string, glm::mat4> jointMap = CalculateJointTransforms();

	for (auto jointTransform : jointMap)
	{
		std::shared_ptr<Joint> joint = _model->FindJoint(jointTransform.first);
		if (joint != nullptr) joint->setTransform(jointTransform.second);
	}
	_model->InitJointHierarchy(_model->getRootJoint(), glm::scale(glm::vec3(1)));
}

std::unordered_map<std::string, glm::mat4> Animator::CalculateJointTransforms()
{
	std::unordered_map<std::string, glm::mat4> jointTransforms;
	for (auto jointKeys : _currentAnimation->getJointAnims())
	{
		//Using upper bound as it will never return the first value of a map.
		auto posNext = jointKeys._positionKeys.upper_bound(_animationTime);
		auto rotNext = jointKeys._rotationKeys.upper_bound(_animationTime);
		auto scaleNext = jointKeys._scallingKeys.upper_bound(_animationTime);

		if (posNext == jointKeys._positionKeys.end()) posNext--;
		if (rotNext == jointKeys._rotationKeys.end()) rotNext--;
		if (scaleNext == jointKeys._scallingKeys.end()) scaleNext--;

		glm::vec3 pos = GetInterpolatedPos(*(std::prev(posNext)), *posNext);
		glm::quat rot = GetInterpolatedRot(*(std::prev(rotNext)), *rotNext);
		glm::vec3 scale = GetInterpolatedScale(*(std::prev(scaleNext)), *scaleNext);

		glm::mat4 transform =  glm::translate(pos) * glm::toMat4(rot) * glm::scale(scale);

		jointTransforms.insert(std::make_pair(jointKeys._name, transform));
	}
	return jointTransforms;
}

glm::vec3 Animator::GetInterpolatedPos(std::pair<double, glm::vec3> start, std::pair<double, glm::vec3> end)
{
	double delta = end.first - start.first;
	double factor = (_animationTime - start.first) / delta;
	glm::vec3 deltaPos = end.second - start.second;
	glm::vec3 pos = start.second + (float)factor * deltaPos;
	return pos;
}

glm::quat Animator::GetInterpolatedRot(std::pair<double, glm::quat> start, std::pair<double, glm::quat> end)
{
	double delta = end.first - start.first;
	double factor = (_animationTime - start.first) / delta;
	glm::quat rot = slerp(start.second, end.second, (float)factor);
	return glm::normalize(rot);
}

//Adapted from wikipedia: https://en.wikipedia.org/wiki/Slerp#Source_code
glm::quat Animator::Slerp(glm::quat v0, glm::quat v1, float t) {
	// Only unit quaternions are valid rotations.
	// Normalize to avoid undefined behavior.
	v0 = glm::normalize(v0);
	v1 = glm::normalize(v1);

	// Compute the cosine of the angle between the two vectors.
	float dot = glm::dot(v0, v1);

	// If the dot product is negative, the quaternions
	// have opposite handed-ness and slerp won't take
	// the shorter path. Fix by reversing one quaternion.
	if (dot < 0.0f) {
		v1 = -v1;
		dot = -dot;
	}

	//const double DOT_THRESHOLD = 0.9995;
	//if (dot > DOT_THRESHOLD) {
	//	// If the inputs are too close for comfort, linearly interpolate
	//	// and normalize the result.

	//	glm::quat result = v0 + t * (v1 – v0);
	//	result = glm::normalize(result);
	//	return result;
	//}

	glm::clamp(dot, -1.0f, 1.0f);           // Robustness: Stay within domain of acos()
	float theta_0 = acos(dot);  // theta_0 = angle between input vectors
	float theta = theta_0 * t;    // theta = angle between v0 and result

	float s0 = cos(theta) - dot * sin(theta) / sin(theta_0);  // == sin(theta_0 - theta) / sin(theta_0)
	float s1 = sin(theta) / sin(theta_0);

	return (s0 * v0) + (s1 * v1);
}

glm::vec3 Animator::GetInterpolatedScale(std::pair<double, glm::vec3> start, std::pair<double, glm::vec3> end)
{
	double delta = end.first - start.first;
	double factor = (_animationTime - start.first) / delta;
	glm::vec3 deltaScale = end.second - start.second;
	glm::vec3 scale = start.second + (float)factor * deltaScale;
	return scale;
}
