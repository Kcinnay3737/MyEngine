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

using namespace NPEngine;

Engine* Engine::_InstanceEngine = nullptr;

bool Engine::InitEngine(const char* Name, int Width, int Height)
{
#if _DEBUG
	_Logger = new ConsoleLogger();
#else
	_Logger = new FileLogger();
#endif
	if (!_Logger || !_Logger->Initialize())
	{
		return false;
	}

	_Graphics = new SDLGraphics();
	if (!_Graphics || !_Graphics->Initialize(Name, Width, Height))
	{
		return false;
	}
	_Graphics->SetBackgroundColor(Color::Black);
	
	_Input = new SDLInput();
	if (!_Input || !_Input->Initialize())
	{
		return false;
	}

	_Time = new SDLTime();
	if (!_Time || !_Time->Initialise())
	{
		return false;
	}
	_Time->SetFramePerSecond(60);

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

		ProcessInput();
		Update(_Time->GetDeltaTime());
		Render();

		_Time->ControlFrameRate();
		_Time->UpdateLastFrameStartTime();
	}

	Shutdown();
}

void Engine::ProcessInput()
{
	_Input->ProcessInput();
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
	_Graphics->Clear();

	Rectangle2D<float> Rect = Rectangle2D<float>(Vector2D<float>(10.0f, 0.0f), Vector2D<float>(100.0f, 100.0f));
	_Graphics->DrawTextureTile("D:\\MyEngine\\MyEngine\\Texture\\default.png", Rect, Vector2D<int>(3, 3), Vector2D<int>(0, 1));

	_Graphics->Present();
}

void Engine::Shutdown(void)
{
	if (_Graphics)
	{
		_Graphics->Shutdown();
		delete _Graphics;
	}
	if (_Input)
	{
		_Input->Shutdown();
		delete _Input;
	}
	if (_Time)
	{
		_Time->Shutdown();
		delete _Time;
	}
	if (_Logger)
	{
		_Logger->Shutdown();
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
