#include "Graphics/SDLGraphics.h"

#include <SDL.h>
#include "Engine.h"
#include "Debug/Logger/ILogger.h"

using namespace NPEngine;

NPEngine::SDLGraphics::~SDLGraphics()
{
	SDL_DestroyRenderer(_Renderer);
	SDL_DestroyWindow(_Window);
	SDL_Quit();
}

bool NPEngine::SDLGraphics::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		Engine::GetEngineInstance()->GetLogger()->DebugMessage(SDL_GetError());
		return false;
	}
	return true;
}

bool SDLGraphics::InitWindow(const char* WindowName, int WindowWidth, int WindowHeight)
{
	int X = SDL_WINDOWPOS_CENTERED;
	int Y = SDL_WINDOWPOS_CENTERED;
	Uint32 Flag = SDL_WINDOW_TOOLTIP;

	_Window = SDL_CreateWindow(WindowName, X, Y, WindowWidth, WindowHeight, Flag);
	if (!_Window)
	{
		Engine::GetEngineInstance()->GetLogger()->DebugMessage(SDL_GetError());
		return false;
	}

	return true;
}

bool SDLGraphics::InitRenderer()
{
	if (!_Window)
	{
		Engine::GetEngineInstance()->GetLogger()->DebugMessage("La window chie");
		return false;
	}

	Uint32 RenderFlags = SDL_RENDERER_ACCELERATED;
	_Renderer = SDL_CreateRenderer(_Window, -1, RenderFlags);

	if (!_Renderer)
	{
		Engine::GetEngineInstance()->GetLogger()->DebugMessage(SDL_GetError());
		return false;
	}

	return true;
}

void NPEngine::SDLGraphics::Render()
{
	SDL_SetRenderDrawColor(_Renderer, 0, 0, 0, 255);
	SDL_RenderClear(_Renderer);

	/*SDL_SetRenderDrawColor(_Renderer, 255, 0, 0, 255);
	SDL_Rect Rect = {0};
	Rect.x = X;
	Rect.y = Y;
	Rect.w = 100;
	Rect.h = 100;

	SDL_RenderDrawRect(_Renderer, &Rect);*/

	SDL_RenderPresent(_Renderer);
}
