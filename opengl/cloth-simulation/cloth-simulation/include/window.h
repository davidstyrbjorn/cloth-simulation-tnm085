#pragma once

// GLFW
#include"GLFW/glfw3.h"

// GLM
#include"glm/vec2.hpp"
#include"glm/vec4.hpp"

class Window {	
public:
	Window();
	Window(int x, int y);

	void Clear(glm::vec4 Color);
	bool IsOpen();
	void Display();

private:
	glm::vec2 windowSize;
	GLFWwindow* glfwWindow; // test
};