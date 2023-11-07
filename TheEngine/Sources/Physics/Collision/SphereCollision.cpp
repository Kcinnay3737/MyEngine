#include "Physics/Collision/SphereCollision.h"
#include "Physics/Collision/PointCollision.h"
#include "Physics/Collision/LineCollision.h"
#include "Physics/Collision/BoxCollision.h"
#include "Physics/Collision/GridCollision.h"
#include "Object/Component/TransformComponent.h"
#include "Engine.h"

using namespace NPEngine;

SphereCollision::SphereCollision(Actor* Owner)
{
    _Owner = Owner;
}

SphereCollision::~SphereCollision()
{
}

CollisionData SphereCollision::CheckCollisionWithPoint(const ICollision& OtherCollision)
{
    return CollisionData();
}

CollisionData SphereCollision::CheckCollisionWithBox(const ICollision& OtherCollision)
{
    return CollisionData();
}

CollisionData SphereCollision::CheckCollisionWithSphere(const ICollision& OtherCollision)
{
    return CollisionData();
}

CollisionData SphereCollision::CheckCollisionWithLine(const ICollision& OtherCollision)
{
    return CollisionData();
}

CollisionData SphereCollision::CheckCollisionWithGrid(const ICollision& OtherCollision)
{
    return CollisionData();
}

void SphereCollision::UpdateCollisionWithActorTransform()
{
    
}

void SphereCollision::DrawCollision()
{
    Engine::GetGraphics()->DrawCircle(_Position, _Ray);
}

void SphereCollision::SetLocationOffset(const Vector2D<float>& LocationOffset)
{
    _OffsetLocation = LocationOffset;
}