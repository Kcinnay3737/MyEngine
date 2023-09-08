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
		virtual ~SDLGraphics() = default;

	private:
		virtual bool InitGraphics(void* Window) override;
	};
}