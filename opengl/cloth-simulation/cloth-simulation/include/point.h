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
	glm::vec3 position		= { 0,0,0 };
	glm::vec3 velocity		= { 0,0,0 };
	glm::vec3 acceleration	= { 0,0,0 };
	glm::vec3 normal = { 0,0,0 };
	glm::vec3 force = { 0,0,0 };
	std::vector<Spring> springs;
	bool isStatic = false;
};

struct Spring {
	Point* connectedPoint;
	SpringType springType;
};

void Step(Point &p, const ClothConfig& clothConfig, float dt);
glm::vec3 calculateForce(Point &p, const ClothConfig& clothConfig);

float calculateRestLength(SpringType springType, float L0);