#pragma once

#include "Input/IInputProvider.h"
#include "Utility/Delegate.h"
#include "Input/EnumInput.h"

namespace NPEngine
{
	struct DataKey
	{
	public:
		EKeyboardKeys Key = EKeyboardKeys::Key_None;
		float TimePressed = 0.0f;
		bool bIsPressed = false;
	};

	struct DataButton
	{
	public:
		EButtonKeys Key = EButtonKeys::Mouse_None;
		float TimePressed = 0.0f;
		bool bIsPressed = false;
	};

	class IInput : public IInputProvider
	{
	public:
		//Key delegate
		std::map<EKeyboardKeys, Delegate<void, const DataKey&>> OnKeyPressed;
		std::map<EKeyboardKeys, Delegate<void, const DataKey&>> OnKeyMaintained;
		std::map<EKeyboardKeys, Delegate<void, const DataKey&>> OnKeyReleased;

		//Button delegate
		std::map<EButtonKeys, Delegate<void, const DataButton&>> OnButtonPressed;
		std::map<EButtonKeys, Delegate<void, const DataButton&>> OnButtonMaintained;
		std::map<EButtonKeys, Delegate<void, const DataButton&>> OnButtonReleased;

	protected:
		std::map<EKeyboardKeys, DataKey> _DataKey;
		std::map<EButtonKeys, DataButton> _DataButton;

	public:
		virtual ~IInput() = default;

		virtual bool IsKeyDown(EKeyboardKeys Key) = 0;
		virtual bool IsButtonDown(EButtonKeys Key) = 0;

		virtual void GetMousePosition(int* X, int* Y) = 0;
	
	private:
		virtual bool Initialize(const Param& Params) override = 0;
		virtual void Shutdown(const Param& Params) override = 0;

		virtual void ProcessInput() override = 0;
		virtual void UpdateInputListener(float DeltaTime) override = 0;
	};
}