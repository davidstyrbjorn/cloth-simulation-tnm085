#pragma once

#include<vector>

class Point;

struct ClothConfig {
	float K; // Fjäderns styvhet
	float L0; // Fjärderns vilolängd
};

class Cloth {
	Cloth()

	void Update(float dt);

private:
	ClothConfig clothConfig;
	std::vector<Point> gridPoints;
};