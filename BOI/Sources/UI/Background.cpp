#include "UI/Background.h"
#include "Object/Component/SpriteComponent.h"

Background::Background(const std::string& Name) : Actor(Name)
{
}

bool Background::Initialise(const Param& Params)
{
	Actor::Initialise(Params);

	CreateComponentOfClass<SpriteComponent>(std::string("SpriteComponent"), Params);

	return true;
}


Actor* Background::Clone(const std::string& Name, const Param& Params)
{
	Background* NewBackground = new  Background(Name);
	return NewBackground;
}