#pragma once

#include "World/IScene.h"

namespace NPEngine
{
	class Scene : public IScene
	{
	private:
		virtual bool Initialise() override;
		virtual void Shutdown() override;
	};
}