#pragma once
#include "cloth.h"



class ClothUI {
public:
	ClothUI(Cloth* cloth);
	void render();
private:
	Cloth* clothPointer;
};