#pragma once


class Cloth;

class ClothUI {
public:
	ClothUI(Cloth& cloth) : cloth(&cloth) {}
	void Render();
private:
	Cloth* cloth;
};