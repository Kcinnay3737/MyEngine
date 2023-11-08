#include "Object/Actor/Pawn.h"
#include "Object/Component/SpriteComponent.h"
#include "Object/Component/PhysicsComponent.h"

using namespace NPEngine;

Pawn::Pawn(std::string& Name) : Actor(Name)
{
}

bool Pawn::Initialise(const Param& Params)
{
	Actor::Initialise(Params);

	CreateComponentOfClass<SpriteComponent>(std::string("SpriteComponent"));

	CreateComponentOfClass<PhysicsComponent>(std::string("PhysicsComponent"));

	return true;
}
