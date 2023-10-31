#pragma once

#include "Object/Object.h"
#include "Object/IActorWorld.h"

namespace NPEngine
{
	class Actor : public Object, public IActorWorld
	{
	private:
		const char* _Name;

	public:
		Actor(const char* Name);
		virtual ~Actor();

		virtual Actor* Clone(const char* Name);

	private:
		virtual bool Initialise(const Param& Params) override;
		virtual void Destroy(const Param& Params) override;

		virtual void BeginPlay() override;
		virtual void Update(float dt) override;
		virtual void Draw() override;
		
	public:
		const char* GetName() { return _Name; }

	};
}