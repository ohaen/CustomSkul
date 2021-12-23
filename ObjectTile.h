#pragma once
#include "GameEntity.h"

class Image;
class ObjectTile : public GameEntity
{
private:
	

	POINT tilePos;
	ObjectTileType tileType;

	POINT renderTilePos;

public:
	virtual ~ObjectTile() {};

	HRESULT Init(POINT pos, POINT renderPos);
	void Update() override;
	void Render(HDC hdc) override;
	void Release() override;

	inline POINT GetTileRenderPos() { return this->renderTilePos; }
	inline ObjectTileType GetTileType() { return this->tileType; }
	inline POINT GetTilePos() { return this->tilePos; }
	inline void SetTile(int posX, int posY, int layer = 0)
	{
		this->renderTilePos.x = posX;
		this->renderTilePos.y = posY;
	}
	inline void SetTileType(ObjectTileType type) { this->tileType = type; }
};

