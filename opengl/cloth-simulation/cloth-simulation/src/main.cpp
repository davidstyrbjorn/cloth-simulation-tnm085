#include<iostream>
#include "../include/window.h"
#include "../include/input.h"

int main() {
	
	Window window = Window(640, 480, "Cloth Simulation");

	while (window.IsOpen()) 
	{
		for (Event e : window.GetPolledEvents()) {
			if (e.type == EventType::key_down) {
				std::cout << "Key Pressed!!!" << std::endl;
			}
			if (e.type == EventType::window_resized) {
				std::cout << e.size.x << std::endl;
			}
		}

		window.Clear(glm::vec4(0.5,0.5,1,1));

		window.Display();
	}

	return 0;
}