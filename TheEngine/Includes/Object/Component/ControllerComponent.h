#pragma once

#include "Object/Component/Component.h"
#include "Input/IInput.h"

namespace NPEngine
{
	class ControllerComponent : public Component
	{
	public:


	public:
		ControllerComponent(std::string& Name);
		virtual ~ControllerComponent() = default;

	private:
		virtual bool Initialise(const Param& Params = Param{}) override;
		virtual void Destroy(const Param& Params = Param{}) override;

		void OnMoveKeyPressed(const DataKey& CurrDataKey);
	};
}