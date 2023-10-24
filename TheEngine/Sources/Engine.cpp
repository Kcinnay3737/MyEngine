#include "Engine.h"

#include "Graphics/IGraphics.h"
#include "Input/IInput.h"
#include "Time/ITime.h"
#include "Logger/ILogger.h"
#include "Audio/IAudio.h"
#include "World/IWorld.h"

#include "Graphics/SDLGraphics.h"
#include "Input/SDLInput.h"
#include "Time/SDLTime.h"
#if _DEBUG
#include "Logger/ConsoleLogger.h"
#else
#include "Logger/FileLogger.h"
#endif
#include "Audio/SDLAudio.h"
#include "World/World.h"

//#include <vld.h>

using namespace NPEngine;

Engine* Engine::_InstanceEngine = nullptr;

bool Engine::InitEngine(const char* Name, int Width, int Height)
{
	//VLDEnable();

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

	_Time = new SDLTime();
	if (!_Time || !_Time->Initialise())
	{
		return false;
	}

	_Input = new SDLInput();
	if (!_Input || !_Input->Initialize())
	{
		return false;
	}

	_Audio = new SDLAudio();
	if (!_Audio || !_Audio->Initialize())
	{
		return false;
	}

	_World = new World();
	if (!_World || !_World->Initialise())
	{
		return false;
	}

	_InstanceEngine = this;

	GetEngineState().IsInit = true;

	return true;
}

static size_t TextureId = 0;
static size_t FontId = 0;
static size_t MusicId = 0;
static size_t SoundId = 0;

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

	TextureId = _Graphics->LoadTexture("default.png");
	FontId = _Graphics->LoadFont("Roboto-Black.ttf", 100);
	MusicId = _Audio->LoadMusic("Dark_House.wav");
	SoundId = _Audio->LoadSound("Warped_Whoosh_001.wav");

	_Audio->PlayMusic(MusicId);
	_Audio->PlaySound(SoundId);

	_Time->InitialiseTime();

	while (GetEngineState().IsRunning)
	{
		_Time->OnStartFrame();

		ProcessInput();
		Update(_Time->GetDeltaTime());
		Render();

		_Time->OnEndFrame();
	}

	Shutdown();
}

void Engine::ProcessInput()
{
	_Input->ProcessInput();

	if (_Input->IsKeyDown(Key_Escape))
	{
		Engine::GetEngineInstance()->GetEngineState().IsRunning = false;
	}
}

static Rectangle2D<float> MovableRect = Rectangle2D<float>(Vector2D<float>(0.0f, 0.0f), Vector2D<float>(100.0f, 100.0f));

void Engine::Update(float DeltaTime)
{
	_Logger->LogMessage("DeltaTime: %f", DeltaTime);

	float MoveSpeed = 200.0f * DeltaTime;

	if (_Input->IsKeyDown(Key_W))
	{
		MovableRect.Position.Y -= MoveSpeed;
	}
	if (_Input->IsKeyDown(Key_S))
	{
		MovableRect.Position.Y += MoveSpeed;
	}
	if (_Input->IsKeyDown(Key_A))
	{
		MovableRect.Position.X -= MoveSpeed;
	}
	if (_Input->IsKeyDown(Key_D))
	{
		MovableRect.Position.X += MoveSpeed;
	}
}

void Engine::Render(void)
{
	_Graphics->Clear();

	Rectangle2D<float> DrawRect = Rectangle2D<float>(Vector2D<float>(100.f, 100.f), Vector2D<float>(200.f, 100.f));
	_Graphics->DrawTexture(TextureId, DrawRect);

	_Graphics->DrawString(FontId, "Allo", Vector2D<int>(0, 0), Color::Blue);

	_Graphics->DrawRect(MovableRect, Color::Red, true);

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
	if (_Audio)
	{
		_Audio->Shutdown();
		delete _Audio;
	}
	if (_Logger)
	{
		_Logger->Shutdown();
		delete _Logger;
	}
	if (_World)
	{
		_World->Shutdown();
		delete _World;
	}

	//VLDDisable();
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
	return GetEngineInstance()->_Graphics;
}

IInput* Engine::GetInput()
{
	return GetEngineInstance()->_Input;
}

ITime* Engine::GetTime()
{
	return GetEngineInstance()->_Time;
}

ILogger* Engine::GetLogger()
{
	return GetEngineInstance()->_Logger;
}

IAudio* NPEngine::Engine::GetAudio()
{
	return GetEngineInstance()->_Audio;
}

IWorld* NPEngine::Engine::GetWorld()
{
	return GetEngineInstance()->_World;
}
