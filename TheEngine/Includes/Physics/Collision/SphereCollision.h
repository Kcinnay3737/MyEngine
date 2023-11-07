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

		Vector2D<float> _OffsetLocation = Vector2D<float>(0.0f, 0.0f);
		Vector2D<float> _Position = Vector2D<float>(0.0f, 0.0f);
		float _Ray = 0.0f;

	public:
		SphereCollision(Actor* Owner);
		virtual ~SphereCollision();

		virtual CollisionData CheckCollisionWithPoint(const ICollision& OtherCollision) override;
		virtual CollisionData CheckCollisionWithBox(const ICollision& OtherCollision) override;
		virtual CollisionData CheckCollisionWithSphere(const ICollision& OtherCollision) override;
		virtual CollisionData CheckCollisionWithLine(const ICollision& OtherCollision) override;
		virtual CollisionData CheckCollisionWithGrid(const ICollision& OtherCollision) override;

		virtual void UpdateCollisionWithActorTransform() override;

		virtual void DrawCollision() override;

		virtual void SetLocationOffset(const Vector2D<float>& LocationOffset) override;
		virtual ECollisionType GetCollisionType() const override { return _CollisionType; }
	};
}