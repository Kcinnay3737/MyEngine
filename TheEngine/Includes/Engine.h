#pragma once

namespace NPEngine
{
	class IGraphics;
	class IInput;
	class ITime;
	class ILogger;
	class IAudio;

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

		IGraphics* _Graphics = nullptr;
		IInput* _Input = nullptr;
		ITime* _Time = nullptr;
		ILogger* _Logger = nullptr;
		IAudio* _Audio = nullptr;

	public:
		bool InitEngine(const char* Name, int Widht, int Height);
		void Start(void);

	private:
		void ProcessInput();
		void Update(float DeltaTime);
		void Render(void);
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
	};
}