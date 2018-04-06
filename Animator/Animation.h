#ifndef JOINT_ANIM_H
#define JOINT_ANIM_H

#include <map>
#include <glm\glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm\gtx\quaternion.hpp>
#include <glm\gtx\transform.hpp>

struct JointAnim
{
	std::string _name;
	std::map<double, glm::vec3> _positionKeys;
	std::map<double, glm::quat> _rotationKeys;
	std::map<double, glm::vec3> _scallingKeys;
};

#endif

#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <nlohmann\json.hpp>

using json = nlohmann::json;

class Animation
{
public:

	Animation(const json& jsonObj);
	virtual ~Animation() {}

	inline std::string getName() { return _name; }
	inline double getDuration() { return _duration; }
	inline std::vector<JointAnim> getJointAnims() { return _jointAnims; }

private:
	std::string _name;
	double _duration = 0;
	std::vector<JointAnim> _jointAnims;
};

#endif