#pragma once
#include "libs.h"
#include "Window.h"
#include <cmath>

glm::vec2 Window::Size;
glm::vec2 Window::Viewport(0);
double Window::Viewscale(1.0);

Window* Window::Instance;

//----------------------------------BASE------------------------------
void Window::Init(std::string name, glm::vec2 size) {
	if (!Instance)
		Instance = new Window(name, size);
	else
		throw "CANNOT INIT SINGLETON WINDOW TWICE";
}

Window* Window::getInstance() {
	return Instance;
}

Window::Window(std::string name, glm::vec2 size) {

	//set pre option for the window
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//make window
	GLFWwindow* window = glfwCreateWindow(size.x, size.y, name.c_str(), NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize_callback);

	//make context
	glfwMakeContextCurrent(window);


	//init glew
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		throw "FAILED TO INIT GLEW";
		return;
	}

	//enable options
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//normal mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	//set callbacks
	glfwSetKeyCallback(window, key_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetCursorPosCallback(window, cursor_callback);


	//set class vars from local
	Size = size;
	WindowID = window;

}

void Window::DestroyWindow() { //ensure Window is properly cleaned up;
	delete Window::Instance;
}

Window::~Window() {
	//clean up in glfw
	glfwDestroyWindow(WindowID);
	glfwTerminate();
}


//---------------------------------------CALLBACKS----------------------------------
void Window::resize_callback(GLFWwindow* window, int framebufferWidth, int framebufferHight) {

	//update graphics window size
	glViewport(0, 0, framebufferWidth, framebufferHight);

	//update size and size scaler
	Size = glm::vec2(framebufferWidth, framebufferHight);
}

void Window::key_callback(GLFWwindow* window, int button, int scanmode, int action, int mods) {
	//close window on esc 
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Window::scroll_callback(GLFWwindow* window, double x_scroll, double y_scroll) {
	Viewscale *= pow(1.05, y_scroll);
}

glm::vec2 last_pos;
void Window::cursor_callback(GLFWwindow* window, double x, double y) {

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
		
		glm::vec2 current_pos = glm::vec2(x, -y);

		if (last_pos != glm::vec2(0)) {
			Viewport += (current_pos - last_pos);
		}

		last_pos = current_pos;
	}
	else {
		last_pos = glm::vec2(0);
	}

}


//----------------------------------------GETS---------------------------------
GLFWwindow* Window::getID() {
	return WindowID;
}

glm::vec2 Window::getSize() {
	return Size;
}

double Window::getViewscale() {
	return Viewscale;
}

glm::vec2 Window::getViewport() {
	return Viewport;
}