#include "..\include\cloth.h"

#include<cmath>

Cloth::Cloth(ClothConfig _config, unsigned int _gridSize) : clothConfig(_config), gridSize(_gridSize), index_count(0)
{
	// Creates the cloth grid

	// 1. Update and fill the points list!
	CreateGridPoints();

	// 2. Create the opengl vertex array object buffer

	// 3. Creat the opengl index buffer object which connects all the points

	// 4. Create the opengl vertex buffer object which holds the points data

	// 5. Setup the created VAO from step 2

	// Done!
}

void Cloth::Update(float dt)
{
	// 1. Loop through and call .step on each point

	// 2. Probably do some kind of UI update later on
}

void Cloth::Draw()
{
	// 1. Bind all buffers

	// 2. Call glDrawElements(...)

	// ...probably no reason to unbind since this project will only render a cloth...
}

void Cloth::CreateGridPoints()
{
	gridPoints.clear(); // Empty out all the current grid points

	for (int x = 0; x < gridSize; x++) {
		for (int y = 0; y < gridSize; y++) {
			Point p;
			p.position = { x*clothConfig.L0,y*clothConfig.L0 };
			gridPoints.push_back(p);
		}
	}

}

void Cloth::UpdateIndicesBuffer()
{
	unsigned int squares_per_side = gridSize - 1;
	unsigned int no_squares = std::pow(squares_per_side, 2);

	index_count = no_squares * 6; // 3 indices per triangle, 2 triangles per square!

	unsigned int* 
}

void Cloth::UpdateVertexBuffer()
{
}
