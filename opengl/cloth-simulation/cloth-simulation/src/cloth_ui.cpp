#include "../include/cloth_ui.h"
#include "../include/cloth.h"

#include "../include/imgui/imgui.h"
#include <iostream>


void ClothUI::Render()
{
	ClothConfig& clothConfig = cloth->GetClothConfig();

	ImGui::Begin("Cloth Simulation");

	ImGui::Text("Cloth Variables");
	ImGui::SliderFloat("Rest Length", &clothConfig.L0, 0.0f, 3.0f);
	ImGui::SliderFloat("Gravity", &clothConfig.g, 0.0f, 20.0f);
	ImGui::SliderFloat("Spring Constant", &clothConfig.K, 0.0f, 6.0f);
	ImGui::SliderFloat("Damping force", &clothConfig.cd, 0.0f, 5.0f);
	ImGui::SliderFloat("Total Mass", &clothConfig.mass, 0.01f, 10.0f);

	ImGui::Text("External Forces");
	//ImGui::SliderFloat("Wind Direction", &clothConfig.L0, 0.0f, 3.0f);

	ImGui::Text("Grid");
	static int newClothSize = cloth->gridSize;
	ImGui::SliderInt("Grid Size", &newClothSize, 2, 36);

	if (ImGui::Button("Update")) {
		if(newClothSize != cloth->gridSize) // Do we even need to recreate the cloth?
			cloth->Recreate(newClothSize);
	}

	ImGui::Text("Constants?");
	ImGui::Text("Wind Controls");

	ImGui::End();
}