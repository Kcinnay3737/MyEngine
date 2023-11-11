#pragma once

#include "Object/Actor/Actor.h"

namespace NPEngine
{
	class Enemy : public Actor
	{
	public:
		Enemy(const std::string& Name);
		virtual ~Enemy() = default;

	protected:
		virtual bool Initialise(const Param& Params) override;
	};
}