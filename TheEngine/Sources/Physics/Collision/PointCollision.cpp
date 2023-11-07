#include "Physics/Collision/PointCollision.h"
#include "Physics/Collision/LineCollision.h"
#include "Physics/Collision/BoxCollision.h"
#include "Physics/Collision/SphereCollision.h"
#include "Physics/Collision/GridCollision.h"
#include "Engine.h"

using namespace NPEngine;

PointCollision::PointCollision(Actor* Owner)
{
    _Owner = Owner;
}

PointCollision::~PointCollision()
{
}

CollisionData PointCollision::CheckCollisionWithPoint(const ICollision& OtherCollision)
{
    return CollisionData();
}

CollisionData PointCollision::CheckCollisionWithBox(const ICollision& OtherCollision)
{
    return CollisionData();
}

CollisionData PointCollision::CheckCollisionWithSphere(const ICollision& OtherCollision)
{
    return CollisionData();
}

CollisionData PointCollision::CheckCollisionWithLine(const ICollision& OtherCollision)
{
    return CollisionData();
}

CollisionData PointCollision::CheckCollisionWithGrid(const ICollision& OtherCollision)
{
    return CollisionData();
}

void PointCollision::DrawCollision()
{
    Engine::GetGraphics()->DrawPoint(_Point);
}
