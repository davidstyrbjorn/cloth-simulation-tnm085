#pragma once

#include <iostream>
#include<vector>

// Forward Decleration
class GLFWwindow;

// GLM
#include"glm/vec2.hpp"
#include"glm/vec4.hpp"

#include"input.h"

class Window {	
public:
	//Creates Window for rendering
	Window(int x = 640, int y = 480, std::string title = "Cloth Simulation");
	~Window();

	void Clear(glm::vec4 Color);
	bool IsOpen();
	void Display();
	std::vector<Event>& GetPolledEvents();
	glm::vec2 GetRelativeMousePosition();
	bool IsKeyDown(int keycode);

	// Static GLFW error callback
	static void error_callback(int error, const char* description);

	// Static GLFW Input Callbacks
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void character_callback(GLFWwindow* window, unsigned int codepoint);
	static void window_size_callback(GLFWwindow* window, int width, int height);

private:
	glm::vec2 windowSize;
	GLFWwindow* glfwWindow; // test
	std::vector<Event> eventList;
	bool keys[1028];
};