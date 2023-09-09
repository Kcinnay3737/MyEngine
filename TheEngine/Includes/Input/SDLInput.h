#pragma once

#include "Input/IInput.h"
#include "SDL_scancode.h"

namespace NPEngine
{
	class SDLInput final : public IInput
	{
	public:

	private:
		const unsigned char* _KeyStates = nullptr;

	public:
		virtual ~SDLInput() = default;

		virtual bool IsKeyDown(EKeyboardKeys Key) override;
		virtual bool IsButtonDown(EButtonKeys Key) override;

		virtual void GetMousePosition(int* x, int* y) override;

		SDL_Scancode MapToSDLScancode(EKeyboardKeys Key);
		Uint8 SDLInput::MapToSDLButtonCode(EButtonKeys button);

	private:
		virtual void ProcessInput() override;
	};
}