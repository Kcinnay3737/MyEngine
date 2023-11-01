#pragma once

#include "Object/Actor/Actor.h"

using namespace NPEngine;

class Isaac : public Actor
{
public:
	Isaac(std::string& Name);

	virtual Actor* Clone(std::string& Name) override;

private:
	virtual void Draw() override;
};