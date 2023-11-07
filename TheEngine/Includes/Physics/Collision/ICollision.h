#pragma once

#include "Utility/Utility.h"
#include "Physics/Collision/CollisionData.h"
#include "Physics/PhysicsEnum.h"

namespace NPEngine
{
	class ICollision
	{
	public:
		virtual ~ICollision() = default;

		virtual CollisionData CheckCollisionWithPoint(const ICollision& OtherCollision) = 0;
		virtual CollisionData CheckCollisionWithBox(const ICollision& OtherCollision) = 0;
		virtual CollisionData CheckCollisionWithSphere(const ICollision& OtherCollision) = 0;
		virtual CollisionData CheckCollisionWithLine(const ICollision& OtherCollision) = 0;
		virtual CollisionData CheckCollisionWithGrid(const ICollision& OtherCollision) = 0;

		virtual ECollisionType GetCollisionType() const = 0;
	};
}