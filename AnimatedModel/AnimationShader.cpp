#include "AnimationShader.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>

AnimationShader::AnimationShader(const std::string& filename)
{
	_program = glCreateProgram();
	_shaders[0] = CreateShader(LoadShader(filename + ".glvs"), GL_VERTEX_SHADER);
	_shaders[1] = CreateShader(LoadShader(filename + ".glfs"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; ++i) 
	{
		glAttachShader(_program, _shaders[i]);
	}

	glBindAttribLocation(_program, 0, "position");
	glBindAttribLocation(_program, 1, "texCoord");
	glBindAttribLocation(_program, 2, "normal");
	glBindAttribLocation(_program, 3, "jointIds");
	glBindAttribLocation(_program, 4, "jointWeights");

	glLinkProgram(_program);
	CheckShaderError(_program, GL_LINK_STATUS, true, "Error: Program linking failed. ");

	glValidateProgram(_program);
	CheckShaderError(_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid. ");

	_uniforms[TRANSFORM_U] = glGetUniformLocation(_program, "transform");
	_uniforms[VIEW_PROJECTION_U] = glGetUniformLocation(_program, "viewProjection");
	_uniforms[JOINT_TRANSFORMS_U] = glGetUniformLocation(_program, "jointTransforms");
}

void AnimationShader::Update(const Transform & transform, const Camera& camera, std::vector<glm::mat4> jointVector)
{
	glm::mat4 model = transform.getModel();
	glm::mat4 viewProjection = camera.GetViewProjection();
	glm::mat4 jointTransforms[MAX_JOINTS];
	for (unsigned int i = 0; i < (jointVector.size() < MAX_JOINTS ? jointVector.size() : MAX_JOINTS); ++i)
	{
		jointTransforms[i] = jointVector[i];
	}

	glUniformMatrix4fv(_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(_uniforms[VIEW_PROJECTION_U], 1, GL_FALSE, &viewProjection[0][0]);
	glUniformMatrix4fv(_uniforms[VIEW_PROJECTION_U], MAX_JOINTS, GL_FALSE, glm::value_ptr(jointTransforms[0]));

	/*for (unsigned int i = 0; i < jointTransforms.size(); ++i)
	{
		std::string s = "jointTransforms[" + std::to_string(i) + "]";
		GLuint uniform = glGetUniformLocation(_program, s.c_str());

	}*/

}

void AnimationShader::Bind()
{
	for (unsigned int i = 0; i < NUM_SHADERS; ++i)
	{
		glDetachShader(_program, _shaders[i]);
		glDeleteShader(_shaders[i]);
	}
	glUseProgram(_program);
}

AnimationShader::~AnimationShader()
{
	glDeleteProgram(_program);
}