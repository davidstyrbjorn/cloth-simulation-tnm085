#pragma once

typedef unsigned int uint;

#include<string>

#include<glm/vec3.hpp>
#include<glm/mat4x4.hpp>

/* Shader class taken from https://github.com/davidstyrbjorn/terr/edit/master/engine/include/core/shader.h with SOME modifications */

// Good because:
/* Does caching of uniforms and allows text file loading! */

class Shader {
public:
	// Constructor
	Shader() = default;
	// Destructor
	~Shader();

	/* Public methods */

	void CreateAndCompileShader(std::string vertex_file_path, std::string fragment_file_path);

	void Enable();
	void Disable();

	void UniformMat4x4(std::string name, const glm::mat4x4& mat);
	void UniformVec3(std::string name, const glm::vec3& vec);
	void UniformFloat(std::string name, const float val);
	void UniformInt(std::string name, const int val);
	void UniformVec3Array(std::string name, glm::vec3* array); // @TODO Needs to be recoded

private:
	uint GetUniformLocation(std::string name);
private:
	uint program_id; // opengl handle
};