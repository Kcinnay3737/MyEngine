#pragma once

#include "StateMachine/IState.h"

using namespace NPEngine;

class StateIsaacWin : public IState
{
private:
	float _DelayRestart = 2.0f;
	float _CurrentDelayRestart = 0.0f;

public:
	StateIsaacWin();
	virtual ~StateIsaacWin() = default;

	virtual void OnEnter(Object* Owner) override;
	virtual void Execute(float DeltaTime, Object* Owner) override;
	virtual void OnExit(Object* Owner) override;

	virtual void OnCollision(const std::vector<CollisionData>& CollisionsData) override;
};