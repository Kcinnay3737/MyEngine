#pragma once

#include "IInterface.h"

namespace NPEngine
{
	class IScene : public IInterface
	{
	public:
		virtual ~IScene() = default;

	private:
		friend class Engine;
		virtual bool Initialise() = 0;
		friend class Engine;
		virtual void Shutdown() = 0;
	};
}