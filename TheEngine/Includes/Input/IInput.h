#pragma once

#include "Input/EnumInput.h"

namespace NPEngine
{
	class IInput
	{
	public:
		virtual ~IInput() = default;

		virtual bool IsKeyDown(EKeyboardKeys Key) = 0;
		virtual bool IsButtonDown(EButtonKeys Key) = 0;

		virtual void GetMousePosition(int* X, int* Y) = 0;
	
	private:
		friend class Engine;
		virtual bool Initialize() = 0;
		friend class Engine;
		virtual void Shutdown() = 0;

		friend class Engine;
		virtual void ProcessInput() = 0;
		
	};
}