#pragma once

#include "Object/Actor/Pawn.h"

namespace NPEngine
{
	class Enemy : public Pawn
	{
	public:
		Enemy(const std::string& Name);
		virtual ~Enemy() = default;

	protected:
		virtual bool Initialise(const Param& Params) override;
	};
}