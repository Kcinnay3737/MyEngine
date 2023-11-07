#pragma once

#include "Physics/IPhysics.h"

namespace NPEngine
{
	class Actor;

	class Physics : public IPhysics
	{
	public:
		virtual ~Physics() = default;

	private:
		std::map<std::string, const Actor*> _PhysicsActors;

		virtual bool Initialize(const Param& Params = Param{}) override;
		virtual void Shutdown(const Param& Params = Param{}) override;

		virtual void UpdatePhysics(float DeltaTime) override;

		virtual void AddPhysicsActor(const Actor* ActorToAdd) override;
		virtual void RemovePhysicsActor(const std::string& Name) override;

		virtual void OnPhysicsComponentStateChanged(const std::string& Name) override;

		virtual void UpdatePositions(float DeltaTime) override;
		virtual void DetectCollisions() override;
		virtual void ResolveCollisions() override;

		virtual std::vector<CollisionData> CheckCollisionWith(const ICollision& Collision) override;
	};
}