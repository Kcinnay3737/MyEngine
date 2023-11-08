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

		T Magnitude() const;
		void Normalize();

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

		Vector2D<T> operator * (const T& Scalar);
	};

	template<class T>
	inline Vector2D<T>::Vector2D(T X, T Y)
	{
		this->X = X;
		this->Y = Y;
	}

	template<class T>
	inline T Vector2D<T>::Magnitude() const
	{
		return std::sqrt(X * X + Y * Y);
	}

	template<class T>
	inline void Vector2D<T>::Normalize()
	{
		T length = Magnitude();

		if (length > T(0))
		{
			X /= length;
			Y /= length;
		}
	}

	template<class T>
	inline Vector2D<T> Vector2D<T>::operator*(const T& Scalar)
	{
		return Vector2D<T>(X * Scalar, Y * Scalar);
	}
}