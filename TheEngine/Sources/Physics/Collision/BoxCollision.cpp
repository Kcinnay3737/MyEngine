#include "Physics/Collision/BoxCollision.h"
#include "Physics/Collision/SphereCollision.h"
#include "Physics/Collision/LineCollision.h"
#include "Physics/Collision/PointCollision.h"
#include "Physics/Collision/GridCollision.h"

using namespace NPEngine;

BoxCollision::BoxCollision(Actor* Owner)
{
    _Owner = Owner;
}

BoxCollision::~BoxCollision()
{
}

CollisionData BoxCollision::CheckCollisionWithPoint(const ICollision& OtherCollision)
{
    return CollisionData();
}

CollisionData BoxCollision::CheckCollisionWithBox(const ICollision& OtherCollision)
{
    return CollisionData();
}

CollisionData BoxCollision::CheckCollisionWithSphere(const ICollision& OtherCollision)
{
    return CollisionData();
}

CollisionData BoxCollision::CheckCollisionWithLine(const ICollision& OtherCollision)
{
    return CollisionData();
}

CollisionData BoxCollision::CheckCollisionWithGrid(const ICollision& OtherCollision)
{
    return CollisionData();
}