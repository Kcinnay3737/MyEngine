#include "Graphics/SDLGraphics.h"

#include <SDL.h>
#include <SDL_image.h>
#include "Engine.h"
#include "Debug/Logger/ILogger.h"
#include <string>
#include <SDL_ttf.h>

using namespace NPEngine;

bool SDLGraphics::Initialize(const char* WindowName, int WindowWidth, int WindowHeight)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		Engine::GetLogger()->LogMessage(SDL_GetError());
		return false;
	}

	int X = SDL_WINDOWPOS_CENTERED;
	int Y = SDL_WINDOWPOS_CENTERED;
	Uint32 Flag = SDL_WINDOW_TOOLTIP;
	_Window = SDL_CreateWindow(WindowName, X, Y, WindowWidth, WindowHeight, Flag);
	if (!_Window)
	{
		Engine::GetLogger()->LogMessage(SDL_GetError());
		return false;
	}

	Uint32 RenderFlags = SDL_RENDERER_ACCELERATED;
	_Renderer = SDL_CreateRenderer(_Window, -1, RenderFlags);
	if (!_Renderer)
	{
		Engine::GetLogger()->LogMessage(SDL_GetError());
		return false;
	}

	if (TTF_Init() == -1)
	{
		Engine::GetLogger()->LogMessage(TTF_GetError());
		return false;
	}

	return true;
}

void SDLGraphics::Shutdown()
{
	SDL_DestroyRenderer(_Renderer);
	SDL_DestroyWindow(_Window);
	TTF_Quit();
	SDL_Quit();
}

void SDLGraphics::SetBackgroundColor(const Color& Color)
{
	_BackgroundColor = Color;
}

void SDLGraphics::SetColor(const Color& Color)
{
	SDL_SetRenderDrawColor(_Renderer, Color.rgba.R, Color.rgba.G, Color.rgba.B, Color.rgba.A);
}

void SDLGraphics::DrawRect(const Rectangle2D<float>& Rect, const Color& Color, bool bFill)
{
	SetColor(Color);

	SDL_FRect SDLRect = { 0.0f };
	SDLRect.x = Rect.Position.X;
	SDLRect.y = Rect.Position.Y;
	SDLRect.w = Rect.Size.X;
	SDLRect.h = Rect.Size.Y;

	if (bFill)
	{
		SDL_RenderFillRectF(_Renderer, &SDLRect);
	}
	else
	{
		SDL_RenderDrawRectF(_Renderer, &SDLRect);
	}
}

void SDLGraphics::DrawLine(const Vector2D<float>& Start, const Vector2D<float>& End, const Color& Color)
{
	SetColor(Color);

	SDL_RenderDrawLineF(_Renderer, Start.X, Start.Y, End.X, End.Y);
}

void SDLGraphics::DrawTexture(size_t TextureId, const Rectangle2D<float>& DrawRect, const Color& Color, float Angle, const Flip& Flip)
{
	SDL_Texture* Texture = _TextureMap[TextureId];
	if (!Texture) return;

	SDL_RendererFlip SDLFlip = SDL_FLIP_NONE;
	if (Flip.Horizontal && Flip.Vertical)
	{
		SDLFlip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
	}
	else if (Flip.Horizontal)
	{
		SDLFlip = SDL_FLIP_HORIZONTAL;
	}
	else if (Flip.Vertical)
	{
		SDLFlip = SDL_FLIP_VERTICAL;
	}

	SDL_SetTextureColorMod(Texture, Color.rgba.R, Color.rgba.G, Color.rgba.B);
	SDL_SetTextureAlphaMod(Texture, Color.rgba.A);

	SDL_FRect SDLDrawRect = { 0.0f };
	SDLDrawRect.x = DrawRect.Position.X;
	SDLDrawRect.y = DrawRect.Position.Y;
	SDLDrawRect.w = DrawRect.Size.X;
	SDLDrawRect.h = DrawRect.Size.Y;

	Rectangle2D<int> TextureRect = Rectangle2D<int>(Vector2D<int>(0, 0), Vector2D<int>(0, 0));
	GetTextureSize(TextureId, &TextureRect.Size);

	SDL_Rect SDLTextureRect = { 0 };
	SDLTextureRect.x = TextureRect.Position.X;
	SDLTextureRect.y = TextureRect.Position.Y;
	SDLTextureRect.w = TextureRect.Size.X;
	SDLTextureRect.h = TextureRect.Size.Y;

	SDL_RenderCopyExF(_Renderer, Texture, &SDLTextureRect, &SDLDrawRect, Angle, nullptr, SDLFlip);
}

