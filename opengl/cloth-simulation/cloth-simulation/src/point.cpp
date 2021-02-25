#include "..\include\point.h"
#include <iostream>
#include <algorithm>

/*
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

*/

void Step(Point p, float dt)
{
	p.position = p.position + p.velocity * dt; 
	p.velocity = p.velocity + (calculateForce(p) / p.mass) * dt; 
}

glm::vec3 calculateForce(Point p)
{
	glm::vec3 totalForce = glm::vec3(0.0f, 0.0f, 0.0f);
	std::for_each(p.connectedPoints.begin(), p.connectedPoints.end(), [&](Point q) {
		glm::vec3 a = glm::abs(p.position - q.position);
		glm::vec3 springForce = p.stiffness * (p.restLength - a) * ((p.position - q.position) / a);
		totalForce += springForce;
	});

	totalForce += glm::vec3(0.0f, p.mass * gravity, 0.0f);
	totalForce += -cd * p.velocity;

	return totalForce;
}
