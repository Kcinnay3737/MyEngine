#include "Object/Actor/Enemy.h"

using namespace NPEngine;

Enemy::Enemy(const std::string& Name) : Pawn(Name)
{
}

bool Enemy::Initialise(const Param& Params)
{
    Pawn::Initialise(Params);

    return false;
}