#pragma once

#include "Object/Actor/Actor.h"

namespace NPEngine
{
	class Pawn : public Actor
	{
	public:
		Pawn(const std::string& Name);
		virtual ~Pawn() = default;

		virtual Actor* Clone(std::string& Name, const Param& Params = Param{}) override;

	protected:
		virtual bool Initialise(const Param& Params) override;
	};
}