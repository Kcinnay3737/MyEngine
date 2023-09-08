#pragma once

#include <string>

//struct SDL_Renderer;
//struct SDL_Window;

namespace NPEngine
{
	class IWindow;
	class IGraphics;
	class IInput;
	class ITime;

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
		EngineState _EngineState = EngineState();

		//SDL_Renderer* _Renderer = NULL;
		//SDL_Window* _Window = NULL;

		IWindow* _Window = nullptr;
		IGraphics* _Graphics = nullptr;
		IInput* _Input = nullptr;
		ITime* _Time = nullptr;

		const int _FramesPerSecond = 60;
		const uint8_t* _KeyState = NULL;
		float _X = 0.0f;

	public:
		bool InitEngine(const char* Name, int Widht, int Height);
		void Start(void);

	private:
		void ProcessInput(void);
		void Update(float DeltaTime);
		void Render(void);
		void ControlFrameRate(long StartTime, long CurrentTime);
		void Shutdown(void);

	public:
		//Getter, setter
		EngineState& GetEngineState();

		IWindow* GetWindow();
		IGraphics* GetGraphics();
		IInput* GetInput();
		ITime* GetTime();
	};
}