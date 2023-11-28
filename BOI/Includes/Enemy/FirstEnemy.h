#pragma once

#include "Object/Actor/AI.h"
#include "Object/Component/PhysicsComponent.h"
#include "Object/Component/AnimationComponent.h"

using namespace NPEngine;

class Isaac;

class FirstEnemy : public AI
{
public:

private:
	PhysicsComponent* _PhysicsComponent = nullptr;
	AnimationComponent* _AnimationComponent = nullptr;

	Isaac* _Player = nullptr;

	Vector2D<float> _LastVeloDir = Vector2D<float>(0.0f, 0.0f);

	float _LastDistance = 0.0f;

	double _CurrentReward = 0.0f;

	bool _bCanAttack = true;
	float _AttackDelay = 1.0f;
	float _CurrAttackDelay = 0.0f;

	int _CurrentHealth = 3;

public:
	FirstEnemy(const std::string& Name);
	virtual ~FirstEnemy() = default;

	virtual Actor* Clone(const std::string& Name, const Param& Params = Param{});

	virtual void TakeHit(float Damage) override;

protected:
	virtual bool Initialise(const Param& Params) override;
	virtual void Destroy(const Param& Params) override;

	virtual void BeginPlay() override;
	virtual void Update(float DeltaTime) override;
	virtual void Draw() override;

	//AI function
	virtual int GetCurrentState();
	virtual void PerformAction(int Action);
	virtual int GetNewState();
	virtual double GetReward();
	//----------

private:
	void OnCollision(const std::vector<CollisionData>& CollisionsData);

};