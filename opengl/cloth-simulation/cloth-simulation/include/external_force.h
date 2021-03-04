#pragma once

#include<glm/vec3.hpp>

#include"point.h"

class ExternalForce {
public:
	virtual glm::vec3 getForce(float time, const Point& point) = 0;

public:
	float strength = 0.0f;
};

class SinusWind : public ExternalForce {
public:
	virtual glm::vec3 getForce(float time, const Point& point);

	glm::vec3 direction = { 0,0,0 };
};
