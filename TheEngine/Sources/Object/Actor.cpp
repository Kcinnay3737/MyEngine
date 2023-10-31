#include "Object/Actor.h"

using namespace NPEngine;

Actor::Actor(const char* Name) : Object()
{
	_Name = Name;
}

Actor::~Actor()
{
	
}

bool Actor::Initialise(const Param& Params)
{
	return true;
}

void Actor::Destroy(const Param& Params)
{
}

Actor* Actor::Clone(const char* Name)
{
	Actor* CloneActor = new Actor(Name);
	return CloneActor;
}

void Actor::BeginPlay()
{
}

void Actor::Update(float dt)
{
}

void Actor::Draw()
{
}
