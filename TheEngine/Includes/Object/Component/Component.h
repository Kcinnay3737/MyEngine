#pragma once

#include "Object/Object.h"
#include "Object/Component/IActorComponent.h"
#include "Object/Component/IDrawableComponent.h"
#include "Object/Component/IUpdatableComponent.h"

namespace NPEngine
{
	//class Actor;

	class Component : public Object, public IActorComponent
	{
	protected:
		std::string _Name = "";

		Actor* _OwnerActor = nullptr;

	public:
		Component(const std::string& Name);
		virtual ~Component() = default;

	protected:
		virtual bool Initialise(const Param& Params = Param{}) override;
		virtual void Destroy(const Param& Params = Param{}) override;

	private:
		virtual void SetOwner(Actor* Owner) override;

	public:
		std::string GetName() { return _Name; }
		Actor* GetOwner() { return _OwnerActor; }

	};
}