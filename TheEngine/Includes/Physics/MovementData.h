#pragma once

#include "Math/Vector2D.h"

namespace NPEngine
{
	struct MovementData
	{
	public:
		Vector2D<float> Velocity = Vector2D<float>(0.0f, 0.0f);
		float MaxSpeed = 10.0f;
	};
}