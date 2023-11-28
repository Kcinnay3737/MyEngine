#pragma once

#include "Object/Actor/Actor.h"
#include "Object/Component/AtlasComponent.h"
#include "Object/Component/PhysicsComponent.h"

using namespace NPEngine;

class Door : public Actor
{
private:
	AtlasComponent* _AtlasComponent = nullptr;
	PhysicsComponent* _PhysicsComponent = nullptr;

	bool _bIsOpen = false;

	std::string _OpenLevelName = "";

	int _NumberOfMonsterAlive = 0;

public:
	Door(const std::string& Name);
	virtual ~Door() = default;

	virtual Actor* Clone(const std::string& Name, const Param& Params = Param{});

	void Close();
	void Open();

	void AddMonsterAlive();
	void PopMonsterAlive();

private:
	virtual bool Initialise(const Param& Params) override;

	virtual void BeginPlay() override;

	void OnCollision(const std::vector<CollisionData>& CollisionsData);

	void OpenLevel();

public:
	void SetOpenLevelName(const std::string& LevelName) { _OpenLevelName = LevelName; }
};