#pragma once

#include "Object/Actor/Actor.h"

namespace NPEngine
{
	class Button : public Actor
	{
	public:
		Button(const std::string& Name);
		virtual ~Button() = default;

	protected:
		virtual bool Initialise(const Param& Params) override;
	};
}