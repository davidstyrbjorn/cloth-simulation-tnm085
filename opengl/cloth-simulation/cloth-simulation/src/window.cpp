#include"../include/window.h"
#include<iostream>



Window::Window(int x, int y, std::string title) : windowSize(x,y)
{
	
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
	{
		std::cout << "Någe gick tame fan fel!" << std::endl;
	}
	
	//Creates window
	glfwWindow = glfwCreateWindow(windowSize.x, windowSize.y, title.c_str() , NULL, NULL);
	
	//Set Key Callback
	//"Kommer vara jättemånga sen" - davst420
	glfwSetKeyCallback(glfwWindow, key_callback);


	if (!glfwWindow)
	{
		std::cout << "Hörre du du, nu ville fönstret cke fungera :'(" << std::endl;
	}

	glfwMakeContextCurrent(glfwWindow);

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
	glfwSwapBuffers(glfwWindow);
	glfwPollEvents();
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
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}