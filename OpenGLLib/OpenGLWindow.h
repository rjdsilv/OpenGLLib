#ifndef _OPENGL_WINDOW_H_
#define _OPENGL_WINDOW_H_

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

/*
 * Class      : OpenGLWindow
 * Description: This class will be resposible for managing the game window using GLFW. It will be responsible
 *              for creating, destroying and managing the possible window events.
 * Author     : Rodrigo Januario da Silva
 * Version    : 1.0.0
 */
class OpenGLWindow {
private:
	GLuint width = 0;
	GLuint height = 0;
	GLFWwindow* window = nullptr;
	const GLchar* title = nullptr;

public:
	const GLint OPENGL_OK = 0;
	const GLint OPENGL_ERR_CREATE_WINDOW = -1;
	const GLint OPENGL_ERR_INIT_GLAD = 2;

private:
	void terminate(GLint errorCode, const char* message);

public:
	OpenGLWindow(const GLint majorVersion, const GLint minorVersion, const GLuint width, const GLuint height, const GLchar* title);
	~OpenGLWindow();
	bool shouldClose();
	void swapBuffersAndPoolEvents();
};

#endif