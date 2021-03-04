#pragma once
#include <vector>
#include <string>
#include "shader.h"

class Skybox
{
public:	
	Skybox(std::vector<std::string> textures_faces, int width, int height, int nrChannels);
	~Skybox();
	
	void Draw();
	
public:
	Shader skyShader;
	unsigned int textureID;
	unsigned int vao;
	unsigned int vbo;
	unsigned char* data;
};

