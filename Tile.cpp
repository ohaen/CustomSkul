#include "Tile.h"
#include "Image.h"

HRESULT Tile::Init(POINT pos, POINT renderPos)
{
	
	tilePos.x = pos.x;
	tilePos.y = pos.y;
	tileType = TileType::Null;

	renderTilePos.x = renderPos.x;
	renderTilePos.y = renderPos.y;


	return S_OK;
}

void Tile::Update()
{
}

void Tile::Render(HDC hdc)
{
	
}

void Tile::Release()
{
}
