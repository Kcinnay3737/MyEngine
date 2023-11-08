#include "Object/Component/PhysicsComponent.h"
#include "Engine.h"
#include "Object/Component/TransformComponent.h"
#include "Object/Actor/Actor.h"
#include "Physics/Collision/PointCollision.h"
#include "Physics/Collision/LineCollision.h"
#include "Physics/Collision/BoxCollision.h"
#include "Physics/Collision/SphereCollision.h"
#include "Physics/Collision/GridCollision.h"

using namespace NPEngine;

PhysicsComponent::PhysicsComponent(std::string& Name) : Component(Name)
{

}

bool PhysicsComponent::Initialise(const Param& Params)
{
	bool Success = Component::Initialise(Params);

	IPhysics* Physics = Engine::GetPhysics();
	if (Physics)
	{
		IPhysicsProvider* PhysicsProvider = static_cast<IPhysicsProvider*>(Physics);
		if (PhysicsProvider)
		{
			TransformComponent* CurrTransformComponent = GetOwner()->GetComponentOfClass<TransformComponent>();
			if (CurrTransformComponent)
			{
				PhysicsProvider->AddPhysicsActor(GetOwner()->GetName(), this);
			}
			else
			{
				Success = false;
			}
		}
		else
		{
			Success = false;
		}
	}
	else
	{
		Success = false;
	}

	return Success;
}

void PhysicsComponent::Destroy(const Param& Params)
{
	Component::Destroy(Params);

	IPhysics* Physics = Engine::GetPhysics();
	if (Physics)
	{
		IPhysicsProvider* PhysicsProvider = static_cast<IPhysicsProvider*>(Physics);
		if (PhysicsProvider)
		{
			PhysicsProvider->RemovePhysicsActor(GetOwner()->GetName());
		}
	}

	if (_Collision != nullptr)
	{
		delete _Collision;
	}
}

void PhysicsComponent::Draw()
{
	if (_Collision && _bDrawCollision)
	{
		_Collision->DrawCollision();
	}
}

void PhysicsComponent::CorrectMagnetude()
{
	if (GetVelocity().Magnitude() > _MaxVelocityMagnetude)
	{
		_MovementData.Velocity.Normalize();
		_MovementData.Velocity = _MovementData.Velocity * _MaxVelocityMagnetude;
	}
}

Vector2D<float> PhysicsComponent::GetVelocity()
{
	return _MovementData.Velocity;
}

void PhysicsComponent::SetVelocity(const Vector2D<float>& NewVelocity)
{
	_MovementData.Velocity = NewVelocity;
	CorrectMagnetude();
}

void PhysicsComponent::AddVelocity(const Vector2D<float>& VelociyToAdd)
{
	_MovementData.Velocity += VelociyToAdd;
	CorrectMagnetude();
}

void PhysicsComponent::ApplyVelocity(float DeltaTime)
{
	TransformComponent* CurrTransformComponent = GetOwner()->GetComponentOfClass<TransformComponent>();
	if (CurrTransformComponent)
	{
		CurrTransformComponent->AddPositionOffset(GetVelocity() * DeltaTime);
	}

	SetVelocity(Vector2D<float>(0.0f, 0.0f));
}

void PhysicsComponent::SetCollision(const ECollisionType& CollisionType)
{
	if (_Collision != nullptr)
	{
		delete _Collision;
	}

	_CollisionType = CollisionType;

	switch (_CollisionType)
	{
	case ECollisionType::None:
		_Collision = nullptr;
		break;
	case ECollisionType::Point:
		_Collision = new PointCollision(GetOwner());
		break;
	case ECollisionType::Line:
		_Collision = new LineCollision(GetOwner());
		break;
	case ECollisionType::Box:
		_Collision = new BoxCollision(GetOwner());
		break;
	case ECollisionType::Sphere:
		_Collision = new SphereCollision(GetOwner());
		break;
	case ECollisionType::Grid:
		_Collision = new GridCollision(GetOwner());
		break;
	default:
		_Collision = nullptr;
		break;
	}
}

const ICollision* PhysicsComponent::GetCollision() const
{
	return _Collision;
}
