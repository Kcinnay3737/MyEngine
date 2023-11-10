#pragma once

#include "Physics/Collision/ICollision.h"

namespace NPEngine
{
	class Actor;
	class PhysicsComponent;

	class BoxCollision : public ICollision
	{
	private:
		ECollisionType _CollisionType = ECollisionType::Box;

		Actor* _OwnerActor = nullptr;
		PhysicsComponent* _OwnerPhysicsComponent = nullptr;

		Vector2D<float> _PositionOffset = Vector2D<float>(0.0f, 0.0f);
		Vector2D<float> _SizeOffset = Vector2D<float>(0.0f, 0.0f);

	public:
		BoxCollision(Actor* Owner, PhysicsComponent* OwnerPhysicsComponent);
		virtual ~BoxCollision();

		virtual CollisionData CheckCollisionWithPoint(const ICollision& OtherCollision) const override;
		virtual CollisionData CheckCollisionWithBox(const ICollision& OtherCollision) const override;
		virtual CollisionData CheckCollisionWithSphere(const ICollision& OtherCollision) const override;
		virtual CollisionData CheckCollisionWithLine(const ICollision& OtherCollision) const override;
		virtual CollisionData CheckCollisionWithGrid(const ICollision& OtherCollision) const override;

		virtual void DrawCollision() override;

		void SetPositionOffset(Vector2D<float> PositionOffset) { _PositionOffset = PositionOffset; }
		Vector2D<float> GetPositionOffset() const { return _PositionOffset; }
		Vector2D<float> GetPosition() const;

		void SetSizeOffset(Vector2D<float> SizeOffset) { _SizeOffset = SizeOffset; }
		Vector2D<float> GetSizeOffset() const { return _SizeOffset; }
		Vector2D<float> GetSize() const;

		virtual ECollisionType GetCollisionType() const override { return _CollisionType; }

		virtual Actor* GetOwner() const override { return _OwnerActor; }
		virtual PhysicsComponent* GetOwnerPhysicsComponent() const  override { return _OwnerPhysicsComponent; }
	};
}