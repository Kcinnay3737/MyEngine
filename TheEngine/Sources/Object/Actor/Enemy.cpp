#include "Object/Actor/Enemy.h"

using namespace NPEngine;

Enemy::Enemy(const std::string& Name) : Actor(Name)
{
}

bool Enemy::Initialise(const Param& Params)
{
    Actor::Initialise(Params);

    return true;
}
