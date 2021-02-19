#pragma once

#include<glm/vec3.hpp>
#include<glm/vec2.hpp>

// A simple Quad that can be rendered, mainly used to test stuff 
class Quad {
public:
	Quad(glm::vec3 _position, glm::vec2 _size);
	~Quad();

	// Binds the related OpenGL buffers
	void Bind();

	// Renders the Quad
	void Render();

public:
	glm::vec3 position;
	glm::vec2 size;

private:
	unsigned int vao; // Vertex Array Object
	unsigned int ibo; // Index Buffer
	unsigned int vbo; // Vertex Buffer
};