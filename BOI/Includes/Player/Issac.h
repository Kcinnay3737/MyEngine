#pragma once

#include "Object/Actor/Actor.h"
#include "Object/Component/PhysicsComponent.h"
#include "Object/Component/AtlasComponent.h"
#include "Object/Component/AnimationComponent.h"

using namespace NPEngine;

class Isaac : public Actor
{
private:
	Vector2D<float> _LastVeloDir = Vector2D<float>(0.0f, 1.0f);

	Vector2D<float> _ShootDirection = Vector2D<float>(0.0f, 0.0f);

	PhysicsComponent* _PhysicsComponent = nullptr;
	AtlasComponent* _AtlasComponent = nullptr;
	AnimationComponent* _AnimationComponent = nullptr;

	float _ShootDelay = 0.3f;
	float _CurrShootDelay = 0.0f;

public:
	Isaac(const std::string& Name);

	virtual Actor* Clone(const std::string& Name, const Param& Params = Param{}) override;

private:
	virtual bool Initialise(const Param& Params) override;
	virtual void BeginPlay() override;

	virtual void Update(float DeltaTime) override;

	void UpdateShoot(float DeltaTime);
	void UpdateBodyAnimation();
	void UpdateHeadAtlas();
};