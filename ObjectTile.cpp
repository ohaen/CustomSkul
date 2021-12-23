#include "ObjectTile.h"
#include "Image.h"

HRESULT ObjectTile::Init(POINT pos, POINT renderPos)
{
	
	tilePos.x = pos.x;
	tilePos.y = pos.y;
	tileType = ObjectTileType::None;

	renderTilePos.x = renderPos.x;
	renderTilePos.y = renderPos.y;


	return S_OK;
}

void ObjectTile::Update()
{
}

void ObjectTile::Render(HDC hdc)
{
	//objectTileImage->Render(hdc, tilePos.x + TILE_SIZE * 0.5 - CAM_MGR->GetCamaraPos().x, tilePos.y + TILE_SIZE * 0.5 - CAM_MGR->GetCamaraPos().y, renderTilePos.x, renderTilePos.y);
}

void ObjectTile::Release()
{
}
