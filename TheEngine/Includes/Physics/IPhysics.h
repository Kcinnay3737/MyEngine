#pragma once

#include "Physics/IPhysicsProvider.h"
#include "Physics/Collision/CollisionData.h"

namespace NPEngine
{
	class ICollision;

	class IPhysics : public IPhysicsProvider
	{
	public:
		virtual ~IPhysics() = default;

		virtual std::vector<CollisionData> CheckCollisionWith(const ICollision& Collision) = 0;

	private:
		virtual bool Initialize(const Param& Params = Param{}) override = 0;
		virtual void Shutdown(const Param& Params = Param{}) override = 0;

		virtual void UpdatePhysics(float DeltaTime) override = 0;

		virtual void AddPhysicsActor(const std::string& ActorName, PhysicsComponent* PhysicsComponentToAdd) override = 0;
		virtual void RemovePhysicsActor(const std::string& Name) override = 0;

		virtual void OnPhysicsComponentStateChanged(const std::string& Name) override = 0;

		virtual void UpdatePositions(float DeltaTime) = 0;
		virtual void DetectCollisions() = 0;
		virtual void ResolveCollisions() = 0;
	};
}