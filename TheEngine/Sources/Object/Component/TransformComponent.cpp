#include "Object/Component/TransformComponent.h"
#include <cmath>

using namespace NPEngine;

TransformComponent::TransformComponent(std::string& Name) : Component(Name)
{
	_Position.X = 0.0f;
	_Position.Y = 0.0f;
	
	_Size.X = 100.0f;
	_Size.Y = 100.0f;

	_Angle = 0.0f;
}

Vector2D<float> TransformComponent::GetPosition()
{
	return _Position;
}

void TransformComponent::SetPosition(const Vector2D<float>& NewPosition)
{
	_Position = NewPosition;
}

void TransformComponent::AddPositionOffset(const Vector2D<float>& PositionOffsetToAdd)
{
	_Position += PositionOffsetToAdd;
}

Vector2D<float> TransformComponent::GetSize()
{
	return _Size;
}

void TransformComponent::SetSize(const Vector2D<float>& NewSize)
{
	_Size = NewSize;
}

void TransformComponent::AddSizeOffset(const Vector2D<float>& SizeOffsetToAdd)
{
	_Size += SizeOffsetToAdd;
}

Rectangle2D<float> TransformComponent::GetPositionSizeRectangle()
{
	Rectangle2D<float> Rectangle = Rectangle2D<float>(_Position, _Size);
	return Rectangle;
}

void TransformComponent::AdjustsAngleBetweenValue(float MinAngle, float MaxAngle)
{
	if (_Angle < MinAngle || _Angle > MaxAngle)
	{
		float Range = MaxAngle - MinAngle;
		_Angle = std::fmod(_Angle - MinAngle, Range);

		if (_Angle < 0)
		{
			_Angle += Range;
		}

		_Angle += MinAngle; 
	}
}

float TransformComponent::GetAngle()
{
	return _Angle;
}

void TransformComponent::SetAngle(const float& NewAngle)
{
	_Angle = NewAngle;
	AdjustsAngleBetweenValue(-180.0f, 180.0f);
}

void TransformComponent::AddAngleOffset(const float& AngleOffsetToAdd)
{
	_Angle += AngleOffsetToAdd;
	AdjustsAngleBetweenValue(-180.0f, 180.0f);
}
