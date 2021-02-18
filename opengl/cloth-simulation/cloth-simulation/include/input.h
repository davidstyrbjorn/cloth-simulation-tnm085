#pragma once

#include<glm/vec2.hpp>

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