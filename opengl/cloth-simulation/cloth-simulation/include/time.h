#pragma once

struct FPSTimer {
	double lastRecord = 0.0f;
	int fps = 0;
	int recordedFPS = 0; // Use this to display in ImGui or some UI

	void FrameDone();
};