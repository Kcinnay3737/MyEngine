#include "Physics/Collision/PointCollision.h"
#include "Physics/Collision/LineCollision.h"
#include "Physics/Collision/BoxCollision.h"
#include "Physics/Collision/SphereCollision.h"
#include "Physics/Collision/GridCollision.h"
#include "Object/Component/TransformComponent.h"
#include "Engine.h"

using namespace NPEngine;

PointCollision::PointCollision(Actor* Owner)
{
    _Owner = Owner;
}

PointCollision::~PointCollision()
{
}

CollisionData PointCollision::CheckCollisionWithPoint(const ICollision& OtherCollision) const
{
    return CollisionData();
}

CollisionData PointCollision::CheckCollisionWithBox(const ICollision& OtherCollision) const
{
    return CollisionData();
}

CollisionData PointCollision::CheckCollisionWithSphere(const ICollision& OtherCollision) const
{
    return CollisionData();
}

CollisionData PointCollision::CheckCollisionWithLine(const ICollision& OtherCollision) const
{
    return CollisionData();
}

CollisionData PointCollision::CheckCollisionWithGrid(const ICollision& OtherCollision) const
{
    return CollisionData();
}

void PointCollision::UpdateCollisionWithActorTransform()
{
}

void PointCollision::DrawCollision()
{
    Engine::GetGraphics()->DrawPoint(_Point);
}

void PointCollision::SetLocationOffset(const Vector2D<float>& LocationOffset)
{
    _OffsetLocation = LocationOffset;
}