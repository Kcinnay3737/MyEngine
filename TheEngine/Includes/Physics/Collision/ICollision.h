#pragma once

#include "Utility/Utility.h"
#include "Physics/Collision/CollisionData.h"
#include "Physics/PhysicsEnum.h"

namespace NPEngine
{
	class Actor;
	class PhysicsComponent;

	class ICollision
	{
	public:
		virtual ~ICollision() = default;

		virtual CollisionData CheckCollisionWithPoint(const ICollision& OtherCollision) const = 0;
		virtual CollisionData CheckCollisionWithBox(const ICollision& OtherCollision) const = 0;
		virtual CollisionData CheckCollisionWithSphere(const ICollision& OtherCollision) const = 0;
		virtual CollisionData CheckCollisionWithLine(const ICollision& OtherCollision) const = 0;
		virtual CollisionData CheckCollisionWithGrid(const ICollision& OtherCollision) const = 0;

		virtual void DrawCollision() = 0;

		virtual ECollisionType GetCollisionType() const = 0;

		virtual Actor* GetOwner() const = 0;
		virtual PhysicsComponent* GetOwnerPhysicsComponent() const = 0;
	};
}