#pragma once

#include "Vector2D.h"

namespace NPEngine
{
	template <class T>
	struct Rectangle2D
	{
	public:
		Rectangle2D() = default;
		Rectangle2D(Vector2D<T> Position, Vector2D<T> Size);

		Vector2D<T> Position;
		Vector2D<T> Size;
	};

	template<class T>
	inline Rectangle2D<T>::Rectangle2D(Vector2D<T> Position, Vector2D<T> Size)
	{
		this->Position = Position;
		this->Size = Size;
	}
}