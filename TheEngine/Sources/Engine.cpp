#include "Engine.h"

#include "Graphics/IGraphics.h"
#include "Input/IInput.h"
#include "Time/ITime.h"
#include "Debug/Logger/ILogger.h"

#include "Graphics/SDLGraphics.h"
#include "Input/SDLInput.h"
#include "Time/SDLTime.h"
#if _DEBUG
#include "Debug/Logger/ConsoleLogger.h"
#else
#include "Debug/Logger/FileLogger.h"
#endif

#include <time.h>
#include <SDL.h>

using namespace NPEngine;

Engine* Engine::_InstanceEngine = nullptr;

bool Engine::InitEngine(const char* Name, int Width, int Height)
{
	_Graphics = new SDLGraphics();
	if (!_Graphics)
	{
		return false;
	}
	if (!_Graphics->Init())
	{
		return false;
	}
	if (!_Graphics->InitWindow(Name, Width, Height))
	{
		return false;
	}
	if (!_Graphics->InitRenderer())
	{
		return false;
	}

	_Input = new SDLInput();
	if (!_Input)
	{
		return false;
	}

	_Time = new SDLTime();
	if (!_Time)
	{
		return false;
	}
	_Time->SetFramePerSecond(60);

#if _DEBUG
	_Logger = new ConsoleLogger();
#else
	_Logger = new FileLogger();
#endif

	_InstanceEngine = this;

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

	_Time->UpdateCurrentFrameStartTime();
	_Time->UpdateLastFrameStartTime();

	while (GetEngineState().IsRunning)
	{
		_Time->UpdateCurrentFrameStartTime();
		_Time->UpdateDeltaTime();

		_Input->ProcessInput();

		Update(_Time->GetDeltaTime());
		
		_Graphics->Render();

		_Time->ControlFrameRate();
		_Time->UpdateLastFrameStartTime();
	}

	Shutdown();
}

void NPEngine::Engine::ProcessInput()
{

}

void Engine::Update(float DeltaTime)
{
	if (_Input->IsKeyDown(Key_W))
	{
		_Logger->DebugMessage("test");
	}
	/*if (_KeyState[SDL_SCANCODE_D])
	{
		_X += 100 * DeltaTime;
	}*/
}

void Engine::Render(void)
{
	

}

void Engine::Shutdown(void)
{
	if (_Graphics != nullptr)
	{
		delete _Graphics;
	}
	if (_Input != nullptr)
	{
		delete _Input;
	}
	if (_Time != nullptr)
	{
		delete _Time;
	}
	if (_Logger)
	{
		delete _Logger;
	}
}

//Getter, Setter

Engine* Engine::GetEngineInstance()
{
	return _InstanceEngine;
}

EngineState& Engine::GetEngineState()
{
	return _EngineState;
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

ILogger* NPEngine::Engine::GetLogger()
{
	return _Logger;
}
