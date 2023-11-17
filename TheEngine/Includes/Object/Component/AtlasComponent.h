#pragma once

#include "Object/Component/SpriteComponent.h"

namespace NPEngine
{
	class AtlasComponent : public SpriteComponent
	{
	protected:
		Vector2D<int> _TileSize = Vector2D<int>(32, 32);
		int _CurrTileIndex = 0;

	public:
		AtlasComponent(const std::string& Name);
		virtual ~AtlasComponent() = default;

	private:
		virtual bool Initialise(const Param& Params = Param{}) override;

		virtual void Draw() override;
		
	public:
		void SetTileSize(Vector2D<int> TileSize) { _TileSize = TileSize; }
		Vector2D<int> GetTileSize() const { return _TileSize; }

		void SetTileIndex(int TileIndex) { _CurrTileIndex = TileIndex; }
		int GetTileIndex() const { return _CurrTileIndex; }
	};
}