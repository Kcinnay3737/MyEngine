#include "Engine.h"

#include "Window/IWindow.h"
#include "Graphics/IGraphics.h"
#include "Input/IInput.h"

#include "Window/SDLWindow.h"
#include "Graphics/SDLGraphics.h"
#include "Input/SDLInput.h"

#include <time.h>
#include <SDL.h>

using namespace NPEngine;

bool Engine::InitEngine(const char* Name, int Width, int Height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		SDL_Log(SDL_GetError());
		return false;
	}

	_Window = new SDLWindow();
	if (!_Window->InitWindow(Name, Width, Height))
	{
		return false;
	}

	_Graphics = new SDLGraphics();
	if (!_Graphics->InitGraphics(_Window))
	{
		return false;
	}

	_Input = new SDLInput();

	GetEngineState().IsInit = true;

	return true;
}

void Engine::Start(void)
{
	if (!GetEngineState().IsInit)
	{
		if (!InitEngine("Unknow title", 800, 600))
		{
			return;
		}
	}

	GetEngineState().IsRunning = true;

	clock_t LastFrameStartTime = clock();

	while (GetEngineState().IsRunning)
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

void Engine::ProcessInput(void)
{
	IInput* Input = GetInput();
	if (Input)
	{
		Input->Update();
	}

	//SDL_Event _Event;
	//while (SDL_PollEvent(&_Event))
	//{
	//	switch (_Event.type)
	//	{
	//	case SDL_QUIT:
	//		_IsRunning = false;
	//		break;
	//	}
	//}

	//_KeyState = SDL_GetKeyboardState(nullptr);
}

void Engine::Update(float DeltaTime)
{
	/*if (_KeyState[SDL_SCANCODE_D])
	{
		_X += 100 * DeltaTime;
	}*/
}

void Engine::Render(void)
{
	/*SDL_SetRenderDrawColor(_Renderer, 0, 0, 0, 255);
	SDL_RenderClear(_Renderer);

	SDL_SetRenderDrawColor(_Renderer, 255, 0, 0, 255);
	SDL_Rect Rect = {0};
	Rect.x = _X;
	Rect.y = 100;
	Rect.w = 100;
	Rect.h = 100;

	SDL_RenderDrawRect(_Renderer, &Rect);

	SDL_RenderPresent(_Renderer);*/

}

void Engine::ControlFrameRate(long StartTime, long CurrentTime)
{
	const int DesiredFrameDuration = 1000 / _FramesPerSecond;
	long CurrentFrameTime = (CurrentTime - StartTime) * 1000 / CLOCKS_PER_SEC;

	if (CurrentFrameTime < DesiredFrameDuration)
	{
		SDL_Delay(DesiredFrameDuration - CurrentFrameTime);
	}
}

void Engine::Shutdown(void)
{
	if (_Input != nullptr)
	{
		delete _Input;
	}
	//SDL_DestroyRenderer(_Renderer);
	//SDL_DestroyWindow(_Window);
	//SDL_Quit();
}

//Getter, Setter

EngineState& NPEngine::Engine::GetEngineState()
{
	return _EngineState;
}

IWindow* Engine::GetWindow()
{
	return _Window;
}

IGraphics* Engine::GetGraphics()
{
	return _Graphics;
}

IInput* Engine::GetInput()
{
	return _Input;
}

ITime* NPEngine::Engine::GetTime()
{
	return _Time;
}
