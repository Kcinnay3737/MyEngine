#pragma once

#include "Physics/Collision/ICollision.h"
#include "Physics/Collision/BoxCollision.h"

namespace NPEngine
{
	class Actor;
	class PhysicsComponent;

	class GridCollision : public ICollision
	{
	private:
		ECollisionType _CollisionType = ECollisionType::Grid;

		Actor* _OwnerActor = nullptr;
		PhysicsComponent* _OwnerPhysicsComponent = nullptr;

		std::vector<std::vector<bool>> _Grid;
		Vector2D<float> _PositionOffset = Vector2D<float>(0.0f, 0.0f);
		Vector2D<float> _CellSize = Vector2D<float>(0.0f, 0.0f);

	public:
		GridCollision(Actor* Owner, PhysicsComponent* OwnerPhysicsComponent);
		virtual ~GridCollision();

		virtual CollisionData CheckCollisionWithPoint(const ICollision& OtherCollision) const override;
		virtual CollisionData CheckCollisionWithBox(const ICollision& OtherCollision) const override;
		virtual CollisionData CheckCollisionWithSphere(const ICollision& OtherCollision) const override;
		virtual CollisionData CheckCollisionWithLine(const ICollision& OtherCollision) const override;
		virtual CollisionData CheckCollisionWithGrid(const ICollision& OtherCollision) const override;


		std::vector<Vector2D<int>> GetIndexInRect(const Rectangle2D<float>& Rect) const;

		virtual void DrawCollision() override;

		void SetGrid(std::vector<std::vector<bool>>& Grid) { _Grid = Grid; }
		const std::vector<std::vector<bool>>& GetGrid() const { return _Grid; }

		void SetPositionOffset(Vector2D<float> PositionOffset) { _PositionOffset = PositionOffset; }

		void SetCellSize(Vector2D<float> CellSize) { _CellSize = CellSize; }

		BoxCollision GetBoxCollisionAt(Vector2D<int> CellPosition) const;
	
		virtual ECollisionType GetCollisionType() const override { return _CollisionType; }

		virtual Actor* GetOwner() const override { return _OwnerActor; }
		virtual PhysicsComponent* GetOwnerPhysicsComponent() const  override { return _OwnerPhysicsComponent; }
	};
}