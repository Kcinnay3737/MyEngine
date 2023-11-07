#pragma once

#include "Physics/Collision/ICollision.h"

namespace NPEngine
{
	class Actor;

	class PointCollision : public ICollision
	{
	private:
		ECollisionType _CollisionType = ECollisionType::Point;

		Actor* _Owner = nullptr;

		Vector2D<float> Point = Vector2D<float>(0.0f, 0.0f);

	public:
		PointCollision(Actor* Owner);
		virtual ~PointCollision();

		virtual CollisionData CheckCollisionWithPoint(const ICollision& OtherCollision) override;
		virtual CollisionData CheckCollisionWithBox(const ICollision& OtherCollision) override;
		virtual CollisionData CheckCollisionWithSphere(const ICollision& OtherCollision) override;
		virtual CollisionData CheckCollisionWithLine(const ICollision& OtherCollision) override;
		virtual CollisionData CheckCollisionWithGrid(const ICollision& OtherCollision) override;

		virtual ECollisionType GetCollisionType() const override { return _CollisionType; }
	};
}