#include "Player/Issac.h"
#include "Engine.h"

Isaac::Isaac(std::string& Name) : Actor::Actor(Name)
{

}

Actor* Isaac::Clone(std::string& Name)
{
	Isaac* CopyIsaac = new Isaac(Name);
	return CopyIsaac;
}

void Isaac::Draw()
{
	Engine::GetLogger()->LogMessage("testo");
}
