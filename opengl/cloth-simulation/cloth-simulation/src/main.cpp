#include<iostream>
#include "../include/window.h"
#include "../include/input.h"




int main() {
	
	Window window = Window(640, 480, "Cloth Simulation");

	while (window.IsOpen()) 
	{
		window.Clear(glm::vec4(0.5,0.5,1,1));

		window.Display();
	}


	return 0;
}