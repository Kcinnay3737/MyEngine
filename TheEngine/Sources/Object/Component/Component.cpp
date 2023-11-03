#include "Object/Component/Component.h"

using namespace NPEngine;

Component::Component(std::string& Name) : Object()
{
	_Name = Name;
}

Component::~Component()
{
}

bool Component::Initialise(const Param& Params)
{
	return true;
}

void Component::Destroy(const Param& Params)
{
}

void Component::BeginPlay()
{
}

void Component::SetOwner(Actor* Owner)
{
	_OwnerActor = Owner;
}