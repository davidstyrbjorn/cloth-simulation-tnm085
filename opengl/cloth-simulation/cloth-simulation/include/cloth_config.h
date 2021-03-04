#pragma once

#include<memory>
#include<vector>

class ExternalForce;

struct ClothConfig {
	float K; // Fjäderns styvhet
	float L0; // Fjärderns vilolängd
	float g; // Gravity
	float cd; // Damp
	float mass; // mass of each individual point
	std::vector<ExternalForce*> externalForces;
};