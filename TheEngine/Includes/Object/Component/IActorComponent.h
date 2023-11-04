#pragma once

#include "Utility/Utility.h"

namespace NPEngine
{
	class Actor;

	class IActorComponent
	{
		friend class Actor;
	public:
		virtual ~IActorComponent() = default;

	private:
		virtual bool Initialise(const Param& Params = Param{}) = 0;
		virtual void Destroy(const Param& Params = Param{}) = 0;

		virtual void SetOwner(Actor* Owner) = 0;
	};
}