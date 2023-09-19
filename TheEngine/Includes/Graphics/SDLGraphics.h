#pragma once

#include "Graphics/IGraphics.h"
#include <map>

struct SDL_Renderer;
struct SDL_Window;
struct SDL_Texture;

namespace NPEngine
{

	class SDLGraphics final : public IGraphics
	{
	public:

	private:
		SDL_Renderer* _Renderer = nullptr;
		SDL_Window* _Window = nullptr;

		std::map<const char*, SDL_Texture*> _TextureMap;

	public:
		virtual ~SDLGraphics() = default;

		virtual void SetBackgroundColor(const Color& Color) override;
		virtual void SetColor(const Color& Color) override;

		virtual void DrawRect(const Rectangle2D<float>& Rect, const Color& Color, bool bFill) override;

		virtual void DrawLine(const Vector2D<float>& Start, const Vector2D<float>& End, const Color& Color) override;

		virtual void DrawTexture(const char* Filename, const Rectangle2D<float>& DrawRect, const Color& Color, float Angle, const Flip& Flip) override;
		virtual void DrawTextureTile(const char* Filename, const Rectangle2D<float>& DrawRect, const Vector2D<int>& GridSize, const Vector2D<int>& CellPosition, const Color& Color, float Angle, const Flip& Flip) override;
		virtual void GetTextureSize(const char* Filename, Vector2D<int>* Size) override;

	private:
		virtual bool Initialize(const char* Title, int Width, int Height) override;
		virtual void Shutdown() override;

		virtual void Clear() override;
		virtual void Present() override;

		virtual bool LoadTexture(const char* Filename) override;

	};
}