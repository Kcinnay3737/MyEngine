#include "Physics/Collision/LineCollision.h"
#include "Physics/Collision/BoxCollision.h"
#include "Physics/Collision/SphereCollision.h"
#include "Physics/Collision/PointCollision.h"
#include "Physics/Collision/GridCollision.h"
#include "Object/Component/TransformComponent.h"
#include "Engine.h"

using namespace NPEngine;

LineCollision::LineCollision(Actor* Owner)
{
    _Owner = Owner;
}

LineCollision::~LineCollision()
{
}

CollisionData LineCollision::CheckCollisionWithPoint(const ICollision& OtherCollision)
{
    return CollisionData();
}

CollisionData LineCollision::CheckCollisionWithBox(const ICollision& OtherCollision)
{
    return CollisionData();
}

CollisionData LineCollision::CheckCollisionWithSphere(const ICollision& OtherCollision)
{
    return CollisionData();
}

CollisionData LineCollision::CheckCollisionWithLine(const ICollision& OtherCollision)
{
    return CollisionData();
}

CollisionData LineCollision::CheckCollisionWithGrid(const ICollision& OtherCollision)
{
    return CollisionData();
}

void LineCollision::UpdateCollisionWithActorTransform()
{
}

void LineCollision::DrawCollision()
{
    Engine::GetGraphics()->DrawLine(_StartPoint, _EndPoint);
}

void LineCollision::SetLocationOffset(const Vector2D<float>& LocationOffset)
{
    _OffsetLocation = LocationOffset;
}