#include "window.h"

Window::Window()
{
	windowSize = glm::vec2(640, 420);
	glfwWindow = glfwCreateWindow(640, 420, "Window", NULL, NULL);
}


Window::Window(int x, int y)
{
	windowSize = glm::vec2(x, y);
	glfwWindow = glfwCreateWindow(x, y, "Window", NULL, NULL);
}
