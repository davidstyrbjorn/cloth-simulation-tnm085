#include<iostream>
#include"../include/window.h"
#include"../include/input.h"
#include"../include/camera.h"
#include"../include/time.h"

#include"../include/cloth.h"
#include"../include/cloth_UI.h"
#include"../include/quad.h"
#include"../include/shader.h"

#include"../include/skybox.h"
#include"../include/external_force.h"

#include<stdio.h>

#include"../include/imgui/imgui.h"

#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW\glfw3.h>

const unsigned int SCR_WIDTH = 800;		
const unsigned int SCR_HEIGHT = 600;	

int main() {
	
	Window window = Window(SCR_WIDTH, SCR_HEIGHT, "Cloth Simulation");

	Camera camera(&window, glm::vec3(0.0f, 0.0f, 3.0f));
	float lastX = SCR_WIDTH / 2.0f;
	float lastY = SCR_HEIGHT / 2.0f;
	bool firstMouse = true;

	ClothConfig cc;
	cc.L0 = 1.0f;
	cc.g = 15;
	cc.K = 2;
	cc.cd = 2;
	cc.mass = 0.1f;
	Cloth cloth(cc, 16);
	
	SinusWind* force = new SinusWind;
	force->direction = {0.5, 0, 0 };
	force->strength = 3;
	cloth.AddExternalForce(force);

	Quad quad({ 0,0,0 }, { 0,0 });

	//Skybox Faces
	std::vector<std::string> faces
	{
		"skybox/right.jpg",
		"skybox/left.jpg",
		"skybox/top.jpg",
		"skybox/bottom.jpg",
		"skybox/front.jpg",
		"skybox/back.jpg"
	};
	Skybox sky = Skybox(faces, 2048, 2048, 3);
	unsigned int cubemapTexture = sky.textureID;

	// timing
	float currentTime = 0.0f;
	float deltaTime = 0.0f;	// time between current frame and last frame
	float oldTime = 0.0f;

	float stepTime = 1.2;
	//float stepTime = 0.1f;

	Shader shader;
	shader.CreateAndCompileShader("quad_vert.txt", "quad_frag.txt");

	bool isMouseDown = false;
	glm::vec2 orgMousePos;

	FPSTimer fpsTimer;

	while (window.IsOpen()) 
	{	
		for (Event e : window.GetPolledEvents()) {
			if (e.type == EventType::mouse_down) {
				// Useed for camera movement
				orgMousePos = window.GetRelativeMousePosition();
			}
		}
		
		camera.ProcessKeyboard(deltaTime);
		if(window.IsRightMouseDown()){
			auto mousepos = window.GetRelativeMousePosition();
			camera.ProcessMouseMovement(mousepos.x - orgMousePos.x ,  orgMousePos.y - mousepos.y);
		}

		/* UPDATING */

		cloth.Update(deltaTime*stepTime);

		/* RENDERING */

		// Clear the window
		window.Clear(glm::vec4(0.5,0.5,1,1));

		// Create matrices
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 skyView = glm::mat4(glm::mat3(camera.GetViewMatrix()));

		// Render the skybox
		sky.skyShader.Enable();
		sky.skyShader.UniformMat4x4("skyView", skyView);
		sky.skyShader.UniformMat4x4("projection", projection);
		sky.Draw();

		// Real rendering starts here
		shader.Enable();
		// pass projection matrix to shader (note that in this case it could change every frame)
		shader.UniformMat4x4("projection", projection);
		// camera/view transformation
		shader.UniformMat4x4("view", view);

		// Render a banana, for reference
		quad.Bind();
		quad.Render();
		
		// Renders everything todo with the cloth
		cloth.Draw();
		
		//Renders UI!
		ImGui::Begin("test");
		ImGui::Text("Or alien");
		ImGui::End();

		// Rendering done!
		window.Display();

		// Frame done, measure FPS and delta
		currentTime = glfwGetTime();
		deltaTime = currentTime - oldTime;
		oldTime = currentTime;

		fpsTimer.FrameDone();
	}

	return 0;
}