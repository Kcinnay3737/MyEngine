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
		PhysicsComponent* _OwnerPhysicsComponent = nullptr;

		Vector2D<float> _PositionOffset = Vector2D<float>(0.0f, 0.0f);

	public:
		PointCollision(Actor* Owner);
		virtual ~PointCollision();

		virtual CollisionData CheckCollisionWithPoint(const ICollision& OtherCollision) const override;
		virtual CollisionData CheckCollisionWithBox(const ICollision& OtherCollision) const override;
		virtual CollisionData CheckCollisionWithSphere(const ICollision& OtherCollision) const override;
		virtual CollisionData CheckCollisionWithLine(const ICollision& OtherCollision) const override;
		virtual CollisionData CheckCollisionWithGrid(const ICollision& OtherCollision) const override;

		virtual void DrawCollision() override;

		void SetPositionOffset(const Vector2D<float>& PositionOffset);
		Vector2D<float> GetPositionOffset() const { return _PositionOffset; }
		Vector2D<float> GetPosition() const;

		virtual ECollisionType GetCollisionType() const override { return _CollisionType; }

		virtual Actor* GetOwner() const override { return _Owner; }
		virtual PhysicsComponent* GetOwnerPhysicsComponent() const  override { return _OwnerPhysicsComponent; }
	};
}