#pragma once

#include<glm/vec2.hpp>
#include<vector>
#include<iostream>

class Shader;

// Representation of a point in the grid
struct GridPoint {
	glm::vec2 position;
	std::vector<GridPoint> structural_connection;

	void UpdatePoint() { std::cout << "Its unethical in the quest for ethics - Musselios 1939\n"; }
};

class Grid {
	Grid() = default;

	void ConstructGrid();
	void UpdatePoints();
	void UploadPointsToGPU(Shader* shader);

private:
	std::vector<GridPoint> points;
	int size;
};