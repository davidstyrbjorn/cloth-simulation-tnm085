#include<iostream>
#include "../include/window.h"
#include "../include/input.h"

#include"../include/quad.h"
#include"../include/shader.h"

#define GLEW_STATIC
#include<GL/glew.h>

int main() {
	
	Window window = Window(640, 480, "Cloth Simulation");

	Shader shader;
	shader.CreateAndCompileShader("quad_vert.txt", "quad_frag.txt");

	Quad quad({ 0,0,0 }, { 0,0 });

	while (window.IsOpen()) 
	{
		for (Event e : window.GetPolledEvents()) {
			if (e.type == EventType::key_down) {
				std::cout << "Key Pressed!!!" << std::endl;
			}
			if (e.type == EventType::window_resized) {
				glViewport(0, 0, e.size.x, e.size.y);
			}
		}

		window.Clear(glm::vec4(0.5,0.5,1,1));

		// Render a quad
		shader.Enable();

		quad.Bind();
		quad.Render();

		window.Display();
	}

	return 0;
}