#include "Window.h"
#include "raylib.h"

#if defined PLAT_RAYLIB

bool Window::Init(const char* title, int width, int height) {
	InitWindow(width, height, title);
	return true;
}

bool Window::IsOpen() {
	return !WindowShouldClose();
}

#endif