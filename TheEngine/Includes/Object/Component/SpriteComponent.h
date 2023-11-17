#pragma once

#include "Object/Component/Component.h"
#include "Graphics/Flip.h"

namespace NPEngine
{
	class SpriteComponent : public Component, public IDrawableComponent
	{
	protected:
		size_t _TextureID = -1;

		Vector2D<float> _OffsetPosition = Vector2D<float>(0.0f, 0.0f);
		Vector2D<float> _OffsetSize = Vector2D<float>(0.0f, 0.0f);

		bool _bTextureIsLoaded = false;

		Flip _Flip = Flip();

	public:
		SpriteComponent(const std::string& Name);
		virtual ~SpriteComponent() = default;

		void LoadTexture(const std::string& TexturePath);

	protected:
		virtual bool Initialise(const Param& Params = Param{}) override;

	private:
		virtual void Draw() override;

	public:
		void SetOffsetPosition(const Vector2D<float>& OffsetPosition) { _OffsetPosition = OffsetPosition; }
		Vector2D<float> GetOffsetPosition() const { return _OffsetPosition; }
		Vector2D<float> GetPosition() const;

		void SetOffsetSize(const Vector2D<float>& Size) { _OffsetSize = Size; }
		Vector2D<float> GetOffsetSize() const { return _OffsetSize; }
		Vector2D<float> GetSize() const;

		void SetFlip(Flip NewFlip) { _Flip = NewFlip; }
		Flip GetFlip() const { return _Flip; }
	};
}