#include "Object/Actor/Pawn.h"
#include "Object/Component/SpriteComponent.h"
#include "Object/Component/PhysicsComponent.h"

using namespace NPEngine;

Pawn::Pawn(const std::string& Name) : Actor(Name)
{
}

bool Pawn::Initialise(const Param& Params)
{
	Actor::Initialise(Params);

	CreateComponentOfClass<PhysicsComponent>(std::string("PhysicsComponent"));

	return true;
}

Actor* Pawn::Clone(std::string& Name, const Param& Params)
{
	Pawn* NewPawn = new Pawn(Name);

	return NewPawn;
}
