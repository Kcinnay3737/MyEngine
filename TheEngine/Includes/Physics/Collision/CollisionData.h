#pragma once

#include "Math/Vector2D.h"

class Actor;

namespace NPEngine
{
	struct CollisionData
	{
	public:
		Actor* OtherActor = nullptr;
		Vector2D<float> Normal;
	};
}