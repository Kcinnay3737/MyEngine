#include "Graphics/SDLGraphics.h"

#include <SDL.h>

using namespace NPEngine;

bool SDLGraphics::InitGraphics(void* Window)
{
	_Window = static_cast<SDL_Window*>(Window);
	if (!_Window)
	{
		SDL_Log("La window chie mon cave");
		return false;
	}

	Uint32 RenderFlags = SDL_RENDERER_ACCELERATED;
	_Renderer = SDL_CreateRenderer(_Window, -1, RenderFlags);

	if (!_Renderer)
	{
		SDL_Log(SDL_GetError());
		return false;
	}

	return true;
}
