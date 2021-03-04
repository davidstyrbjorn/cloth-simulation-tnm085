#pragma once

class Cloth;

class ClothUI {
public:
	ClothUI(Cloth* cloth);
	void render();
private:
	Cloth* clothPointer;
};