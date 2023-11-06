#pragma once

#include "Math/Vector2D.h"

namespace NPEngine
{
	struct MovementData
	{
	public:
		Vector2D<float> Velocity;
		float DecelerationSpeed = 0.0f;
	};
}