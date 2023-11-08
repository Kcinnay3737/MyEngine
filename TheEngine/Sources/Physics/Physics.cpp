#include "Physics/Physics.h"
#include "Object/Actor/Actor.h"
#include "Object/Component/PhysicsComponent.h"
#include "Physics/Collision/ICollision.h"

using namespace NPEngine;

bool Physics::Initialize(const Param& Params)
{
    return true;
}

void Physics::Shutdown(const Param& Params)
{
}

void Physics::UpdatePhysics(float DeltaTime)
{
    for (auto& IT : _PhysicsActors)
    {
        PhysicsComponent* CurrPhysicsComponent = IT.second;
        if(!CurrPhysicsComponent) continue;
        
        CurrPhysicsComponent->ApplyVelocity(DeltaTime);
    }


    //Appliquer les Forces

    //Mettre a jour velo

    //Detecter les collision

}

void Physics::AddPhysicsActor(const std::string& ActorName, PhysicsComponent* PhysicsComponentToAdd)
{
    if (!PhysicsComponentToAdd) return;

    _PhysicsActors[ActorName] = PhysicsComponentToAdd;
}

void Physics::RemovePhysicsActor(const std::string& Name)
{
    _PhysicsActors.erase(Name);
}

void Physics::OnPhysicsComponentStateChanged(const std::string& Name)
{
}

void Physics::UpdatePositions(float DeltaTime)
{
}

void Physics::DetectCollisions()
{
}

void Physics::ResolveCollisions()
{
}

std::vector<CollisionData> Physics::CheckCollisionWith(const ICollision& Collision)
{
    std::vector<CollisionData> CollisionsData;

    for (auto& IT : _PhysicsActors)
    {
        const PhysicsComponent* OtherPhysicsComponent = IT.second;
        const ICollision* OtherCollision = OtherPhysicsComponent->GetCollision();
        if(!OtherCollision) continue;
        
        CollisionData CurrCollisionData = CollisionData();

        switch (OtherCollision->GetCollisionType())
        {
        case ECollisionType::Box:
            CurrCollisionData = Collision.CheckCollisionWithBox(*OtherCollision);
            break;
        case ECollisionType::Grid:
            CurrCollisionData = Collision.CheckCollisionWithGrid(*OtherCollision);
            break;
        case ECollisionType::Line:
            CurrCollisionData = Collision.CheckCollisionWithLine(*OtherCollision);
            break;
        case ECollisionType::Point:
            CurrCollisionData = Collision.CheckCollisionWithPoint(*OtherCollision);
            break;
        case ECollisionType::Sphere:
            CurrCollisionData = Collision.CheckCollisionWithSphere(*OtherCollision);
            break;
        case ECollisionType::None:
            break;
        }
    }
    
    return CollisionsData;
}
