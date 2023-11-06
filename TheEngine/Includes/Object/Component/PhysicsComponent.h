#pragma once

#include "Object/Component/Component.h"
#include "Physics/PhysicsEnum.h"
#include "Physics/Collision/CollisionData.h"
#include "Physics/Collision/ICollision.h"
#include "Physics/MovementData.h"

namespace NPEngine
{
	class PhysicsComponent : public Component
	{
	public:
		Delegate<void, const CollisionData&> OnCollision;

	private:
		bool _bDrawCollision = false;
		ECollisionType _CollisionType = ECollisionType::None;

		ICollision* _Collision = nullptr;

		MovementData _MovementData = MovementData();

	public:
		PhysicsComponent(std::string& Name);
		virtual ~PhysicsComponent() = default;

	private:
		virtual bool Initialise(const Param& Params = Param{}) override;
		virtual void Destroy(const Param& Params = Param{}) override;

	public:
		Vector2D<float> GetVelocity();
		void SetVelocity(const Vector2D<float>& NewVelocity);
		void AddVelocity(const Vector2D<float>& VelociyToAdd);

		float GetDecelerationSpeed();
		void SetDecelerationSpeed(const float& NewDecelationSpeed);

		void SetCollision(const ECollisionType& CollisionType);
		const ICollision* GetCollision() const;

	};
}