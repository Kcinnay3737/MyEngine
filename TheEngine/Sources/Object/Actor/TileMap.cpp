#include "Object/Actor/TileMap.h"
#include "Engine.h"

#include <fstream>
#include <sstream>

using namespace NPEngine;

TileMap::TileMap(std::string& Name) : Actor(Name)
{
}

bool TileMap::Initialise(const Param& Params)
{
	Actor::Initialise(Params);

	auto& IT = Params.find("LayerPath");
	if (IT != Params.end())
	{
		const std::vector<std::string>& LayerPath = std::any_cast<const std::vector<std::string>&>(IT->second);
		LoadTileMap(LayerPath);
	}

	IT = Params.find("TileSetPath");
	if (IT != Params.end())
	{
		const std::string& TileSetPath = std::any_cast<const std::string&>(IT->second);

		LoadTileSet(TileSetPath);
	}

	IT = Params.find("CellSize");
	if (IT != Params.end())
	{
		_CellSize = std::any_cast<Vector2D<int>>(IT->second);
	}

	return true;
}

void TileMap::Destroy(const Param& Params)
{
	Actor::Destroy(Params);


}

Actor* TileMap::Clone(std::string& Name, const Param& Params)
{
	TileMap* CloneActor = new TileMap(Name);
	return CloneActor;
}

void TileMap::Draw()
{
	Actor::Draw();
	
	for (const std::vector<std::vector<int>>& CurrLayer : _TileMap)
	{
		Rectangle2D<float> CurrDrawRectangle = Rectangle2D<float>(Vector2D<float>(0.0f, 0.0f), Vector2D<float>(_CellSize.X, _CellSize.Y));

		for (const std::vector<int>& CurrRow : CurrLayer)
		{
			CurrDrawRectangle.Position.X = 0;
			for (const int& Cell : CurrRow)
			{
				Engine::GetGraphics()->DrawTextureTile(_TileSetID, CurrDrawRectangle, _CellSize, Cell);
				CurrDrawRectangle.Position.X += static_cast<float>(_CellSize.X);
			}
			CurrDrawRectangle.Position.Y += static_cast<float>(_CellSize.Y);
		}
	}
}

void TileMap::LoadTileSet(const std::string& TileSetPath)
{
	_TileSetID = Engine::GetGraphics()->LoadTexture(TileSetPath.c_str());
}

void TileMap::LoadTileMap(const std::vector<std::string>& LayerPath)
{
	for (const std::string& EndPath : LayerPath)
	{
		std::string CurrPath = std::string("./Assets/TileMap/") + EndPath;

		std::ifstream File(CurrPath);
		std::string Line;
		std::vector<std::vector<int>> Layer;

		if (File.is_open()) 
		{
			while (getline(File, Line)) 
			{
				std::vector<int> Row;
				std::stringstream LineStream(Line);
				std::string Cell;

				while (getline(LineStream, Cell, ',')) 
				{
					if (!Cell.empty()) 
					{
						Row.push_back(std::stoi(Cell));
					}
				}

				Layer.push_back(Row);
			}
			_TileMap.push_back(Layer);
			File.close();
		}
	}
}
