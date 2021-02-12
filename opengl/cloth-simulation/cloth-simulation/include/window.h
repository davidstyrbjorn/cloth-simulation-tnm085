#pragma once

// GLFW
#include"GLFW/glfw3.h"

// GLM
#include"glm/vec2.hpp"
#include"glm/vec4.hpp"

/*
Example use case by user:

#include"window.h"
#include"input.h"

Window window(400,300);
Input input(window);

while(window.IsOpen()){
	
	for(InputEvent event : input.GetPolledEvents()){
		// Examples
		if(event.type == EventType::WINDOW_RESIZE) {} ...
		if(event.type == EventType::KEY_PRESSED) {} ...
		if(event.type == EventType::MOUSE_DOWN) {} ...
		// event.key, event.size.x , event.size.y ...
	}

	window.Clear(...);

	// Rendering här

	input.CollectEvents();
	window.Display();
}

########################################################################################

Window constructor ska skapa GLFW fönstret inget mer
Input constructor tar in fönstret och sätter alla 'callbacks'
SE: https://www.glfw.org/docs/3.3.1/input_guide.html#events

*/

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