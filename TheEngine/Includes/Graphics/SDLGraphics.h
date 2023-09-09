#pragma once

#include "Graphics/IGraphics.h"

struct SDL_Renderer;
struct SDL_Window;

namespace NPEngine
{
	class SDLGraphics final : public IGraphics
	{
	public:

	private:
		SDL_Renderer* _Renderer = nullptr;
		SDL_Window* _Window = nullptr;

	public:
		virtual ~SDLGraphics();

	private:
		float X = 100.0f;
		float Y = 100.0f;

		bool Init() override;
		bool InitWindow(const char* WindowName, int WindowWidth, int WindowHeight) override;
		bool InitRenderer() override;

		void Render();
	};
}