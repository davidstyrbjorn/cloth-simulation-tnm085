#include "..\include\cloth.h"

#include<cmath>
#include<iostream> //For debug purposes

#define GLEW_STATIC
#include<GL/glew.h>

#include"../include/external_force.h"

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
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (GLvoid*)0);					// position
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (GLvoid*)sizeof(glm::vec3)); // normals

	// Done!
}

Cloth::~Cloth()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);

	for (int i = 0; i < clothConfig.externalForces.size(); i++) {
		delete clothConfig.externalForces[i];
	}
}

void Cloth::Update(float dt)
{	
	// 1. Loop through and call .step on each point
	for(auto& point : gridPoints)
	{
		Step(point, clothConfig, dt);	
	}

	// 2. Probably do some kind of UI update later on
}

void Cloth::Draw()
{
	// 1. Bind all buffers
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	UpdateVertexBuffer();
	UpdateNormals();

	// 2. Call glDrawElements(...)
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, (const void*)0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// 3. Draw representation for the external forces

	// ...probably no reason to unbind since this project will only render a cloth...
}

void Cloth::AddExternalForce(ExternalForce* external)
{
	clothConfig.externalForces.push_back(external);
}

ClothConfig& Cloth::GetClothConfig()
{
	return clothConfig;
}

void Cloth::CreateGridPoints()
{
	gridPoints.clear(); // Empty out all the current grid points

	for (int x = 0; x < gridSize; x++) {
		for (int z = 0; z < gridSize; z++) {
			Point p;
			p.position = { x*clothConfig.L0, 0, z * clothConfig.L0 };
			gridPoints.push_back(p);
		}
	}

	// Connect all the points
	unsigned int squares_per_side = gridSize - 1;
	int x_counter = -1; 
	int y_counter = 0; 
	for (int i = 0; i < gridPoints.size(); i++) {
		x_counter++;

		Point& curr = gridPoints[i];

		if (y_counter == 0 && (x_counter == 0 || x_counter == squares_per_side)) curr.isStatic = true;

		//not to the left
		if (x_counter != 0) {
			//connect point to the left to gridPoints.p
			curr.springs.push_back({
				&gridPoints[i - 1],
				SpringType::STRUCTURAL
			});

			if (y_counter != 0) {
				//connect diagonly to the top 
				curr.springs.push_back({ 
					&gridPoints[i - gridSize - 1], 
					SpringType::SHEAR
				});
			}

			//flexion two to the left
			if (x_counter - 2 >= 0) {
				//connect point 2 away to the left
				curr.springs.push_back({
					&gridPoints[i - 2],
					SpringType::FLEXION
				});
			}
		}
		//not to the right
		if (x_counter != squares_per_side) {
			//connect point to the right to gridPoints.p
			curr.springs.push_back({
				&gridPoints[i + 1],
				SpringType::STRUCTURAL
			});

			if (y_counter != 0) {
				//connect diagonly to the top right
				curr.springs.push_back({
					&gridPoints[i - gridSize + 1],
					SpringType::SHEAR
				});
			}

			//flexion two to the right
			if (x_counter + 2 <= squares_per_side) {
				//connect point 2 away to the right
				curr.springs.push_back({
					&gridPoints[i + 2],
					SpringType::FLEXION
				});
			}
		}
		//not above
		if (y_counter != 0) {
			//connect point to the above to gridPoints.p
			curr.springs.push_back({
				&gridPoints[i - gridSize],
				SpringType::STRUCTURAL
			});

			//flexion two to the top
			if (y_counter - 2 >= 0) {
				//connect point 2 away to the top
				curr.springs.push_back({
					&gridPoints[i - gridSize*2],
					SpringType::FLEXION
				});
			}

			
		}
		//not under
		if (y_counter != squares_per_side) {
			//connect point under 
			curr.springs.push_back({
				&gridPoints[i + gridSize],
				SpringType::STRUCTURAL
			});

			if (x_counter != 0) {
				//connect diagonly to the bottom left
				curr.springs.push_back({
					&gridPoints[i + gridSize - 1],
					SpringType::SHEAR
				});
			}

			if (x_counter != squares_per_side) {
				//connect diagonly to the bottom right
				curr.springs.push_back({
					&gridPoints[i + gridSize + 1],
					SpringType::SHEAR
				});
			}

			//flexion two to the bottom
			if (y_counter + 2 <= squares_per_side) {
				//connect point 2 away to the bottom
				curr.springs.push_back({
					&gridPoints[i + gridSize*2],
					SpringType::FLEXION
				});
			}
		}

		if (x_counter == squares_per_side) {
			x_counter = -1;
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

void Cloth::UpdateNormals()
{
	unsigned int squares_per_side = gridSize - 1;
	int x_counter = -1;
	int y_counter = 0;

	for (int i = 0; i < gridPoints.size(); i++) {
		x_counter++;

		Point& curr = gridPoints[i];
		
		// Bottom case
		if (y_counter == squares_per_side) {
			if (x_counter == squares_per_side) {
				Point& left = gridPoints[i - 1];
				Point& above = gridPoints[i - gridSize];
				curr.normal = GetNormal(curr, above, left);
			}
			else {
				Point& right = gridPoints[i + 1];
				Point& above = gridPoints[i - gridSize];
				curr.normal = GetNormal(curr, right, above);
			}
		}
		else if (x_counter == squares_per_side) {
			Point& left = gridPoints[i - 1];
			Point& under = gridPoints[i + gridSize];
			curr.normal = GetNormal(curr, left, under);
		}
		else {
			Point& right = gridPoints[i + 1];
			Point& under = gridPoints[i + gridSize];
			curr.normal = GetNormal(curr, right, under);
		}

		if (x_counter == squares_per_side) {
			x_counter = -1;
			y_counter++;
		}
	}
}

glm::vec3 Cloth::GetNormal(const Point& p1, const Point& p2, const Point& p3) const
{
	// p1 is assumed to be in the 90 degree corner
	// p2 and p3 are hypthenus points

	glm::vec3 A = p2.position - p1.position;
	glm::vec3 B = p3.position - p1.position;

	return glm::cross(A, B);
}
