#pragma once

#include "Object/Actor.h"

using namespace NPEngine;

class Isaac : public Actor
{
public:
	Isaac(const char* Name);

private:
	virtual void Draw() override;
};