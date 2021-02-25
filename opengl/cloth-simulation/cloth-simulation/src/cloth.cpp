#include "..\include\cloth.h"

#include<cmath>
#include<iostream> //For debug purposes
#define GLEW_STATIC
#include<GL/glew.h>

Cloth::Cloth(ClothConfig _config, unsigned int _gridSize) : clothConfig(_config), gridSize(_gridSize), index_count(0)
{
	// Creates the cloth grid

	// 1. Update and fill the points list!
	CreateGridPoints();

	// 2. Create the opengl vertex array object buffer
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// 3. Creat the opengl index buffer object which connects all the points
	glGenBuffers(1, &ibo);
	UpdateIndicesBuffer();

	// 4. Create the opengl vertex buffer object which holds the points data
	glGenBuffers(1, &vbo);
	UpdateVertexBuffer();

	// 5. Setup the created VAO from step 2
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (GLvoid*)0);

	// Done!
}

void Cloth::Update(GLfloat dt)
{
	// 1. Loop through and call .step on each point
	
	for(auto& Point : gridPoints)
	{
		Step(Point, dt);
	}

	// 2. Probably do some kind of UI update later on
}

void Cloth::Draw()
{
	// 1. Bind all buffers
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// 2. Call glDrawElements(...)
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, (const void*)0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// ...probably no reason to unbind since this project will only render a cloth...
}

void Cloth::CreateGridPoints()
{
	gridPoints.clear(); // Empty out all the current grid points

	for (int x = 0; x < gridSize; x++) {
		for (int y = 0; y < gridSize; y++) {
			Point p;
			p.position = { x*clothConfig.L0, 0, y * clothConfig.L0 };
			gridPoints.push_back(p);
		}
	}
	unsigned int squares_per_side = gridSize - 1;
	int x_counter = -1; 
	int y_counter = 0; 
	for (int i = 0; i < gridPoints.size(); i++) {
		x_counter++;

		//not to the left
		if (x_counter != 0) {
			//connect point to the left to gridPoints.p

			if (y_counter != 0) {
				//connect diagonly to the top left
			}

			//flexion two to the left
			if (x_counter - 2 >= 0) {
				//connect point 2 away to the left
			}
		}
		//not to the right
		if (x_counter != squares_per_side) {
			//connect point to the right to gridPoints.p

			if (y_counter != 0) {
				//connect diagonly to the top right
			}

			//flexion two to the right
			if (x_counter + 2 <= squares_per_side) {
				//connect point 2 away to the right
			}
		}
		//not above
		if (y_counter != 0) {
			//connect point to the above to gridPoints.p

			//flexion two to the top
			if (y_counter - 2 >= 0) {
				//connect point 2 away to the top
			}

			
		}
		//not under
		if (y_counter != squares_per_side) {
			//connect point to the left to gridPoints.p

			if (x_counter != 0) {
				//connect diagonly to the bottom left
			}

			if (x_counter != squares_per_side) {
				//connect diagonly to the bottom right
			}

			//flexion two to the bottom
			if (x_counter + 2 <= squares_per_side) {
				//connect point 2 away to the bottom
			}

		}

		if (x_counter == squares_per_side) {
			x_counter = 0;
			y_counter++;
		}
	}
}

void Cloth::UpdateIndicesBuffer()
{
	unsigned int squares_per_side = gridSize - 1;
	unsigned int no_squares = std::pow(squares_per_side, 2);

	index_count = no_squares * 6; // 3 indices per triangle, 2 triangles per square!

	unsigned int* indices = new unsigned int[index_count];
	int counter = 0;
	int pointer = 0;

	for (int i = 0; i < index_count; i++) {
		int _temp = gridSize + 1;

		indices[i] = pointer; i += 1;
		indices[i] = pointer + 1; i += 1;
		indices[i] = pointer + _temp; i += 1;
		indices[i] = pointer; i += 1;
		indices[i] = pointer + _temp; i += 1;
		indices[i] = pointer + (_temp - 1);

		counter++;

		if (counter == gridSize - 1) {
			pointer += 2;
			counter = 0;
		}
		else {
			pointer += 1;
		}
	}

	std::vector<unsigned int> indices_vec(indices, indices + index_count);
	delete[] indices;

	// Update the ibo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_vec.size() * sizeof(unsigned int), &indices_vec.front(), GL_STATIC_DRAW);
}

void Cloth::UpdateVertexBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, gridPoints.size() * sizeof(Point), &gridPoints.front(), GL_STATIC_DRAW);
}
