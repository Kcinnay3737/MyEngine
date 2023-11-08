#pragma once

#include "Object/Actor/Pawn.h"

namespace NPEngine
{
	class Player : public Pawn
	{
	public:
		Player(std::string& Name);
		virtual ~Player() = default;

	protected:
		virtual bool Initialise(const Param& Params) override;
	};
}