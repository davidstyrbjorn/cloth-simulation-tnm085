#include"../include/external_force.h"

#include<cmath>
#include<glm/glm.hpp>

glm::vec3 SinusWind::getForce(float time, const Point& point)
{
	// @TODO: Add some random strength, up to 1% of the strength is added
	return point.normal * glm::dot(point.normal, direction) * strength;
}