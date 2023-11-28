#pragma once

#include "Object/Actor/Actor.h"
#include "StateMachine/IState.h"
#include "Object/Component/PhysicsComponent.h"
#include "Object/Component/AtlasComponent.h"
#include "Object/Component/AnimationComponent.h"

class IsaacUI;

using namespace NPEngine;

class Isaac : public Actor
{
public:
	Delegate<void, int> OnHealthChanged;
	Delegate<void> OnLose;
	Delegate<void> OnWin;

private:
	PhysicsComponent* _PhysicsComponent = nullptr;
	AtlasComponent* _AtlasComponent = nullptr;
	AnimationComponent* _AnimationComponent = nullptr;
	IsaacUI* _IsaacUI = nullptr;

	int _CurrHP = 5;

	IState* _CurrentState = nullptr;
	std::map<std::string, IState*> _AllState;

public:
	Isaac(const std::string& Name);

	virtual Actor* Clone(const std::string& Name, const Param& Params = Param{}) override;

	virtual void TakeHit(float Damage) override;

private:
	virtual bool Initialise(const Param& Params) override;
	virtual void Destroy(const Param& Params) override;
	virtual void BeginPlay() override;

	virtual void Update(float DeltaTime) override;

	void Dead();

	void OnCollision(const std::vector<CollisionData>& CollisionsData);

public:
	void SetCurrentState(const std::string& State);
};