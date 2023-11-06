#pragma once

namespace NPEngine
{
	template <class T>
	struct Vector2D
	{
	public:
		T X;
		T Y;

	public:
		Vector2D() = default;
		Vector2D(T X, T Y);

		Vector2D& operator = (const Vector2D& Other)
		{
			if (this != &Other)
			{
				X = Other.X;
				Y = Other.Y;
			}
			return *this;
		}

		Vector2D& operator += (const Vector2D& other)
		{
			X += other.X;
			Y += other.Y;
			return *this;
		}
	};

	template<class T>
	inline Vector2D<T>::Vector2D(T X, T Y)
	{
		this->X = X;
		this->Y = Y;
	}
}