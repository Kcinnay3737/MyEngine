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

void Isaac::Bob(const DataKey& pDataKey)
{
	Engine::GetLogger()->LogMessage("testo");
}

void Isaac::Draw()
{
	
}

void Isaac::Update(float dt)
{
	
}
