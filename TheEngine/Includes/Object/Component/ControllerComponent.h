#pragma once

#include "Object/Component/Component.h"
#include "Input/IInput.h"

namespace NPEngine
{
	class ControllerComponent : public Component
	{
	private:
		float _MoveSpeed = 200.0f;

	public:
		ControllerComponent(std::string& Name);
		virtual ~ControllerComponent() = default;

	private:
		virtual bool Initialise(const Param& Params = Param{}) override;
		virtual void Destroy(const Param& Params = Param{}) override;

		void OnMoveKeyPressed(const DataKey& CurrDataKey);

	public:
		void SetMoveSpeed(float MoveSpeed) { _MoveSpeed = MoveSpeed; }
		float GetMoveSpeed() const { return _MoveSpeed; }
	};
}