#include "OpenGLShader.h"

#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdio.h>

/*
 * Method     : Class constructor.
 * Description: It will initialize the Shader with the path for the shaders files.
 * Param      : vertexShaderPath   - The path to the vertex shader code file.
 * Param      : fragmentShaderPath - The path to the fragment shader code file.
 */
OpenGLShader::OpenGLShader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath) {
	validateParameter(vertexShaderPath, "vertexShaderPath");
	validateParameter(fragmentShaderPath, "fragmentShaderPath");
	linkProgram(vertexShaderPath, fragmentShaderPath);
}

const GLchar* OpenGLShader::readShader(const GLchar * shaderPath) {
	ifstream shaderFile;

	// Ensure ifstream can throw exceptions.
	shaderFile.exceptions(ifstream::failbit | ifstream::badbit);

	try {
		// Read the stream buffer and return its string
		shaderFile.open(shaderPath);
		stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();	
		shaderFile.close();
		return shaderStream.str().c_str();
	}
	catch (ifstream::failure fail) {
		cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << endl;
	}

	return "";
}

GLuint OpenGLShader::compileShader(const GLchar* code, GLenum type) {
	const GLchar* shaderName = (type == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT";
	GLint success;
	GLchar infoLog[512];
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &code, nullptr);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		cout << "ERROR::SHADER::" << shaderName << "::COMPILATION_FAILURE\n" << infoLog << endl;
	}

	return shader;
}

void OpenGLShader::linkProgram(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath) {
	GLint success;
	GLchar infoLog[512];
	GLuint vertexShader = compileShader(readShader(vertexShaderPath), GL_VERTEX_SHADER);
	GLuint fragmentShader = compileShader(readShader(fragmentShaderPath), GL_FRAGMENT_SHADER);

	// Create and link the shader program
	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, nullptr, infoLog);
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
	}

	// Delete already used the shaders.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void OpenGLShader::use() {
	if (0 != program) {
		glUseProgram(program);
	}
	else {
		throw logic_error("The Shader Program hasn't be created!");
	}
}

void OpenGLShader::validateParameter(const GLchar* shaderPath, const GLchar* parameterName) {
	const GLuint size = 64;
	GLchar errorMsg[size];
	sprintf_s(errorMsg, size, "The '%s' argument cannot be NULL!", parameterName);
	
	if (nullptr == shaderPath) {
		throw invalid_argument(errorMsg);
	}
}
