#pragma once
#include "window.h"
#define GLEW_STATIC
#include "../third_party/glew/include/GL/glew.h"

class Input {
public:
	Window window;
	
	Input();
	void CollectEvents();
	bool IsKeyDown(int keycode);

private:
	void StaticInputFunction();
};