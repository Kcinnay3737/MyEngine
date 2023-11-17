#pragma once

#include "Object/Component/Component.h"

namespace NPEngine
{
	class TransformComponent : public Component
	{
	private:
		Vector2D<float> _Position;
		Vector2D<float> _Size;
		float _Angle = 0.0f;

	public:
		TransformComponent(const std::string& Name);
		virtual ~TransformComponent() = default;

	private:
		virtual bool Initialise(const Param& Params = Param{}) override;

		void AdjustsAngleBetweenValue(float MinAngle, float MaxAngle);

	public:
		Vector2D<float> GetPosition();
		void SetPosition(const Vector2D<float>& NewPosition);
		void AddPositionOffset(const Vector2D<float>& PositionOffsetToAdd);

		Vector2D<float> GetSize();
		void SetSize(const Vector2D<float>& NewSize);
		void AddSizeOffset(const Vector2D<float>& SizeOffsetToAdd);

		Rectangle2D<float> GetPositionSizeRectangle();

		float GetAngle();
		void SetAngle(const float& NewAngle);
		void AddAngleOffset(const float& AngleOffsetToAdd);
	};
}