#pragma once

#include "Object/Actor/Actor.h"

namespace NPEngine
{
	class TileMap : public Actor
	{
	public:
		std::vector<std::vector<std::vector<int>>> _TileMap;

		size_t _TileSetID = 0;

		Vector2D<float> _CellSize = Vector2D<float>(0.0f, 0.0f);
		std::vector<int> _CollisionLayer;

	public:
		TileMap(const std::string& Name);
		virtual ~TileMap() = default;

		virtual Actor* Clone(std::string& Name, const Param& Params = Param{});

	protected:
		virtual bool Initialise(const Param& Params = Param{}) override;
		virtual void Destroy(const Param& Params = Param{}) override;

		virtual void BeginPlay() override;

		virtual void Draw() override;

	private:
		void LoadTileSet(const std::string& TileSetPath);
		void LoadTileMap(const std::vector<std::string>& LayerPath);

		std::vector<std::vector<bool>> GetCollisionGrid() const;
	};
}