#pragma once

#include "World/IWorld.h"

namespace NPEngine
{
	class World final : public IWorld
	{
	private:
		virtual bool Initialise() override;
		virtual void Shutdown() override;
	};
}