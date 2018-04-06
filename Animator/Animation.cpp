#include "Animation.h"

Animation::Animation(const json & jsonObj)
{
	_name = jsonObj["name"].get<std::string>();
	_duration = jsonObj["duration"].get<double>();

	for (json bone : jsonObj["bones"])
	{
		JointAnim jAnim;
		jAnim._name = bone["name"].get<std::string>();

		for (json posKey : bone["pos_keys"])
		{
			glm::vec3 pos(posKey["x"], posKey["y"], posKey["z"]);
			double time = posKey["time"];
			jAnim._positionKeys.insert(std::make_pair(time, pos));
		}
		for (json rotKey : bone["rot_keys"])
		{
			glm::quat rot(rotKey["w"], rotKey["x"], rotKey["y"], rotKey["z"]);
			double time = rotKey["time"];
			jAnim._rotationKeys.insert(std::make_pair(time, rot));
		}
		for (json scaleKey : bone["scale_keys"])
		{
			glm::vec3 scale(scaleKey["x"], scaleKey["y"], scaleKey["z"]);
			double time = scaleKey["time"];
			jAnim._scallingKeys.insert(std::make_pair(time, scale));
		}

		_jointAnims.push_back(jAnim);
	}
}
