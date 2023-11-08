#include "Object/Actor/Player.h"
#include "Object/Component/ControllerComponent.h"

using namespace NPEngine;

Player::Player(std::string& Name) : Pawn(Name)
{
}

bool Player::Initialise(const Param& Params)
{
	Pawn::Initialise(Params);

	CreateComponentOfClass<ControllerComponent>(std::string("ControllerComponent"));

	return true;
}
