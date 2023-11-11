#pragma once

#include "Graphics/IGraphics.h"
#include <unordered_map>

struct SDL_Renderer;
struct SDL_Window;
struct SDL_Texture;
struct _TTF_Font;

namespace NPEngine
{
	class SDLGraphics final : public IGraphics
	{
	public:

	private:
		SDL_Renderer* _Renderer = nullptr;
		SDL_Window* _Window = nullptr;

		std::unordered_map<size_t, SDL_Texture*> _TextureMap;
		std::unordered_map<size_t, _TTF_Font*> _FontMap;

	public:
		virtual ~SDLGraphics() = default;

		virtual void SetBackgroundColor(const Color& Color) override;
		virtual void SetColor(const Color& Color) override;

		virtual void DrawRect(const Rectangle2D<float>& Rect, const Color& Color, bool bFill) override;

		virtual void DrawLine(const Vector2D<float>& Start, const Vector2D<float>& End, const Color& Color) override;

		virtual void DrawPoint(const Vector2D<float>& Position, const Color& Color = Color::Red) override;

		virtual void DrawCircle(const Vector2D<float>& Position, const float Ray, const Color& Color = Color::Red) override;

		virtual size_t LoadTexture(const char* Filename) override;
		virtual void DrawTexture(size_t TextureId, const Rectangle2D<float>& DrawRect, const Color& Color, float Angle, const Flip& Flip) override;
		virtual void DrawTextureTile(size_t TextureId, const Rectangle2D<float>& DrawRect, const Vector2D<int>& CellSize, const Vector2D<int>& CellPosition, const Color& Color, float Angle, const Flip& Flip) override;
		virtual void DrawTextureTile(size_t TextureId, const Rectangle2D<float>& DrawRect, const Vector2D<int>& CellSize, const int& CellIndex, const Color& Color = Color::White, float Angle = 0, const Flip& Flip = Flip()) override;
		virtual void GetTextureSize(size_t TextureId, Vector2D<int>* Size) override;

		virtual size_t LoadFont(const char* Filename, int FontSize) override;
		virtual void DrawString(size_t FontId, const char* Text, const Vector2D<int>& Location, const Color& Color) override;
		virtual void GetTextSize(size_t FontId, const char* Text, Vector2D<int>* Size) override;

		virtual Vector2D<int> GetScreenSize() const override;

	private:
		virtual bool Initialize(const Param& Params) override;
		virtual void Shutdown(const Param& Params) override;

		virtual void Clear() override;
		virtual void Present() override;

	};
}