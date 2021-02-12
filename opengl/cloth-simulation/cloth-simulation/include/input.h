#pragma once

class Window;

class Input {
public:
	Input(Window& _window); // Default constructor
	
	void CollectEvents();
	bool IsKeyDown(int keycode);

private:
	Window& window;
};