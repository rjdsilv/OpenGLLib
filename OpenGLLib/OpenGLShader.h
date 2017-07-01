#ifndef _OPENGL_SHADER_H_
#define _OPENGL_SHADER_H_

#pragma once

#include <glad/glad.h>
#include <string>

using namespace std;

/*
* Class      : OpenGLShader
* Description: This class will be able the read shaders from the disk and make the shader ready for use.
* Author     : Rodrigo Januario da Silva
* Version    : 1.0.0
*/
class OpenGLShader {
protected:
	GLuint program;

private:
	void validateParameter(const GLchar* shaderPath, const GLchar* parameterName);
	const GLchar* readShader(const GLchar* shaderPath);
	GLuint compileShader(const GLchar* code, GLenum type);
	void linkProgram(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath);

public:
	// Constructors.
	OpenGLShader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath);

	// Methods.
	void use();
};

#endif
