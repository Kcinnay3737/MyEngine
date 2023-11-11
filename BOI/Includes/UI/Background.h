#pragma once

#include "Object/Actor/Actor.h"

using namespace NPEngine;

class Background : public Actor
{
private:

public:
	Background(const std::string& Name);
	virtual ~Background() = default;

	virtual Actor* Clone(std::string& Name, const Param& Params = Param{}) override;

private:
	virtual bool Initialise(const Param& Params) override;

};