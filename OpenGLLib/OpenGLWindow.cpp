#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "OpenGLWindow.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

/*
 * Method     : Class Constructor.
 * Description: It will initialize GLFW, create a GLFW Window and prepare it for use.
 * Param      : width  - The window with
 * Param      : height - The window height
 */
OpenGLWindow::OpenGLWindow(const GLint majorVersion, const GLint minorVersion, const GLuint width, const GLuint height, const GLchar* title) {
	this->width = width;
	this->height = height;
	this->title = title;

	// Initializing GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Creates the OpenGL Window.
	this->window = glfwCreateWindow(this->width, this->height, this->title, nullptr, nullptr);
	if (nullptr == this->window) {	
		terminate(OPENGL_ERR_CREATE_WINDOW, "Failed to create GLFW window");
	}
	glfwMakeContextCurrent(this->window);
	glfwSetFramebufferSizeCallback(this->window, framebufferSizeCallback);

	// Initializing GLAD.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		terminate(OPENGL_ERR_INIT_GLAD, "Failed to initialize GLAD");
	}
}

OpenGLWindow::~OpenGLWindow() {	
	terminate(OPENGL_OK, "");
}

bool OpenGLWindow::shouldClose() {
	if (nullptr != window) {
		return glfwWindowShouldClose(window) != 0;
	}

	return true;
}

void OpenGLWindow::swapBuffersAndPoolEvents() {
	glfwSwapBuffers(this->window);
	glfwPollEvents();
}

void OpenGLWindow::terminate(GLint code, const char* message) {
	cout << message << endl;
	glfwTerminate();
	exit(code);
}