void SDLGraphics::DrawTextureTile(size_t TextureId, const Rectangle2D<float>& DrawRect, const Vector2D<int>& GridSize, const Vector2D<int>& CellPosition, const Color& Color, float Angle, const Flip& Flip)
{
	if (GridSize.X <= 0 || GridSize.Y <= 0) return;

	SDL_Texture* Texture = _TextureMap[TextureId];
	if (!Texture) return;

	SDL_RendererFlip SDLFlip = SDL_FLIP_NONE;
	if (Flip.Horizontal && Flip.Vertical)
	{
		SDLFlip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
	}
	else if (Flip.Horizontal)
	{
		SDLFlip = SDL_FLIP_HORIZONTAL;
	}
	else if (Flip.Vertical)
	{
		SDLFlip = SDL_FLIP_VERTICAL;
	}

	SDL_SetTextureColorMod(Texture, Color.rgba.R, Color.rgba.G, Color.rgba.B);
	SDL_SetTextureAlphaMod(Texture, Color.rgba.A);

	SDL_FRect SDLDrawRect = { 0.0f };
	SDLDrawRect.x = DrawRect.Position.X;
	SDLDrawRect.y = DrawRect.Position.Y;
	SDLDrawRect.w = DrawRect.Size.X;
	SDLDrawRect.h = DrawRect.Size.Y;

	Vector2D<int> TextureSize;
	GetTextureSize(TextureId, &TextureSize);
	Vector2D<int> CellSize;
	CellSize.X = TextureSize.X / GridSize.X;
	CellSize.Y = TextureSize.Y / GridSize.Y;

	Rectangle2D<int> TextureRect = Rectangle2D<int>(Vector2D<int>(CellSize.X * CellPosition.X, CellSize.Y * CellPosition.Y), Vector2D<int>(CellSize.X, CellSize.Y));

	SDL_Rect SDLTextureRect = { 0 };
	SDLTextureRect.x = TextureRect.Position.X;
	SDLTextureRect.y = TextureRect.Position.Y;
	SDLTextureRect.w = TextureRect.Size.X;
	SDLTextureRect.h = TextureRect.Size.Y;

	SDL_RenderCopyExF(_Renderer, Texture, &SDLTextureRect, &SDLDrawRect, Angle, nullptr, SDLFlip);
}

void SDLGraphics::GetTextureSize(size_t TextureId, Vector2D<int>* Size)
{
	SDL_Texture* Texture = _TextureMap[TextureId];
	if (!Texture) return;

	SDL_QueryTexture(Texture, NULL, NULL, &Size->X, &Size->Y);
}

size_t SDLGraphics::LoadFont(const char* Filename, int FontSize)
{
	std::hash<const char*> Hasher;
	size_t FontId = Hasher(Filename);

	if (_FontMap.find(FontId) == _FontMap.end())
	{
		std::string FilePath = "../Assets/Font/";
		FilePath += Filename;

		TTF_Font* Font = TTF_OpenFont(FilePath.c_str(), FontSize);
		if (Font)
		{
			_FontMap[FontId] = Font;
		}
		else
		{
			Engine::GetLogger()->LogMessage(TTF_GetError());
		}
	}

	return FontId;
}

void SDLGraphics::DrawString(size_t FontId, const char* Text, Vector2D<int>& Location, const Color& Color)
{
	TTF_Font* Font = _FontMap[FontId];

	SDL_Color SDLColor = SDL_Color();
	SDLColor.r = Color.rgba.R;
	SDLColor.g = Color.rgba.G;
	SDLColor.b = Color.rgba.B;
	SDLColor.a = Color.rgba.A;

	SDL_Surface* Surface = TTF_RenderText_Solid(Font, Text, SDLColor);
	SDL_Texture* TextureBuffer = SDL_CreateTextureFromSurface(_Renderer, Surface);

	Vector2D<int> FontSize;
	GetTextSize(FontId, Text, &FontSize);

	SDL_Rect SDLRect = SDL_Rect();
	SDLRect.x = Location.X;
	SDLRect.y = Location.Y;
	SDLRect.w = FontSize.X;
	SDLRect.h = FontSize.Y;

	SDL_RenderCopy(_Renderer, TextureBuffer, nullptr, &SDLRect);
	SDL_FreeSurface(Surface);
}

void SDLGraphics::GetTextSize(size_t FontId, const char* Text, Vector2D<int>* Size)
{
	TTF_Font* Font = _FontMap[FontId];
	if (!Font) return;

	int Width = 0;
	int Height = 0;
	if (TTF_SizeText(Font, Text, &Width, &Height) != 0) return;

	Size->X = Width;
	Size->Y = Height;
}

void SDLGraphics::Clear()
{
	SDL_SetRenderDrawColor(_Renderer, _BackgroundColor.rgba.R, _BackgroundColor.rgba.G, _BackgroundColor.rgba.B, _BackgroundColor.rgba.A);
	SDL_RenderClear(_Renderer);
}

void SDLGraphics::Present()
{
	SDL_RenderPresent(_Renderer);
}

size_t SDLGraphics::LoadTexture(const char* Filename)
{
	std::hash<const char*> Hasher;
	size_t TextureId = Hasher(Filename);

	if (_TextureMap.find(TextureId) == _TextureMap.end())
	{
		std::string FilePath = "../Assets/Texture/";
		FilePath += Filename;
		SDL_Texture* Texture = IMG_LoadTexture(_Renderer, FilePath.c_str());
		if (Texture)
		{
			_TextureMap[TextureId] = Texture;
		}
		else
		{
			Engine::GetLogger()->LogMessage("Texture not found");
		}
	}

	return TextureId;
}