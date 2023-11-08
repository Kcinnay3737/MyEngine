#pragma once

#include "Object/Actor/Player.h"

using namespace NPEngine;

class Isaac : public Player
{
public:
	Isaac(std::string& Name);

	virtual Actor* Clone(std::string& Name, const Param& Params = Param{}) override;
};