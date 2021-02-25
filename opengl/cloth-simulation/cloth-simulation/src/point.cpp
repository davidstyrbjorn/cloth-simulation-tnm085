#include "..\include\point.h"
#include <iostream>
#include <algorithm>
#include<cmath>

#include<glm/glm.hpp>

void Step(Point& p, const ClothConfig& clothConfig, float dt)
{
	if (p.isStatic) return;

	p.position = p.position + p.velocity * dt; 
	p.velocity = p.velocity + (calculateForce(p, clothConfig) / clothConfig.mass) * dt; 
}

glm::vec3 calculateForce(Point& p, const ClothConfig& clothConfig)
{
	glm::vec3 totalForce = glm::vec3(0.0f, 0.0f, 0.0f);
	for(auto&& spring : p.springs){
		Point& q = *spring.connectedPoint; // Get the connected point

		// temp
		float temp = glm::distance(p.position, q.position);
		
		float actualRestLength = calculateRestLength(spring.springType, clothConfig.L0);

		// Calculate and add the spring force to our total force
		//glm::vec3 springForce = clothConfig.K * (actualRestLength - temp) * ((p.position - q.position) / temp);
		glm::vec3 springForce = -clothConfig.K * (p.position - q.position);
		totalForce += springForce;
	}

	// Add gravity and damping
	totalForce += glm::vec3(0.0f, -clothConfig.mass*clothConfig.g, 0.0f);
	totalForce += -clothConfig.cd * p.velocity;

	// Done
	return totalForce;
}

float calculateRestLength(SpringType springType, float L0)
{
	// Calculate the actual rest length based on the spring type and L0 (structural)
	if (springType == SpringType::STRUCTURAL) return L0;

	if (springType == SpringType::SHEAR) {
		// Pythagoras theormen
		return std::sqrt(std::pow(L0, 2) + std::pow(L0, 2));
	}
	if (springType == SpringType::FLEXION) {
		// Twice the length
		return L0 * 2;
	}
}
