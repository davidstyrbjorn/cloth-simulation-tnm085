#pragma once

class Cloth;

class ClothUI {
public:
	ClothUI(Cloth* cloth) : clothPointer(cloth) {}

private:
	Cloth* clothPointer;

};