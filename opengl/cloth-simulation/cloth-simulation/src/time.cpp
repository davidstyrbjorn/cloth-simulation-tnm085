#include "../include/time.h"

#include<GLFW/glfw3.h>
#include<iostream>

void FPSTimer::FrameDone()
{
	if (glfwGetTime() - lastRecord > 1) {
		std::cout << "MEASURED FPS: " << fps << std::endl;
		recordedFPS = fps;
		fps = 0;
		lastRecord = glfwGetTime();
	}
	fps++;
}
