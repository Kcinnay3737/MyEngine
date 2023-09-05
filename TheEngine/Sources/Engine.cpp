#include "Engine.h"
#include <time.h>
#include <SDL.h>

#include "SDLInput.h"

bool NPEngine::Engine::Init(const char* Name, int Widht, int Height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		SDL_Log(SDL_GetError());
		return false;
	}

	int X = SDL_WINDOWPOS_CENTERED;
	int Y = SDL_WINDOWPOS_CENTERED;
	Uint32 Flag = SDL_WINDOW_TOOLTIP;

	_Window = SDL_CreateWindow(Name,X, Y, Widht, Height, Flag);
	if (!_Window)
	{
		SDL_Log(SDL_GetError());
		return false;
	}

	Uint32 RenderFlags = SDL_RENDERER_ACCELERATED;
	_Renderer = SDL_CreateRenderer(_Window, -1, RenderFlags);

	if (!_Renderer)
	{
		SDL_Log(SDL_GetError());
		return false;
	}

	_IsInit = true;

	_Input = new SDLInput();

	return true;
}

void NPEngine::Engine::Start(void)
{
	if (!_IsInit)
	{
		if (!Init("Unknow title", 800, 600))
		{
			return;
		}
	}

	_IsRunning = true;

	clock_t LastFrameStartTime = clock();

	while (_IsRunning)
	{
		const clock_t CurrentFrameStartTime = clock();
		float DeltaTime = (CurrentFrameStartTime - LastFrameStartTime) * 0.001f;

		ProcessInput();
		Update(DeltaTime);
		Render();

		ControlFrameRate(CurrentFrameStartTime, clock());

		LastFrameStartTime = CurrentFrameStartTime;
	}

	Shutdown();
}

void NPEngine::Engine::ProcessInput(void)
{
	Input().Update();

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

void NPEngine::Engine::Update(float DeltaTime)
{
	if (_KeyState[SDL_SCANCODE_D])
	{
		_X += 100 * DeltaTime;
	}
}

void NPEngine::Engine::Render(void)
{
	SDL_SetRenderDrawColor(_Renderer, 0, 0, 0, 255);
	SDL_RenderClear(_Renderer);

	SDL_SetRenderDrawColor(_Renderer, 255, 0, 0, 255);
	SDL_Rect Rect = {0};
	Rect.x = _X;
	Rect.y = 100;
	Rect.w = 100;
	Rect.h = 100;

	SDL_RenderDrawRect(_Renderer, &Rect);

	SDL_RenderPresent(_Renderer);

}

void NPEngine::Engine::ControlFrameRate(long StartTime, long CurrentTime)
{
	const int DesiredFrameDuration = 1000 / _FramesPerSecond;
	long CurrentFrameTime = (CurrentTime - StartTime) * 1000 / CLOCKS_PER_SEC;

	if (CurrentFrameTime < DesiredFrameDuration)
	{
		SDL_Delay(DesiredFrameDuration - CurrentFrameTime);
	}
}

void NPEngine::Engine::Shutdown(void)
{
	if (_Input != nullptr)
	{
		delete _Input;
	}
	SDL_DestroyRenderer(_Renderer);
	SDL_DestroyWindow(_Window);
	SDL_Quit();
}