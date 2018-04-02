#ifndef ANIMATION_SHADER_H
#define ANIMATION_SHADER_H

#include <string>
#include <GL\glew.h>
#include <vector>
#include <glm\glm.hpp>
#include "..\Animation\Transform.h"
#include "..\Camera\Camera.h"
#include "Shader.h"

static const unsigned int MAX_JOINTS = 50;

class AnimationShader : public BaseShader
{
public:
	AnimationShader(const std::string& filename);
	virtual ~AnimationShader();

	void Update(const Transform& transform, const Camera& camera, glm::mat4 jointTransforms[MAX_JOINTS]);
	void Bind();

private:
	static const unsigned int NUM_SHADERS = 2;

	enum
	{
		TRANSFORM_U,
		VIEW_PROJECTION_U,
		JOINT_TRANSFORMS_U,

		NUM_UNIFORMS
	};

	GLuint _program;
	GLuint _uniforms[NUM_UNIFORMS];
	GLuint _shaders[NUM_SHADERS];


};

#endif