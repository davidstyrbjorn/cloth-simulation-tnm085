#include "..\include\input.h"

#include"../include/window.h"

Input::Input(Window& _window) : window(_window)
{
}

void Input::CollectEvents()
{
}

bool Input::IsKeyDown(int keycode)
{
	return false;
}
