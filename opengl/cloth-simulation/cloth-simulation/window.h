#pragma once
#define GLEW_STATIC
#include "../third_party/glew/include/GL/glew.h"
#include "../third_party/glm/glm/glm.hpp"
#include "../third_party/glfw/include/GLFW/glfw3.h"


class Window {
public:
	glm::vec2 windowSize;
	GLFWwindow* glfwWindow;
	
	Window();
	Window(int x, int y);

	void Clear(glm::vec4 Color);
	bool IsOpen();
	void Display();
};
