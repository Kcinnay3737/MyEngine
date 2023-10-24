#pragma once

#include "IInterface.h"

namespace NPEngine
{
	class IWorld : public IInterface
	{
	public:
		virtual ~IWorld() = default;

	private:
		friend class Engine;
		virtual bool Initialise() = 0;
		friend class Engine;
		virtual void Shutdown() = 0;
	};
}