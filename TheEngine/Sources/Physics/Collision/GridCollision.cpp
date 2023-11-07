#include "Physics/Collision/GridCollision.h"
#include "Physics/Collision/BoxCollision.h"
#include "Physics/Collision/SphereCollision.h"
#include "Physics/Collision/LineCollision.h"
#include "Physics/Collision/PointCollision.h"
#include "Engine.h"

using namespace NPEngine;

GridCollision::GridCollision(Actor* Owner)
{
    _Owner = Owner;
}

GridCollision::~GridCollision()
{
}

CollisionData GridCollision::CheckCollisionWithPoint(const ICollision& OtherCollision)
{
    return CollisionData();
}

CollisionData GridCollision::CheckCollisionWithBox(const ICollision& OtherCollision)
{
    return CollisionData();
}

CollisionData GridCollision::CheckCollisionWithSphere(const ICollision& OtherCollision)
{
    return CollisionData();
}

CollisionData GridCollision::CheckCollisionWithLine(const ICollision& OtherCollision)
{
    return CollisionData();
}

CollisionData GridCollision::CheckCollisionWithGrid(const ICollision& OtherCollision)
{
    return CollisionData();
}

void GridCollision::DrawCollision()
{
    std::vector<std::vector<BoxCollision>> _Grid;

    for (std::vector<BoxCollision>& Lines : _Grid)
    {
        for (BoxCollision& Box : Lines)
        {
            Box.DrawCollision();
        }
    }
}
