#pragma once

#include "Object/Actor/Actor.h"
#include "Input/IInput.h"

using namespace NPEngine;

class Isaac : public Actor
{
public:
	Isaac(std::string& Name);

	virtual Actor* Clone(std::string& Name) override;

	void Bob(const DataKey& pDataKey);
private:
	virtual void Draw() override;
	virtual void Update(float dt) override;

	
};