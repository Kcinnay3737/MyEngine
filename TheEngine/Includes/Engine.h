#pragma once

#include "Utility/Utility.h"
#include "Utility/GameplayStatic.h"
#include "Utility/Delegate.h"

#include "Logger/ILogger.h"
#include "Time/ITime.h"
#include "Graphics/IGraphics.h"
#include "Audio/IAudio.h"
#include "Input/IInput.h"
#include "World/World.h"

namespace NPEngine
{
	struct EngineState
	{
	public:
		bool IsInit = false;
		bool IsRunning = false;
	};

	class Engine final 
	{
	public:

	private:
		static Engine* _InstanceEngine;

		EngineState _EngineState = EngineState();

		IGraphicsProvider* _GraphicsProvider = nullptr;
		IGraphics* _Graphics = nullptr;
		IInputProvider* _InputProvider = nullptr;
		IInput* _Input = nullptr;
		ITimeProvider* _TimeProvider = nullptr;
		ITime* _Time = nullptr;
		ILoggerProvider* _LoggerProvider = nullptr;
		ILogger* _Logger = nullptr;
		IAudioProvider* _AudioProvider = nullptr;
		IAudio* _Audio = nullptr;
		IWorldProvider* _WorldProvider = nullptr;
		World* _World = nullptr;

	public:
		bool InitEngine(const char* Name, int Widht, int Height);
		void Start(void);

	private:
		void StartFrame();

		void ProcessInput();
		void PostInput();

		void Update(float DeltaTime);
		void PostUpdate();

		void Render(void);
		void PostRender();

		void EndFrame();

		void Shutdown(void);

	public:
		//Getter, setter
		EngineState& GetEngineState();

		static Engine* GetEngineInstance();

		static IGraphics* GetGraphics();
		static IInput* GetInput();
		static ITime* GetTime();
		static ILogger* GetLogger();
		static IAudio* GetAudio();
		static World* GetWorld();
	};
}