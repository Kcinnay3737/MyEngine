#pragma once

#include "Object/Component/Component.h"

namespace NPEngine
{
	class SpriteComponent : public Component, public IDrawableComponent
	{
	public:
		SpriteComponent(std::string& Name);
		virtual ~SpriteComponent() = default;

		Vector2D<float> _OffsetPosition = Vector2D<float>(0.0f, 0.0f);
		Vector2D<float> _OffsetSize = Vector2D<float>(0.0f, 0.0f);

	private:
		virtual void Draw() override;

	public:
		void SetOffsetPosition(const Vector2D<float>& OffsetPosition) { _OffsetPosition = OffsetPosition; }
		Vector2D<float> GetOffsetPosition() const { return _OffsetPosition; }

		void SetOffsetSize(const Vector2D<float>& Size) { _OffsetSize = Size; }
		Vector2D<float> GetOffsetSize() const { return _OffsetSize; }
	};
}