#pragma once

#include "Window/IWindow.h"

struct SDL_Window;

namespace NPEngine
{
	class SDLWindow final : public IWindow
	{
	public:
		
	private:
		SDL_Window* _Window = nullptr;

	public:
		virtual ~SDLWindow() = default;

	private:
		bool InitWindow(const char* WindowName, int WindowWidth, int WindowHeight) override;

	};
}