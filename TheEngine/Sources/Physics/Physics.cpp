#include "Physics/Physics.h"
#include "Object/Actor/Actor.h"

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
    

    //Update collision

    //Update movement
}

void Physics::AddPhysicsActor(const Actor* ActorToAdd)
{
    if (!ActorToAdd) return;
    _PhysicsActors[ActorToAdd->GetName()] = ActorToAdd;
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
