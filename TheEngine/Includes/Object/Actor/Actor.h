#pragma once

#include "Object/Object.h"
#include "Object/Actor/IActorWorld.h"

namespace NPEngine
{
	class Actor : public Object, public IActorWorld
	{
	private:
		unsigned char _DrawDepth = 0;

		std::string _Name;

	public:
		Actor(std::string& Name);
		virtual ~Actor();

		virtual Actor* Clone(std::string& Name);

	private:
		virtual bool Initialise(const Param& Params) override;
		virtual void Destroy(const Param& Params) override;

		virtual void BeginPlay() override;
		virtual void Update(float dt) override;
		virtual void Draw() override;
		
	public:
		std::string GetName() { return _Name; }

		virtual void SetDrawDepth(unsigned char DrawDepth) override;
		virtual unsigned char GetDrawDepth() override { return _DrawDepth; }

	};
}