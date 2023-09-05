#pragma once

#include <string>
#include "IInput.h"

struct SDL_Renderer;
struct SDL_Window;

namespace NPEngine
{
	class Engine final 
	{
	private:
		bool _IsRunning = false;
		bool _IsInit = false;

	private:
		SDL_Renderer* _Renderer = NULL;
		SDL_Window* _Window = NULL;

		IInput* _Input = nullptr;

	private:
		const int _FramesPerSecond = 60;
		const uint8_t* _KeyState = NULL;
		float _X = 0.0f;

	public:
		bool Init(const char* Name, int Widht, int Height);
		void Start(void);

		IInput& Input() { return *_Input; };

	private:
		void ProcessInput(void);
		void Update(float DeltaTime);
		void Render(void);
		void ControlFrameRate(long StartTime, long CurrentTime);
		void Shutdown(void);
	};
}