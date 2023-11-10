#include "Object/Component/AtlasComponent.h"
#include "Engine.h"

using namespace NPEngine;

AtlasComponent::AtlasComponent(std::string& Name) : SpriteComponent(Name)
{
}

void AtlasComponent::Draw()
{
	if (_bTextureIsLoaded)
	{
		Engine::GetGraphics()->DrawTextureTile(_TextureID, Rectangle2D<float>(GetPosition(), GetSize()), _TileSize, _CurrTileIndex, Color::White, 0.0f, _Flip);
	}
}