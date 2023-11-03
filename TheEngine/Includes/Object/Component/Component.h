#pragma once

#include "Object/Object.h"
#include "Object/Component/IActorComponent.h"

namespace NPEngine
{
	class Actor;

	class Component : public Object, public IActorComponent
	{
	private:
		std::string _Name = "";

		Actor* _OwnerActor = nullptr;

	public:
		Component(std::string& Name);
		virtual ~Component();

	private:

		virtual bool Initialise(const Param& Params = Param{}) override;
		virtual void Destroy(const Param& Params = Param{}) override;

		virtual void BeginPlay() override;

		virtual void SetOwner(Actor* Owner) override;

	public:
		std::string GetName() { return _Name; }
	};
}