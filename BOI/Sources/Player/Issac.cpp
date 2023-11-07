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
	
}

void Isaac::Draw()
{
	Engine::GetGraphics()->DrawCircle(Vector2D<float>(300.0f, 300.0f), 50);
}

void Isaac::Update(float dt)
{
	Engine::GetLogger()->LogMessage("testo");
}
