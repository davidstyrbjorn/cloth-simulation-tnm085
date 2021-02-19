#include "..\include\point.h"
#include <iostream>
#include <algorithm>


Point::Point()
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	velocity = glm::vec3(0.0f, 0.0f, 0.0f);
}

Point::Point(glm::vec3 Position, glm::vec3 Velocity, float Mass, float Stiffness, float RestLength)
{
	position = Position;
	velocity = Velocity;
	mass = Mass;
	stiffness = Stiffness;
	restLength = RestLength; 
}

void Point::Step(float dt)
{
	position = position + velocity * dt; 
	velocity = velocity + (calculateForce() / mass) * dt; 
}

glm::vec3 Point::calculateForce()
{
	glm::vec3 totalForce = glm::vec3(0.0f, 0.0f, 0.0f);
	std::for_each(connectedPoints.begin(), connectedPoints.end(), [&](Point q) {
		glm::vec3 a = glm::abs(position - q.position);
		glm::vec3 springForce = stiffness * (restLength - a) * ((position - q.position) / a);
		totalForce += springForce;
	});

	totalForce += glm::vec3(0.0f, mass * gravity, 0.0f);
	totalForce += -cd * velocity;

	return totalForce;
}
