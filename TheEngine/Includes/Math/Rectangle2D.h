#pragma once

#include "Vector2D.h"

namespace NPEngine
{
	template <class T>
	struct Rectangle2D
	{
	public:
		Vector2D<T> Position;
		Vector2D<T> Size;
	};
}