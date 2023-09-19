#include "Input/SDLInput.h"

#include "Engine.h"
#include <SDL.h>

using namespace NPEngine;

bool SDLInput::Initialize()
{
	return true;
}

void SDLInput::Shutdown()
{
	/*if (_KeyStates)
	{
		delete _KeyStates;
	}*/
}

bool SDLInput::IsKeyDown(EKeyboardKeys Key)
{
	return _KeyStates[MapToSDLScancode(Key)];
}

bool SDLInput::IsButtonDown(EButtonKeys Key)
{
	return SDL_BUTTON(MapToSDLButtonCode(Key));
}

void SDLInput::GetMousePosition(int* X, int* Y)
{
	SDL_GetMouseState(X, Y);
}

SDL_Scancode SDLInput::MapToSDLScancode(EKeyboardKeys Key)
{
	switch (Key)
	{
	// Letter
	case Key_A: return SDL_SCANCODE_A;
	case Key_B: return SDL_SCANCODE_B;
	case Key_C: return SDL_SCANCODE_C;
	case Key_D: return SDL_SCANCODE_D;
	case Key_E: return SDL_SCANCODE_E;
	case Key_F: return SDL_SCANCODE_F;
	case Key_G: return SDL_SCANCODE_G;
	case Key_H: return SDL_SCANCODE_H;
	case Key_I: return SDL_SCANCODE_I;
	case Key_J: return SDL_SCANCODE_J;
	case Key_K: return SDL_SCANCODE_K;
	case Key_L: return SDL_SCANCODE_L;
	case Key_M: return SDL_SCANCODE_M;
	case Key_N: return SDL_SCANCODE_N;
	case Key_O: return SDL_SCANCODE_O;
	case Key_P: return SDL_SCANCODE_P;
	case Key_Q: return SDL_SCANCODE_Q;
	case Key_R: return SDL_SCANCODE_R;
	case Key_S: return SDL_SCANCODE_S;
	case Key_T: return SDL_SCANCODE_T;
	case Key_U: return SDL_SCANCODE_U;
	case Key_V: return SDL_SCANCODE_V;
	case Key_W: return SDL_SCANCODE_W;
	case Key_X: return SDL_SCANCODE_X;
	case Key_Y: return SDL_SCANCODE_Y;
	case Key_Z: return SDL_SCANCODE_Z;

	// Number
	case Key_0: return SDL_SCANCODE_0;
	case Key_1: return SDL_SCANCODE_1;
	case Key_2: return SDL_SCANCODE_2;
	case Key_3: return SDL_SCANCODE_3;
	case Key_4: return SDL_SCANCODE_4;
	case Key_5: return SDL_SCANCODE_5;
	case Key_6: return SDL_SCANCODE_6;
	case Key_7: return SDL_SCANCODE_7;
	case Key_8: return SDL_SCANCODE_8;
	case Key_9: return SDL_SCANCODE_9;

	// F Key
	case Key_F1: return SDL_SCANCODE_F1;
	case Key_F2: return SDL_SCANCODE_F2;
	case Key_F3: return SDL_SCANCODE_F3;
	case Key_F4: return SDL_SCANCODE_F4;
	case Key_F5: return SDL_SCANCODE_F5;
	case Key_F6: return SDL_SCANCODE_F6;
	case Key_F7: return SDL_SCANCODE_F7;
	case Key_F8: return SDL_SCANCODE_F8;
	case Key_F9: return SDL_SCANCODE_F9;
	case Key_F10: return SDL_SCANCODE_F10;
	case Key_F11: return SDL_SCANCODE_F11;
	case Key_F12: return SDL_SCANCODE_F12;

	// Modifier keys and more
	case Key_Shift: return SDL_SCANCODE_LSHIFT;
	case Key_Control: return SDL_SCANCODE_LCTRL;
	case Key_Alt: return SDL_SCANCODE_LALT;
	case Key_Space: return SDL_SCANCODE_SPACE;
	case Key_Enter: return SDL_SCANCODE_RETURN;
	case Key_Backspace: return SDL_SCANCODE_BACKSPACE;
	case Key_Tab: return SDL_SCANCODE_TAB;
	case Key_Escape: return SDL_SCANCODE_ESCAPE;
	case Key_CapsLock: return SDL_SCANCODE_CAPSLOCK;
	case Key_NumLock: return SDL_SCANCODE_NUMLOCKCLEAR;
	case Key_ScrollLock: return SDL_SCANCODE_SCROLLLOCK;

	// Direction keys
	case Key_UpArrow: return SDL_SCANCODE_UP;
	case Key_DownArrow: return SDL_SCANCODE_DOWN;
	case Key_LeftArrow: return SDL_SCANCODE_LEFT;
	case Key_RightArrow: return SDL_SCANCODE_RIGHT;

	// Numeric keypad keys
	case Key_Numpad0: return SDL_SCANCODE_KP_0;
	case Key_Numpad1: return SDL_SCANCODE_KP_1;
	case Key_Numpad2: return SDL_SCANCODE_KP_2;
	case Key_Numpad3: return SDL_SCANCODE_KP_3;
	case Key_Numpad4: return SDL_SCANCODE_KP_4;
	case Key_Numpad5: return SDL_SCANCODE_KP_5;
	case Key_Numpad6: return SDL_SCANCODE_KP_6;
	case Key_Numpad7: return SDL_SCANCODE_KP_7;
	case Key_Numpad8: return SDL_SCANCODE_KP_8;
	case Key_Numpad9: return SDL_SCANCODE_KP_9;
	case Key_NumpadMultiply: return SDL_SCANCODE_KP_MULTIPLY;
	case Key_NumpadAdd: return SDL_SCANCODE_KP_PLUS;
	case Key_NumpadSubtract: return SDL_SCANCODE_KP_MINUS;
	case Key_NumpadDecimal: return SDL_SCANCODE_KP_PERIOD;
	case Key_NumpadDivide: return SDL_SCANCODE_KP_DIVIDE;

	default: return SDL_SCANCODE_UNKNOWN;
	}
}

Uint8 SDLInput::MapToSDLButtonCode(EButtonKeys button)
{
	switch (button) 
	{
	case Mouse_Left: return SDL_BUTTON_LEFT;
	case Mouse_Right: return SDL_BUTTON_RIGHT;
	case Mouse_Middle: return SDL_BUTTON_MIDDLE;
	default: return 0;
	}
}

void SDLInput::ProcessInput()
{
	SDL_Event _Event;
	while (SDL_PollEvent(&_Event))
	{
		switch (_Event.type)
		{
		case SDL_QUIT:
			Engine::GetEngineInstance()->GetEngineState().IsRunning = false;
			break;
		}
	}

	_KeyStates = SDL_GetKeyboardState(nullptr);
}