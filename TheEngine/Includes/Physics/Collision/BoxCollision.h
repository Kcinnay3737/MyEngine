#pragma once

#include "Physics/Collision/ICollision.h"

namespace NPEngine
{
	class Actor;

	class BoxCollision : public ICollision
	{
	private:
		ECollisionType _CollisionType = ECollisionType::Box;

		Actor* _Owner = nullptr;

		Vector2D<float> _OffsetLocation = Vector2D<float>(0.0f, 0.0f);
		Rectangle2D<float> _Rectangle = Rectangle2D<float>(Vector2D<float>(0.0f, 0.0f), Vector2D<float>(0.0f, 0.0f));

	public:
		BoxCollision(Actor* Owner);
		virtual ~BoxCollision();

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