#pragma once

#include "Graphics/IGraphicsProvider.h"
#include "Graphics/Color.h"
#include "Graphics/Flip.h"
#include "Math/Vector2D.h"
#include "Math/Rectangle2D.h"

namespace NPEngine
{
	class IGraphics : public IGraphicsProvider
	{
	protected:
		Color _BackgroundColor = Color();

	public:
		virtual ~IGraphics() = default;

		virtual void SetBackgroundColor(const Color& Color) = 0;

		virtual void SetColor(const Color& Color) = 0;

		virtual void DrawRect(const Rectangle2D<float>& Rect, const Color& Color = Color::Blue, bool bFill = false) = 0;
		virtual void DrawLine(const Vector2D<float>& Start, const Vector2D<float>& End, const Color& Color = Color::Red) = 0;
		virtual void DrawPoint(const Vector2D<float>& Position, const Color& Color = Color::Red) = 0;
		virtual void DrawCircle(const Vector2D<float>& Position, const float Ray, const Color& Color = Color::Red) = 0;

		virtual size_t LoadTexture(const char* Filename) = 0;
		virtual void DrawTexture(size_t TextureId,
								const Rectangle2D<float>& DrawRect,
								const Color& Color = Color::White,
								float Angle = 0,
								const Flip& Flip = Flip()) = 0;
		virtual void DrawTextureTile(size_t TextureId,
								const Rectangle2D<float>& DrawRect,
								const Vector2D<int>& CellSize,
								const Vector2D<int>& CellPosition,
								const Color& Color = Color::White,
								float Angle = 0,
								const Flip& Flip = Flip()) = 0;
		virtual void DrawTextureTile(size_t TextureId,
								const Rectangle2D<float>& DrawRect,
								const Vector2D<int>& CellSize,
								const int& CellIndex,
								const Color& Color = Color::White,
								float Angle = 0,
								const Flip& Flip = Flip()) = 0;
		virtual void GetTextureSize(size_t TextureId, Vector2D<int>* Size) = 0;

		virtual size_t LoadFont(const char* Filename, int FontSize) = 0;
		virtual void DrawString(size_t FontId, const char* Text, const Vector2D<int>& Location, const Color& Color) = 0;
		virtual void GetTextSize(size_t FontId, const char* Text, Vector2D<int>* Size) = 0;

		virtual Vector2D<int> GetScreenSize() const = 0;

	private:
		virtual bool Initialize(const Param& Params) override = 0;
		virtual void Shutdown(const Param& Params) override = 0;

		virtual void Clear() override = 0;
		virtual void Present() override = 0;
	};
}