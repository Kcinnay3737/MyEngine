#pragma once

#include "Math/Vector2D.h"

namespace NPEngine
{
	class Actor;

	struct CollisionData
	{
	public:
		Actor* OtherActor = nullptr;
		Vector2D<float> Normal;
	};
}