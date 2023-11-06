#pragma once

#include "Physics/Collision/ICollision.h"

namespace NPEngine
{
	class BoxCollider : public ICollision
	{
	public:
		Rectangle2D<float> _Rectangle;
	};
}