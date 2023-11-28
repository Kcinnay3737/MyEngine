#pragma once

#include "Object/Actor/Actor.h"
#include "Physics/Collision/CollisionData.h"

namespace NPEngine
{
	class PhysicsComponent;

	class Projectil : public Actor
	{
	private:
		static size_t _ProjectilCount;

	protected:
		Vector2D<float> _Direction = Vector2D<float>(0.0f, 0.0f);
		float _MoveSpeed = 0.0f;

		float _Damage = 1.0f;

		PhysicsComponent* _PhysicsComponent = nullptr;

	public:
		Projectil(const std::string& Name);
		virtual ~Projectil() = default;

		virtual Actor* Clone(const std::string& Name, const Param& Params = Param{});

	private:
		virtual bool Initialise(const Param& Params) override;
		virtual void BeginPlay() override;
		virtual void Update(float DeltaTime) override;

		void OnHit(const std::vector<CollisionData>& CollisionsData);

	public:
		void SetDirection(const Vector2D<float>& Direction) { _Direction = Direction; }
		void SetMoveSpeed(const float& MoveSpeed);

		static std::string GetNextProjectileName();

		
	};
}