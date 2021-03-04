#pragma once

#include<vector>
#include<glm/vec2.hpp>

#include"point.h"

class ExternalForce;

class Cloth {
public:
	// Constructs the cloth 
	Cloth(ClothConfig _config, unsigned int _gridSize);
	~Cloth(); // @TODO Delete external forces

	// Updates each point in the cloth
	void Update(float dt);

	// Draws the cloth!
	void Draw();

	// Adds a new external force to the cloth
	void AddExternalForce(ExternalForce* external);

	ClothConfig& GetClothConfig();

private:
	void CreateGridPoints();
	void UpdateIndicesBuffer();
	void UpdateVertexBuffer();
	void UpdateNormals();

	glm::vec3 GetNormal(const Point& p1, const Point& p2, const Point& p3) const;

private:
	unsigned int gridSize;
	ClothConfig clothConfig;
	std::vector<Point> gridPoints; // All the points making up the grid
	std::vector<Spring> springs;

	unsigned int vao;
	unsigned int vbo;
	unsigned int ibo;
	unsigned int index_count;

};