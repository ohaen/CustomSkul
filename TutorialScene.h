#pragma once
#include "GameEntity.h"
#include "Tile.h"
#include "ObjectTile.h"

class Physics;
class Skul;
class Image;
class GameManager;
class PlayerStatus;
class TutorialScene : public GameEntity
{
private:
	GameManager* gameManager;

	PlayerStatus* playerStatus;
	Skul* skul;
	Image* backGround;

	Image* exitDoor;
	Image* tileImage;
	Image* objectTileImage;


	bool debug;
	bool openDoor;
	int percent;
	int HPBarPercent;
	int HPBarWidth;
	int doorFrame;
	float doorFrameElapsd;

	POINT exitDoorPos;
public:
	virtual ~TutorialScene() {};
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	ObjectTile objectInfo[TILE_MAP_SIZE_X * TILE_MAP_SIZE_Y];
	Tile tileInfo[TILE_MAP_SIZE_X * TILE_MAP_SIZE_Y];

	void LoadMap(int stage);
};

