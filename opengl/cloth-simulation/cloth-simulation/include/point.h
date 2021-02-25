#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<vector>

#include"cloth_config.h"

struct Spring;

enum SpringType {
	STRUCTURAL,
	SHEAR,
	FLEXION,
};

struct Point {
	glm::vec3 position;
	glm::vec3 velocity;
	std::vector<Spring> springs;
};

struct Spring {
	Point* connectedPoint;
	SpringType springType;
};

void Step(Point &p, const ClothConfig& clothConfig, float dt);
glm::vec3 calculateForce(Point &p, const ClothConfig& clothConfig);

float calculateRestLength(SpringType springType, float L0);