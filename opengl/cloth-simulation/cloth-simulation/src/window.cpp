#include"../include/window.h"

#include<iostream>

#define GLEW_STATIC
#include<GL/glew.h>

#include<GLFW/glfw3.h>

#include"../include/input.h"

Window::Window(int x, int y, std::string title) : windowSize(x, y)
{
	
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
	{
		std::cout << "Någe gick tame fan fel!" << std::endl;
	}
	
	//Creates window
	glfwWindow = glfwCreateWindow(windowSize.x, windowSize.y, title.c_str() , NULL, NULL);
	glfwMakeContextCurrent(glfwWindow);
	
	// Initalize glew now that a opengl context is created
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to Initalize GLEW, OpenGL will not work" << std::endl;
	}

	// Set the window user pointer, mainly so the Input class can use it
	glfwSetWindowUserPointer(glfwWindow, this);

	// Input callbacks
	glfwSetKeyCallback(glfwWindow, key_callback);
	glfwSetMouseButtonCallback(glfwWindow, mouse_button_callback);
	glfwSetScrollCallback(glfwWindow, scroll_callback);
	glfwSetCharCallback(glfwWindow, character_callback);
	glfwSetWindowSizeCallback(glfwWindow, window_size_callback);

	if (!glfwWindow)
	{
		std::cout << "Hörre du du, nu ville fönstret cke fungera :'(" << std::endl;
	}
}

Window::~Window()
{
	glfwDestroyWindow(glfwWindow);
	glfwTerminate();
}


void Window::Clear(glm::vec4 Color)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(Color.r, Color.g, Color.b, Color.a); // set the color
}

void Window::Display()
{
	eventList.clear();
	glfwPollEvents();
	glfwSwapBuffers(glfwWindow);
}

std::vector<Event>& Window::GetPolledEvents()
{
	return eventList;
}


bool Window::IsOpen()
{
	return !glfwWindowShouldClose(glfwWindow);
}

void Window::error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: €s\n", description);
}


void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Check for the viable event types we support
	if (action == GLFW_PRESS || action == GLFW_RELEASE) {
		Event e;
		e.key = key;
		e.type = action == GLFW_PRESS ? EventType::key_down : EventType::key_released;

		// Add the event
		Window* temp = static_cast<Window*>(glfwGetWindowUserPointer(window));
		temp->GetPolledEvents().push_back(e);
	}
}

void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	// Check for the viable event types we support
	if (action == GLFW_PRESS || action == GLFW_RELEASE) {
		Event e;
		e.button = button;
		e.type = action == GLFW_PRESS ? EventType::mouse_down : EventType::mouse_released;

		// Add the event
		Window* temp = static_cast<Window*>(glfwGetWindowUserPointer(window));
		temp->GetPolledEvents().push_back(e);
	}
}

void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	// Do nothing
}

void Window::character_callback(GLFWwindow* window, unsigned int codepoint)
{
	// Do nothing
}

void Window::window_size_callback(GLFWwindow* window, int width, int height)
{
	Event e;
	e.type = EventType::window_resized;
	e.size = { width, height };

	// Add the event
	Window* temp = static_cast<Window*>(glfwGetWindowUserPointer(window));
	temp->GetPolledEvents().push_back(e);
}
