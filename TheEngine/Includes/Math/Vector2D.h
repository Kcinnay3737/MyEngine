#pragma once

namespace NPEngine
{
	template <class T>
	struct Vector2D
	{
	public:
		Vector2D() = default;
		Vector2D(T X, T Y);

		T X;
		T Y;
	};

	template<class T>
	inline Vector2D<T>::Vector2D(T X, T Y)
	{
		this->X = X;
		this->Y = Y;
	}
}