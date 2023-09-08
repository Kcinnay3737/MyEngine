#include "Window/SDLWindow.h"

#include <SDL.h>

using namespace NPEngine;

bool SDLWindow::InitWindow(const char* WindowName, int WindowWidth, int WindowHeight)
{
	int X = SDL_WINDOWPOS_CENTERED;
	int Y = SDL_WINDOWPOS_CENTERED;
	Uint32 Flag = SDL_WINDOW_TOOLTIP;

	_Window = SDL_CreateWindow(WindowName, X, Y, WindowWidth, WindowHeight, Flag);
	if (!_Window)
	{
		SDL_Log(SDL_GetError());
		return false;
	}

    return true;
}
