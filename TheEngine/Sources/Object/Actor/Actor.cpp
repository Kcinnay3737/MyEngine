#include "Object/Actor/Actor.h"
#include "Engine.h"

using namespace NPEngine;

Actor::Actor(std::string& Name) : Object()
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

Actor* Actor::Clone(std::string& Name)
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

void Actor::SetDrawDepth(unsigned char DrawDepth)
{
	_DrawDepth = DrawDepth;

	Engine::GetWorld()->ResetDrawOrder();
}