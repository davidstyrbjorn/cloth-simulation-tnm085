#pragma once

#include<glm/vec2.hpp>
#include<vector>

class Window;
struct GLFWwindow;

enum EventType {
	key_down,
	key_released,
	mouse_down,
	mouse_released,
	window_resized,
};

struct Event {
	EventType type;
	int key;
	int button;
	glm::vec2 size;
};

class Input {
public:
	Input() = default; // Default 

	std::vector<Event>& GetPolledEvents();
	void PollEvents();

	// Static GLFW Input Callbacks
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void character_callback(GLFWwindow* window, unsigned int codepoint);
	static void window_size_callback(GLFWwindow* window, int width, int height);

private:
	std::vector<Event> eventList;
};