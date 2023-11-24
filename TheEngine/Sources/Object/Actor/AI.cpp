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

	_IAQLearning = new AITBQLearning(0, 0, 0.0, 0.0, 0.0);

	return bSucces;
}

void AI::Destroy(const Param& Params)
{
	Actor::Destroy(Params);

	delete _IAQLearning;
}

void AI::BeginPlay()
{
	Actor::BeginPlay();

}

void AI::Update(float DeltaTime)
{
	Actor::Update(DeltaTime);

	int CurrentState = GetCurrentState();

	int Action = _IAQLearning->GetAction(CurrentState);

	PerformAction(Action);

	int NewState = ObserveNewState();
	double Reward = ObserveReward();

	_IAQLearning->UpdateQTable(CurrentState, Action, Reward, NewState);
}

int AI::GetCurrentState()
{
	return 0;
}

void AI::PerformAction(int Action)
{
}

int AI::ObserveNewState()
{
	return 0;
}

double AI::ObserveReward()
{
	return 0.0;
}
