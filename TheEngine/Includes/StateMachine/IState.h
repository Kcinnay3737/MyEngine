#pragma once

#include "Utility/Utility.h"
#include "Physics/Collision/CollisionData.h"

namespace NPEngine
{
	class Object;

	class IState
	{
	public:
		virtual ~IState() = default;

		virtual void OnEnter(Object* Owner) = 0;
		virtual void Execute(float DeltaTime, Object* Owner) = 0;
		virtual void OnExit(Object* Owner) = 0;

		virtual void OnCollision(const std::vector<CollisionData>& CollisionsData) = 0;
	};
}