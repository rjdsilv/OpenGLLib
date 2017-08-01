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
public:
	const GLint SHADER_INVALID_PROGRAM = 0;
	const GLint SHADER_INVALID_UNIFORM = -1;

protected:
	GLuint program = SHADER_INVALID_PROGRAM;

private:
	void validateParameter(const GLchar* shaderPath, const GLchar* parameterName);
	string readShader(const GLchar* shaderPath, stringstream& shaderStream);
	GLuint compileShader(string& code, GLenum type);
	void linkProgram(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath);
	bool isProgramInvalid();

public:
	// Constructors.
	OpenGLShader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath);

	// Methods.
	void use();
	GLint getUniform(const GLchar* name);
};

#endif
