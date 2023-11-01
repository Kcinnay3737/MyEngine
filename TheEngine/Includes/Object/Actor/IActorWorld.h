#pragma once

#include "Utility/Utility.h"

namespace NPEngine
{
	class IActorWorld
	{
		friend class World;
		friend class InstanceManager;
	public:
		virtual ~IActorWorld() = default;

		virtual void SetDrawDepth(unsigned char DrawDepth) = 0;
		virtual unsigned char GetDrawDepth() = 0;

	private:
		virtual bool Initialise(const Param& Params = Param{}) = 0;
		virtual void Destroy(const Param& Params = Param{}) = 0;

		virtual void BeginPlay() = 0;

		virtual void Update(float dt) = 0;
		
		virtual void Draw() = 0;
	};
}