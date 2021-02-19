#include"../include/quad.h"

#define GLEW_STATIC 
#include<GL/glew.h>

Quad::~Quad()
{
	// Delete buffers 
}

Quad::Quad(glm::vec3 _position, glm::vec2 _size) : position(_position), size(_size), vao(0), vbo(0), ibo(0)
{
	// Quad vertices data
	float vertices[] = {
		-0.5, -0.5, 0.0f, // bottom left
		 0.5, -0.5, 0.0f, // bottom right
		 0.5,  0.5, 0.0f, // top right
		-0.5,  0.5, 0.0f // top left
	};

	unsigned int indices[] = {
		0,1,3,
		1,2,3
	};

	// Start with the vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Generate the buffer that holds our vertices
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // This binding as GL_ARRAY_BUFFER now marks it as a vertex buffer!
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	/* Since we feed GL_ARRAY_BUFFER as input to the glBufferData, it knows to talk to our currently bound vbo! */

	// Generate the index buffer
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Set the vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

}

void Quad::Bind()
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
}

void Quad::Render()
{
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
}
