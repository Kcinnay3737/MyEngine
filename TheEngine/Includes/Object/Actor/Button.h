#pragma once

#include "Object/Actor/Actor.h"
#include "Input/IInput.h"

namespace NPEngine
{
	class AtlasComponent;
	class PhysicsComponent;

	class Button : public Actor
	{
	public:
		Delegate<void> OnClicked;

	protected:
		AtlasComponent* _AtlasComponent = nullptr;
		PhysicsComponent* _PhysicsComponent = nullptr;

		bool _bButtonIsPressed = false;

	public:
		Button(const std::string& Name);
		virtual ~Button() = default;

		virtual Actor* Clone(std::string& Name, const Param& Params = Param{}) override;

	protected:
		virtual bool Initialise(const Param& Params) override;
		virtual void Destroy(const Param& Params) override;
		virtual void BeginPlay() override;

	private:
		void OnLeftMousePressed(const DataButton& CurrDataKey);
		void OnLeftMouseReleased(const DataButton& CurrDataKey);

		virtual void OnPressedButton();
		virtual void OnReleasedButton();

	public:
		
	};
}