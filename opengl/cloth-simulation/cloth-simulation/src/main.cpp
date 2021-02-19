#include<iostream>
#include "../include/window.h"
#include "../include/input.h"
#include "../include/camera.h"

#include"../include/quad.h"
#include"../include/shader.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW\glfw3.h>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
	
	Window window = Window(SCR_WIDTH, SCR_HEIGHT, "Cloth Simulation");

	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
	float lastX = SCR_WIDTH / 2.0f;
	float lastY = SCR_HEIGHT / 2.0f;
	bool firstMouse = true;
	
	// timing
	float deltaTime = 0.0f;	// time between current frame and last frame
	float lastFrame = 0.0f;

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
			if (e.type == EventType::key_down) {
				if (e.key == GLFW_KEY_W) {
					camera.ProcessKeyboard(FORWARD, 0.01);
				}
				if (e.key == GLFW_KEY_A) {
					camera.ProcessKeyboard(LEFT, 0.01);
				}
				if (e.key == GLFW_KEY_S) {
					camera.ProcessKeyboard(BACKWARD, 0.01);
				}
				if (e.key == GLFW_KEY_D) {
					camera.ProcessKeyboard(RIGHT, 0.01);
				}
			}
		}
		window.Clear(glm::vec4(0.5,0.5,1,1));

		// Render a quad
		shader.Enable();

		// pass projection matrix to shader (note that in this case it could change every frame)
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		shader.UniformMat4x4("projection", projection);

		// camera/view transformation
		glm::mat4 view = camera.GetViewMatrix();
		shader.UniformMat4x4("view", view);

		quad.Bind();
		quad.Render();

		window.Display();
	}

	return 0;
}