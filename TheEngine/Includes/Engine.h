#pragma once

namespace NPEngine
{
	class IGraphics;
	class IInput;
	class ITime;
	class ILogger;

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
		static Engine* GetEngineInstance();

		EngineState& GetEngineState();

		IGraphics* GetGraphics();
		IInput* GetInput();
		ITime* GetTime();
		ILogger* GetLogger();
	};
}