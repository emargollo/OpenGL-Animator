#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL\glew.h>
#include "..\Animator\Transform.h"
#include "Camera.h"

class BaseShader
{
public:
	virtual void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	virtual std::string LoadShader(const std::string& filename);
	virtual GLuint CreateShader(const std::string& text, GLenum shaderType);
};

class Shader : public BaseShader
{
public:
	Shader(const std::string& filename);
	virtual ~Shader();

	void Update(const Transform& transform, const Camera& camera);
	void Bind();

private:
	static const unsigned int NUM_SHADERS = 2;

	enum
	{
		TRANSFORM_U,
		VIEW_PROJECTION_U,

		NUM_UNIFORMS
	};

	GLuint _program;
	GLuint _uniforms[NUM_UNIFORMS];
	GLuint _shaders[NUM_SHADERS];


};

#endif