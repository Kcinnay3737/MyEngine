#include "Engine.h"

#include "Graphics/IGraphics.h"
#include "Input/IInput.h"
#include "Time/ITime.h"
#include "Debug/Logger/ILogger.h"
#include "Audio/IAudio.h"

#include "Graphics/SDLGraphics.h"
#include "Input/SDLInput.h"
#include "Time/SDLTime.h"
#if _DEBUG
#include "Debug/Logger/ConsoleLogger.h"
#else
#include "Debug/Logger/FileLogger.h"
#endif
#include "Audio/SDLAudio.h"

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

	_Audio = new SDLAudio();
	if (!_Audio || !_Audio->Initialize())
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

	//_Audio->PlayMusic(MusicId);
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
}

void Engine::Update(float DeltaTime)
{
	_Logger->LogMessage("%f", DeltaTime);

	if (_Input->IsKeyDown(Key_W))
	{
		_Logger->LogMessage("test");
	}
}

void Engine::Render(void)
{
	_Graphics->Clear();

	Rectangle2D<float> DrawRect = Rectangle2D<float>(Vector2D<float>(100.f, 100.f), Vector2D<float>(200.f, 100.f));
	_Graphics->DrawTexture(TextureId, DrawRect);

	_Graphics->DrawString(FontId, "Allo", Vector2D<int>(0, 0), Color::Blue);

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
