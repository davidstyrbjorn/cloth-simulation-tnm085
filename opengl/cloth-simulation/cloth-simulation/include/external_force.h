#pragma once

#include<glm/vec3.hpp>

class ExternalForce {
public:
	virtual glm::vec3 getForce(float time) = 0;

protected:
	glm::vec3 
};

class SinusWind : ExternalForce {

	virtual glm::vec3 getForce(float time) {

	}

};