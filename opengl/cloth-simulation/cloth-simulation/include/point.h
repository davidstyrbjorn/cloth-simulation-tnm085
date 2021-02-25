#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<vector>

const float gravity = -9.82f;
const float cd = 2.0f;

struct Point {
	glm::vec3 position;
	glm::vec3 velocity;
	float mass; 
	float stiffness;
	float restLength;
	std::vector<Point> connectedPoints;
};

void Step(Point &p, float dt);

glm::vec3 calculateForce(Point &p);

//class Point {
//
//	
//
//public:
//	//constructor
//	Point();
//	Point(glm::vec3 Position, glm::vec3 Velocity, float Mass, float Stiffness, float RestLength);
//
//	//function
//	
//
//	
//
//	//vars
//	
//
//private:
//};