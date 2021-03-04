#include "..\include\point.h"
#include <iostream>
#include <algorithm>
#include<cmath>

#include<glm/glm.hpp>
#include<GLFW/glfw3.h>

#include"../include/external_force.h"

void Step(Point& p, const ClothConfig& clothConfig, float dt)
{
	if (p.isStatic) return;

	//temp ball
	p.ballRadius = 5.25f;
	p.ballPosition = { -5.0f, -1.0f, 0.0f};

	bool f =false;
	/*-----Euler-----*/
	if (f) {
		p.position = p.position + p.velocity * dt; 
		//collision
			glm::vec3 offset = p.position - p.ballPosition;
			
			if (glm::length(offset) < p.ballRadius) {
				p.position += glm::normalize(offset) * (p.ballRadius - glm::length(offset));
			
		}
		p.velocity = p.velocity + ((calculateForce(p, clothConfig) + p.accumulatedForce) / clothConfig.mass) * dt;
		p.accumulatedForce = { 0,0,0 };

	}
	/*-----Verlet----*/
	else {
		// newAcc is used to save the new acceleration and allow both the new and old to be used during calculations
		glm::vec3 newAcc = (calculateForce(p, clothConfig) + p.accumulatedForce) / clothConfig.mass;
		p.accumulatedForce = { 0,0,0 };

		//Calculate our new position and velocity
		p.position = p.position + p.velocity * dt + p.acceleration * (dt * dt * 0.5f);
		//collision
			glm::vec3 offset = p.position - p.ballPosition;

			if (glm::length(offset) < p.ballRadius) {
				p.position += glm::normalize(offset) * (p.ballRadius - glm::length(offset));
			}
		
		p.velocity = p.velocity + (p.acceleration + newAcc) * (dt * 0.5f);

		//Set newAcc to our current acceleration
		p.acceleration = newAcc;
	}

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
		glm::vec3 springForce = clothConfig.K * (actualRestLength - temp) * ((p.position - q.position) / temp);

		spring.connectedPoint->accumulatedForce += -springForce;

		//springForce = { 0,0,0 };
		totalForce += springForce;

		/* Constraints */
		if (temp > actualRestLength*1.1f) {
			float offset = (temp - actualRestLength*1.1f) / temp;
			glm::vec3 correction = 0.5f * offset * (p.position - q.position);
			if (!p.isStatic)
				p.position -= correction;
			if (!q.isStatic)
				q.position += correction;
		}

	

		
	}

	// Add gravity and damping
	totalForce += -clothConfig.cd * p.velocity;
	totalForce += glm::vec3(0.0f, -clothConfig.mass*clothConfig.g, 0.0f);
	
	// Go through and add each external force 
	for (auto&& force : clothConfig.externalForces) {
		totalForce += force->getForce(glfwGetTime(), p);
	}
	//SinusWindPositional s;
	//s.strength = 4;
	////s.direction = glm::vec3(0.4, 0, 0.5);
	//s.position = { 20, 0, 0 };
	//s.target = p.position;
	//
	//totalForce += s.getForce(glfwGetTime());

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
