#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <memory>
#include <unordered_map>
#include "Animation.h"
class Model;
class Joint;

class Animator
{
public:
	Animator(Model* model);

	void startAnimation(const std::string& animationName);
	void addAnimation(const json& jsonAnimation);
	void Update(double elapsedTime);

private:
	Model* _model;
	std::vector<std::shared_ptr<Animation>> _animations;
	std::shared_ptr<Animation> _currentAnimation;
	double _animationTime;

	std::unordered_map<std::string, glm::mat4> CalculateJointTransforms();

	glm::vec3 GetInterpolatedPos(std::pair<double, glm::vec3> start, std::pair<double, glm::vec3> end);
	glm::quat GetInterpolatedRot(std::pair<double, glm::quat> start, std::pair<double, glm::quat> end);
	glm::vec3 GetInterpolatedScale(std::pair<double, glm::vec3> start, std::pair<double, glm::vec3> end);

};

#endif