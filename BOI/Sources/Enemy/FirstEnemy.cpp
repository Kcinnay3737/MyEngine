#include "Enemy/FirstEnemy.h"

FirstEnemy::FirstEnemy(const std::string& Name) : AI(Name)
{
}

Actor* FirstEnemy::Clone(const std::string& Name, const Param& Params)
{
	FirstEnemy* NewFirstEnemy = new FirstEnemy(Name);
	return NewFirstEnemy;
}

bool FirstEnemy::Initialise(const Param& Params)
{
	bool bSucces = AI::Initialise(Params);

	return bSucces;
}

void FirstEnemy::Destroy(const Param& Params)
{
	AI::Destroy(Params);
}

void FirstEnemy::BeginPlay()
{
	AI::BeginPlay();
}

void FirstEnemy::Update(float DeltaTime)
{
	AI::Update(DeltaTime);
}

int FirstEnemy::GetCurrentState()
{
	return 0;
}

void FirstEnemy::PerformAction(int Action)
{
}

int FirstEnemy::GetNewState()
{
	return 0;
}

double FirstEnemy::GetReward()
{
	return 0.0;
}
