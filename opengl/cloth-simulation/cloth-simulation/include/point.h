#pragma once
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<vector>

class Point {

	const float gravity = -9.82f;
	const float cd = 2.0f;

public:
	//constructor
	Point();
	Point(glm::vec3 Position, glm::vec3 Velocity, float Mass, float Stiffness, float RestLength);

	//function
	void Step(float dt);

	glm::vec3 calculateForce();

	//vars
	glm::vec3 position;
	glm::vec3 velocity;
	float mass; 
	float stiffness;
	float restLength;
	std::vector<Point> connectedPoints;

private:


};