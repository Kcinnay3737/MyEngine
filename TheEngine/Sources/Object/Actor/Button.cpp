#include "Object/Actor/Button.h"

using namespace NPEngine;

Button::Button(std::string& Name) : Actor(Name)
{
}

bool Button::Initialise(const Param& Params)
{
	Actor::Initialise(Params);

	return false;
}
