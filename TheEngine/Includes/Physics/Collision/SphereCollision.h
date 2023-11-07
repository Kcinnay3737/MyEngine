#pragma once

#include "Physics/Collision/ICollision.h"

namespace NPEngine
{
	class Actor;

	class SphereCollision : public ICollision
	{
	private:
		ECollisionType _CollisionType = ECollisionType::Sphere;

		Actor* _Owner = nullptr;

	public:
		SphereCollision(Actor* Owner);
		virtual ~SphereCollision();

		virtual CollisionData CheckCollisionWithPoint(const ICollision& OtherCollision) override;
		virtual CollisionData CheckCollisionWithBox(const ICollision& OtherCollision) override;
		virtual CollisionData CheckCollisionWithSphere(const ICollision& OtherCollision) override;
		virtual CollisionData CheckCollisionWithLine(const ICollision& OtherCollision) override;
		virtual CollisionData CheckCollisionWithGrid(const ICollision& OtherCollision) override;

		virtual ECollisionType GetCollisionType() override { return _CollisionType; }
	};
}