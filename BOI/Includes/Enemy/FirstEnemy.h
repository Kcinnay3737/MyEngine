#pragma once

#include "Object/Actor/AI.h"

using namespace NPEngine;

class FirstEnemy : public AI
{
public:

private:

public:
	FirstEnemy(const std::string& Name);
	virtual ~FirstEnemy() = default;

	virtual Actor* Clone(const std::string& Name, const Param& Params = Param{});

protected:
	virtual bool Initialise(const Param& Params) override;
	virtual void Destroy(const Param& Params) override;

	virtual void BeginPlay() override;
	virtual void Update(float DeltaTime) override;

	//AI function
	virtual int GetCurrentState();
	virtual void PerformAction(int Action);
	virtual int GetNewState();
	virtual double GetReward();
	//----------

};