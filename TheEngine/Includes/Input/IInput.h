#pragma once

#include "Input/IInputProvider.h"
#include "Input/EnumInput.h"

namespace NPEngine
{
	class IInput : public IInputProvider
	{
	public:
		virtual ~IInput() = default;

		virtual bool IsKeyDown(EKeyboardKeys Key) = 0;
		virtual bool IsButtonDown(EButtonKeys Key) = 0;

		virtual void GetMousePosition(int* X, int* Y) = 0;
	
	private:
		virtual bool Initialize(const Param& Params) override = 0;
		virtual void Shutdown(const Param& Params) override = 0;

		virtual void ProcessInput() override = 0;
	};
}