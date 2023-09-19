#include "Graphics/SDLGraphics.h"

#include <SDL.h>
#include <SDL_image.h>
#include "Engine.h"
#include "Debug/Logger/ILogger.h"
#include <string>
#include <iostream>
#include <filesystem>

using namespace NPEngine;

bool SDLGraphics::Initialize(const char* WindowName, int WindowWidth, int WindowHeight)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		Engine::GetEngineInstance()->GetLogger()->DebugMessage(SDL_GetError());
		return false;
	}

	int X = SDL_WINDOWPOS_CENTERED;
	int Y = SDL_WINDOWPOS_CENTERED;
	Uint32 Flag = SDL_WINDOW_TOOLTIP;
	_Window = SDL_CreateWindow(WindowName, X, Y, WindowWidth, WindowHeight, Flag);
	if (!_Window)
	{
		Engine::GetEngineInstance()->GetLogger()->DebugMessage(SDL_GetError());
		return false;
	}

	Uint32 RenderFlags = SDL_RENDERER_ACCELERATED;
	_Renderer = SDL_CreateRenderer(_Window, -1, RenderFlags);
	if (!_Renderer)
	{
		Engine::GetEngineInstance()->GetLogger()->DebugMessage(SDL_GetError());
		return false;
	}

	return true;
}

void SDLGraphics::Shutdown()
{
	SDL_DestroyRenderer(_Renderer);
	SDL_DestroyWindow(_Window);
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

void SDLGraphics::DrawTexture(const char* Filename, const Rectangle2D<float>& DrawRect, const Color& Color, float Angle, const Flip& Flip)
{
	if (!LoadTexture(Filename)) return;

	SDL_Texture* Texture = _TextureMap[Filename];
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
	GetTextureSize(Filename, &TextureRect.Size);

	SDL_Rect SDLTextureRect = { 0 };
	SDLTextureRect.x = TextureRect.Position.X;
	SDLTextureRect.y = TextureRect.Position.Y;
	SDLTextureRect.w = TextureRect.Size.X;
	SDLTextureRect.h = TextureRect.Size.Y;

	SDL_RenderCopyExF(_Renderer, Texture, &SDLTextureRect, &SDLDrawRect, Angle, nullptr, SDLFlip);
}

void NPEngine::SDLGraphics::DrawTextureTile(const char* Filename, const Rectangle2D<float>& DrawRect, const Vector2D<int>& GridSize, const Vector2D<int>& CellPosition, const Color& Color, float Angle, const Flip& Flip)
{
	if (!LoadTexture(Filename)) return;

	if (GridSize.X <= 0 || GridSize.Y <= 0) return;

	SDL_Texture* Texture = _TextureMap[Filename];
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
	GetTextureSize(Filename, &TextureSize);
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

void SDLGraphics::GetTextureSize(const char* Filename, Vector2D<int>* Size)
{
	if (!LoadTexture(Filename)) return;

	SDL_Texture* Texture = _TextureMap[Filename];
	if (!Texture) return;

	SDL_QueryTexture(Texture, NULL, NULL, &Size->X, &Size->Y);
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

bool SDLGraphics::LoadTexture(const char* Filename)
{
	if (_TextureMap.find(Filename) == _TextureMap.end())
	{
		SDL_Texture* Texture = IMG_LoadTexture(_Renderer, Filename);
		if (!Texture) return false;
		_TextureMap[Filename] = Texture;
	}

	return true;
}