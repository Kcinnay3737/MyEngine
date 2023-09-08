#include "Input/SDLInput.h"

#include <SDL.h>

void NPEngine::SDLInput::Update()
{
	/*SDL_Event _Event;
	while (SDL_PollEvent(&_Event))
	{
		switch (_Event.type)
		{
		case SDL_QUIT:
			_IsRunning = false;
			break;
		}
	}

	_KeyState = SDL_GetKeyboardState(nullptr);*/
}

bool NPEngine::SDLInput::IsKeyDown(int keycode)
{
    return false;
}

bool NPEngine::SDLInput::IsButtonDown(int button)
{
    return false;
}

void NPEngine::SDLInput::GetMousePosition(int* x, int* y)
{
}
