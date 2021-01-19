#ifndef WINDOW_H
#define WINDOW_H
#include "glm.hpp"
#include "glfw3.h"
#include <string>

class Window {

public:
	//singleton setup
	static void Init(std::string name, glm::vec2 size);
	static Window* getInstance();
	static void DestroyWindow();
	virtual ~Window();

	//get functions
	glm::vec2 getSize();
	GLFWwindow* getID();
	double getViewscale();
	glm::vec2 getViewport();


private:
	//private init
	Window(std::string name, glm::vec2 size);

	//callbacks
	static void resize_callback(GLFWwindow* window, int framebufferWidth, int framebufferHight);
	static void key_callback(GLFWwindow* window, int key, int scanmode, int action, int mods);
	static void cursor_callback(GLFWwindow* window, double x, double y);
	static void scroll_callback(GLFWwindow* window, double x_scroll, double y_scroll);

	//private vars
	static glm::vec2 Viewport;
	static double Viewscale;
	static glm::vec2 Size;

	//window identifiers
	static Window *Instance;
	GLFWwindow *WindowID;

};


#endif