#pragma once
#include "GameEntity.h"
#include "Tile.h"
#include "ObjectTile.h"

class Image;
class Tile;
class ObjectTile;
class MapEditerScene : public GameEntity
{
private:
	Image* backGround;
	Image* tilePalette;
	Image* objectTileImage;

	int saveNum;

	ObjectTile objectInfo[TILE_MAP_SIZE_X * TILE_MAP_SIZE_Y];
	Tile tileInfo[TILE_MAP_SIZE_X * TILE_MAP_SIZE_Y];

	POINT selectTile;
public:
	virtual ~MapEditerScene() {};
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	//void TileMapInit(vector<Tile*> &initVec);
	void TileMapInit(Tile* initTile);
	void TileMapInit(ObjectTile* initTile);
	int SelectIndex();
	
	TileType FindTileType(Tile* tile);

	void SaveMap(int saveNum);
	void LoadMap(int loadNum);
};