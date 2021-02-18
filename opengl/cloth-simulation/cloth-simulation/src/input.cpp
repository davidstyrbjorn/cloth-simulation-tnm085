#include "..\include\input.h"

#include<GLFW/glfw3.h>

#include"../include/window.h"

#define OR ||

std::vector<Event>& Input::GetPolledEvents()
{
	return eventList;
}

void Input::PollEvents()
{
	eventList.clear();
	glfwPollEvents();
}

void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS OR action == GLFW_RELEASE) {
		Event e;
		e.key = key;
		e.type = action == GLFW_PRESS ? EventType::key_down : EventType::key_released;
	}
}

void Input::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS OR action == GLFW_RELEASE) {
		Event e;
		e.button = button;
		e.type = action == GLFW_PRESS ? EventType::mouse_down : EventType::mouse_released;

		
	}
}

void Input::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
}

void Input::character_callback(GLFWwindow* window, unsigned int codepoint)
{
}

void Input::window_size_callback(GLFWwindow* window, int width, int height)
{
}
