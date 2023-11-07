#include "Physics/Collision/BoxCollision.h"
#include "Physics/Collision/SphereCollision.h"
#include "Physics/Collision/LineCollision.h"
#include "Physics/Collision/PointCollision.h"
#include "Physics/Collision/GridCollision.h"
#include "Object/Actor/Actor.h"
#include "Object/Component/TransformComponent.h"
#include "Engine.h"

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
    if (OtherCollision.GetCollisionType() != ECollisionType::Point) return CollisionData();

    const PointCollision& OtherPointCollision = static_cast<const PointCollision&>(OtherCollision);

    bool bIsColliding = false;

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

void BoxCollision::UpdateCollisionWithActorTransform()
{
    if (!_Owner)
    {

    }

    //TransformComponent* CurrTransformComponent = _Owner->
}

void BoxCollision::DrawCollision()
{
    Engine::GetGraphics()->DrawRect(_Rectangle);
}

void BoxCollision::SetLocationOffset(const Vector2D<float>& LocationOffset)
{
    _OffsetLocation = LocationOffset;
}
