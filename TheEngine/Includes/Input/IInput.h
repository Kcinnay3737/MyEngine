#pragma once

#include "Input/IInputProvider.h"
#include "Input/EnumInput.h"

namespace NPEngine
{
	struct DataInput
	{
	public:
		float TimePressed = 0.0f;
		bool bIsPressed = false;
	};

	class IInput : public IInputProvider
	{
	private:
		std::map<EKeyboardKeys, DataInput> _InputState;
		std::map<EButtonKeys, DataInput> _ButtonState;

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