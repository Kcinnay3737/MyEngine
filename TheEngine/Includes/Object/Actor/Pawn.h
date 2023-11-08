#pragma once

#include "Object/Actor/Actor.h"

namespace NPEngine
{
	class Pawn : public Actor
	{
	public:
		Pawn(std::string& Name);
		virtual ~Pawn() = default;

	protected:
		virtual bool Initialise(const Param& Params) override;
	};
}