#pragma once

#include "Object/Component/Component.h"
#include "Physics/PhysicsEnum.h"
#include "Physics/Collision/CollisionData.h"
#include "Physics/Collision/ICollision.h"
#include "Physics/MovementData.h"
#include <typeindex>
#include <typeinfo>

namespace NPEngine
{
	class PhysicsComponent : public Component, public IDrawableComponent
	{
	public:
		Delegate<void, const std::vector<CollisionData>&> OnCollision;

	private:
		bool _bDrawCollision = false;
		ECollisionType _CollisionType = ECollisionType::None;

		ICollision* _Collision = nullptr;

		MovementData _MovementData = MovementData();

		float _MaxVelocityMagnetude = 100.0f;

		bool _bIsMovable = true;
		bool _bIsPhysicsVolume = true;
		bool _bCalculeCollision = true;

		std::unordered_map<std::type_index, bool> _IgnoreActorClass;

	public:
		PhysicsComponent(const std::string& Name);
		virtual ~PhysicsComponent() = default;

	private:
		virtual bool Initialise(const Param& Params = Param{}) override;
		virtual void Destroy(const Param& Params = Param{}) override;

		virtual void Draw() override;

		void CorrectMagnetude();

		std::vector<CollisionData> CorrectMovement();

	public:
		void SetDrawCollision(bool bDrawCollision) { _bDrawCollision = bDrawCollision; }

		Vector2D<float> GetVelocity();
		void SetVelocity(const Vector2D<float>& NewVelocity);
		void AddVelocity(const Vector2D<float>& VelociyToAdd);
		std::vector<CollisionData> ApplyVelocity(float DeltaTime);

		bool GetIsMovable() const { return _bIsMovable; }
		void SetIsMovable(bool IsMovable) { _bIsMovable = IsMovable; }

		bool GetIsCalculeCollision() const { return _bCalculeCollision; }
		void SetIsCalculeCollision(bool bCalculeCollision) { _bCalculeCollision = bCalculeCollision; }

		bool GetIsPhysicsVolume() const { return _bIsPhysicsVolume; }
		void SetIsPhysicsVolume(bool bIsPhyscicsVolume) { _bIsPhysicsVolume = bIsPhyscicsVolume; }

		std::vector<CollisionData> CheckCollision();

		void SetCollision(const ECollisionType& CollisionType);
		ICollision* GetCollision() const;

		void SetMaxVelocityMagnetude(float MaxVelocityMagnetude) { _MaxVelocityMagnetude = MaxVelocityMagnetude; }
		float GetMaxVelocityMagntude() const { return _MaxVelocityMagnetude; }

		template <typename T>
		void AddIgnoreActorClass();
		void AddIgnoreActorClass(std::type_index TypeIndex);
		template <typename T>
		void RemoveIgnoreActorClass();
		void RemoveIgnoreActorClass(std::type_index TypeIndex);

		bool GetIgnoreActorClass(Actor* CheckActor);

	};

	template<typename T>
	inline void PhysicsComponent::AddIgnoreActorClass()
	{
		static_assert(std::is_base_of<Actor, T>::value, "T must be a derived class of Actor");

		std::type_index TypeIndex(typeid(T));

		_IgnoreActorClass[TypeIndex] = true;
	}

	template<typename T>
	inline void PhysicsComponent::RemoveIgnoreActorClass()
	{
		static_assert(std::is_base_of<Actor, T>::value, "T must be a derived class of Actor");

		std::type_index TypeIndex(typeid(T));

		_IgnoreActorClass.erase(TypeIndex);
	}
}