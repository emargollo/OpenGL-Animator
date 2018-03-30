#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL\glew.h>
#include "..\Animation\Transform.h"
#include "..\Camera\Camera.h"

class Shader
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