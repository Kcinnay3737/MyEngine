#include "Player/Issac.h"
#include "Engine.h"

Isaac::Isaac(const char* Name) : Actor::Actor(Name)
{

}

void Isaac::Draw()
{
	Engine::GetLogger()->LogMessage("testo");
}
