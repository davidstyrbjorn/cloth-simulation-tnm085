#pragma once


class Cloth;

class ClothUI {
public:
	ClothUI(Cloth& cloth) : clothPointer(&cloth) {}
	void Render();
private:
	Cloth* clothPointer;
};