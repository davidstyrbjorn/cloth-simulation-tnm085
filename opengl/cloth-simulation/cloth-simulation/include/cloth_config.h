#pragma once

struct ClothConfig {
	float K; // Fjäderns styvhet
	float L0; // Fjärderns vilolängd
	float g; // Gravity
	float cd; // Damp
	float mass; // mass of each individual point
};