#pragma once

#include "Physics/Collision/ICollision.h"
#include "Physics/Collision/BoxCollision.h"

namespace NPEngine
{
	class Actor;

	class GridCollision : public ICollision
	{
	private:
		ECollisionType _CollisionType = ECollisionType::Grid;

		Actor* _Owner = nullptr;

		Vector2D<float> _OffsetLocation = Vector2D<float>(0.0f, 0.0f);
		std::vector<std::vector<BoxCollision>> _Grid;

	public:
		GridCollision(Actor* Owner);
		virtual ~GridCollision();

		virtual CollisionData CheckCollisionWithPoint(const ICollision& OtherCollision) const override;
		virtual CollisionData CheckCollisionWithBox(const ICollision& OtherCollision) const override;
		virtual CollisionData CheckCollisionWithSphere(const ICollision& OtherCollision) const override;
		virtual CollisionData CheckCollisionWithLine(const ICollision& OtherCollision) const override;
		virtual CollisionData CheckCollisionWithGrid(const ICollision& OtherCollision) const override;

		virtual void UpdateCollisionWithActorTransform() override;

		virtual void DrawCollision() override;
	
		virtual void SetLocationOffset(const Vector2D<float>& LocationOffset) override;
		virtual ECollisionType GetCollisionType() const override { return _CollisionType; }
	};
}