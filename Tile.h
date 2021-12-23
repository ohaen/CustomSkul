#pragma once
#include "GameEntity.h"

class Image;
class Tile : public GameEntity
{
private:
	//Image* tileImage;

	POINT tilePos;
	TileType tileType;

	POINT renderTilePos;
public:
	virtual ~Tile() {};

	HRESULT Init(POINT pos, POINT renderPos);
	void Update() override;
	void Render(HDC hdc) override;
	void Release() override;

	inline POINT GetTileRenderPos() { return this->renderTilePos; }
	inline POINT GetTilePos() { return this->tilePos; }
	inline TileType GetTileType() { return this->tileType; }
	inline void SetTile(int posX, int posY)
	{
		this->renderTilePos.x = posX;
		this->renderTilePos.y = posY;
	}
	inline void SetTileType(TileType type) { this->tileType = type; }
};

