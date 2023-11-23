#include "Object/Actor/AI.h"
#include "AI/AITBQlearning.h"

using namespace NPEngine;

AI::AI(const std::string& Name) : Actor(Name)
{
}

Actor* AI::Clone(const std::string& Name, const Param& Params)
{
	AI* NewAI = new AI(Name);
	return NewAI;
}

bool AI::Initialise(const Param& Params)
{
	bool bSucces = Actor::Initialise(Params);

	_IAQLearning = new AITBQLearning();

	return bSucces;
}

void AI::Destroy(const Param& Params)
{
	Actor::Destroy(Params);
}

void AI::BeginPlay()
{
	Actor::BeginPlay();


}

void AI::Update(float DeltaTime)
{
	Actor::Update(DeltaTime);
}
