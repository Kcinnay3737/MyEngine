#pragma once

#include "Math/Vector2D.h"

namespace NPEngine
{
	struct MovementData
	{
	public:
		Vector2D<float> Velocity;
		float MaxSpeed = 10.0f;
	};
}