#pragma once

#include "StateMachine/IState.h"
#include "Object/Component/AtlasComponent.h"
#include "Object/Component/AnimationComponent.h"
#include "Player/Isaac.h"

using namespace NPEngine;

class StateIsaacAlive : public IState
{
private:
	Isaac* _OwnerIsaac = nullptr;

	PhysicsComponent* _PhysicsComponent = nullptr;
	AtlasComponent* _AtlasComponent = nullptr;
	AnimationComponent* _AnimationComponent = nullptr;

	Vector2D<float> _LastVeloDir = Vector2D<float>(0.0f, 1.0f);

	Vector2D<float> _ShootDirection = Vector2D<float>(0.0f, 0.0f);

	float _ShootDelay = 0.3f;
	float _CurrShootDelay = 0.0f;

public:
	StateIsaacAlive();
	virtual ~StateIsaacAlive() = default;

	virtual void OnEnter(Object* Owner) override;
	virtual void Execute(float DeltaTime, Object* Owner) override;
	virtual void OnExit(Object* Owner) override;

	virtual void OnCollision(const std::vector<CollisionData>& CollisionsData) override;

private:
	void UpdateShoot(float DeltaTime);
	void UpdateBodyAnimation();
	void UpdateHeadAtlas();
};