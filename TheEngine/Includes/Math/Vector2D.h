#pragma once

#include <cmath>

namespace NPEngine
{
	template <class T>
	struct Vector2D
	{
	public:
		T X;
		T Y;

	private:

	public:
		Vector2D() = default;
		Vector2D(T X, T Y);

		T Magnitude() const;
		void Normalize();

		float Distance(const Vector2D<T>& Other);

		static T Dot(const Vector2D<T>& A, const Vector2D<T>& B)
		{
			return A.X * B.X + A.Y * B.Y;
		}

		static T Cross(const Vector2D<T>& A, const Vector2D<T>& B)
		{
			return A.X * B.Y - A.Y * B.X;
		}

		static float AngleBetween(const Vector2D<T>& A, const Vector2D<T>& B)
		{
			const double PI = 3.14159265358979323846264338327950288;

			T DotValue = Dot(A, B);
			T MagA = A.Magnitude();
			T MagB = B.Magnitude();

			// Éviter la division par zéro
			if (MagA == 0 || MagB == 0)
				return 0;

			// Calculer l'angle en radians
			float AngleRadians = acos(DotValue / (MagA * MagB));

			// Convertir l'angle en degrés
			return AngleRadians * (180.0f / PI);
		}

		Vector2D& operator = (const Vector2D& Other)
		{
			if (this != &Other)
			{
				X = Other.X;
				Y = Other.Y;
			}
			return *this;
		}

		Vector2D& operator += (const Vector2D& Other)
		{
			X += Other.X;
			Y += Other.Y;
			return *this;
		}

		Vector2D& operator -= (const Vector2D& Other)
		{
			X -= Other.X;
			Y -= Other.Y;
			return *this;
		}

		Vector2D& operator *= (const Vector2D& Other)
		{
			X *= Other.X;
			Y *= Other.Y;
			return *this;
		}

		Vector2D& operator /= (const Vector2D& Other)
		{
			X /= Other.X;
			Y /= Other.Y;
			return *this;
		}

		bool operator == (const Vector2D<T>& Other) const
		{
			return X == Other.X && Y == Other.Y;
		}

		bool operator != (const Vector2D<T>& Other) const
		{
			return X != Other.X || Y != Other.Y;
		}

		Vector2D<T> operator + (const Vector2D<T>& Other);
		Vector2D<T> operator - (const Vector2D<T>& Other);
		Vector2D<T> operator * (const Vector2D<T>& Other);
		Vector2D<T> operator / (const Vector2D<T>& Other);

		Vector2D<T> operator * (const T& Scalar);
		Vector2D<T> operator / (const T& Scalar);
		Vector2D<T> operator + (const T& Value);
		Vector2D<T> operator - (const T& Value);
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
	inline float Vector2D<T>::Distance(const Vector2D<T>& Other)
	{
		T DX = X - Other.X;
		T DY = Y - Other.Y;
		return sqrt(DX * DX + DY * DY);
	}

	template<class T>
	inline Vector2D<T> Vector2D<T>::operator+(const Vector2D<T>& Other)
	{
		return Vector2D<T>(X + Other.X, Y + Other.Y);
	}

	template<class T>
	inline Vector2D<T> Vector2D<T>::operator-(const Vector2D<T>& Other)
	{
		return Vector2D<T>(X - Other.X, Y - Other.Y);
	}

	template<class T>
	inline Vector2D<T> Vector2D<T>::operator*(const Vector2D<T>& Other)
	{
		return Vector2D<T>(X * Other.X, Y * Other.Y);
	}

	template<class T>
	inline Vector2D<T> Vector2D<T>::operator/(const Vector2D<T>& Other)
	{
		return Vector2D<T>(X / Other.X, Y / Other.Y);
	}

	template<class T>
	inline Vector2D<T> Vector2D<T>::operator*(const T& Scalar)
	{
		return Vector2D<T>(X * Scalar, Y * Scalar);
	}

	template<class T>
	inline Vector2D<T> Vector2D<T>::operator/(const T& Scalar)
	{
		return Vector2D<T>(X / Scalar, Y / Scalar);
	}

	template<class T>
	inline Vector2D<T> Vector2D<T>::operator+(const T& Value)
	{
		return Vector2D<T>(X + Value, Y + Value);
	}

	template<class T>
	inline Vector2D<T> Vector2D<T>::operator-(const T& Value)
	{
		return Vector2D<T>(X - Value, Y - Value);
	}
}