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

		std::vector<std::vector<BoxCollision>> _Grid;

	public:
		GridCollision(Actor* Owner);
		virtual ~GridCollision();

		virtual CollisionData CheckCollisionWithPoint(const ICollision& OtherCollision) override;
		virtual CollisionData CheckCollisionWithBox(const ICollision& OtherCollision) override;
		virtual CollisionData CheckCollisionWithSphere(const ICollision& OtherCollision) override;
		virtual CollisionData CheckCollisionWithLine(const ICollision& OtherCollision) override;
		virtual CollisionData CheckCollisionWithGrid(const ICollision& OtherCollision) override;
	
		virtual ECollisionType GetCollisionType() override { return _CollisionType; }
	};
}