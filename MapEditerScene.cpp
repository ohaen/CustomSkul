#include "MapEditerScene.h"
#include "Image.h"
#include "ObjectTile.h"



HRESULT MapEditerScene::Init()
{
	tilePalette = IMG_MGR->FindImage(eImageTag::TileGrass);
	objectTileImage = IMG_MGR->FindImage(eImageTag::TileObject);
	backGround = IMG_MGR->FindImage(eImageTag::BackGround);
	saveNum = 1;
	TileMapInit(tileInfo);
	TileMapInit(objectInfo);
	return S_OK;
}


void MapEditerScene::Update()
{
	if (InputManager::GetButton('D'))
	{
		CAM_MGR->SetCameraPos(CAM_MGR->GetCamaraPos().x + 10, CAM_MGR->GetCamaraPos().y);
	}
	else if (InputManager::GetButton('A'))
	{
		CAM_MGR->SetCameraPos(CAM_MGR->GetCamaraPos().x - 10, CAM_MGR->GetCamaraPos().y);
	}
	if (InputManager::GetButton('W'))
	{
		CAM_MGR->SetCameraPos(CAM_MGR->GetCamaraPos().x, CAM_MGR->GetCamaraPos().y - 10);
	}
	else if (InputManager::GetButton('S'))
	{
		CAM_MGR->SetCameraPos(CAM_MGR->GetCamaraPos().x, CAM_MGR->GetCamaraPos().y + 10);
	}

	if (g_ptMouse.x > WIN_SIZE_X - tilePalette->GetWidth() && g_ptMouse.x < WIN_SIZE_X &&
		g_ptMouse.y > 0 && g_ptMouse.y < tilePalette->GetHeight())		//tilePalette
	{
		if (InputManager::GetButtonDown(MK_LBUTTON))
		{
			selectTile.x = (g_ptMouse.x - (WIN_SIZE_X - tilePalette->GetWidth())) / TILE_SIZE;
			selectTile.y = g_ptMouse.y / TILE_SIZE;
		}
	}


	if (g_ptMouse.x + CAM_MGR->GetCamaraPos().x > 0 && g_ptMouse.x < WIN_SIZE_X - tilePalette->GetWidth() &&
		g_ptMouse.y + CAM_MGR->GetCamaraPos().y > 0 && g_ptMouse.y < WIN_SIZE_Y&&
		g_ptMouse.x + CAM_MGR->GetCamaraPos().x < TILE_MAP_SIZE_X * TILE_SIZE &&
		g_ptMouse.y + CAM_MGR->GetCamaraPos().y < TILE_MAP_SIZE_Y * TILE_SIZE)		//main layer
	{
		if (InputManager::GetButton(MK_LBUTTON))
		{
			tileInfo[SelectIndex()].SetTile(selectTile.x, selectTile.y);
			tileInfo[SelectIndex()].SetTileType(FindTileType(&tileInfo[SelectIndex()]));
		}
		else if (InputManager::GetButton(MK_RBUTTON))
		{

			tileInfo[SelectIndex()].SetTile(1, 5);
			tileInfo[SelectIndex()].SetTileType(FindTileType(&tileInfo[SelectIndex()]));
		}
	}

	if (InputManager::GetButtonDown('1'))
	{
		for (int i = 0; i < TILE_MAP_SIZE_X * TILE_MAP_SIZE_Y; ++i)
		{
			if (objectInfo[i].GetTileType() == ObjectTileType::Start)
			{
				objectInfo[i].SetTile(2, 0);
				objectInfo[i].SetTileType(ObjectTileType::None);
			}
		}
		objectInfo[SelectIndex()].SetTile(0, 0);
		objectInfo[SelectIndex()].SetTileType(ObjectTileType::Start);
	}

	if (InputManager::GetButtonDown('2'))
	{
		for (int i = 0; i < TILE_MAP_SIZE_X * TILE_MAP_SIZE_Y; ++i)
		{
			if (objectInfo[i].GetTileType() == ObjectTileType::Exit)
			{
				objectInfo[i].SetTile(2, 0);
				objectInfo[i].SetTileType(ObjectTileType::None);
			}
		}
		objectInfo[SelectIndex()].SetTile(1, 0);
		objectInfo[SelectIndex()].SetTileType(ObjectTileType::Exit);
	}

	if (InputManager::GetButton('3'))
	{
		objectInfo[SelectIndex()].SetTile(0, 1);
		objectInfo[SelectIndex()].SetTileType(ObjectTileType::SwordMan);
	}

	if (InputManager::GetButtonDown('Z'))
	{
		cout << saveNum << "번 맵을 저장합니다 \n";
		SaveMap(saveNum);
	}

	if(InputManager::GetButtonDown('X'))
	{
		cout << saveNum << "번 맵을 불러옵니다 \n";
		LoadMap(saveNum);
	}

	if (InputManager::GetButtonDown('C'))
	{
		cout << sizeof(tileInfo) << "\n";
	}

	if (InputManager::GetButtonDown(VK_NUMPAD1))
	{
		cout << "스테이지1 맵 선택\n";
		saveNum = 1;
	}
	if (InputManager::GetButtonDown(VK_NUMPAD2))
	{
		cout << "스테이지2 맵 선택\n";
		saveNum = 2;
	}
	if (InputManager::GetButtonDown(VK_NUMPAD3))
	{
		cout << "스테이지3 맵 선택\n";
		saveNum = 3;
	}
	if (InputManager::GetButtonDown(VK_NUMPAD4))
	{
		system("cls");
		cout << "스테이지4 맵 선택\n";
		saveNum = 4;
	}
	if (InputManager::GetButtonDown(VK_NUMPAD5))
	{
		cout << "스테이지5 맵 선택\n";
		saveNum = 5;
	}
}

void MapEditerScene::Render(HDC hdc)
{
	backGround->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2);

	for (int i = 0; i < TILE_MAP_SIZE_X * TILE_MAP_SIZE_Y; ++i)
	{
		tilePalette->Render(hdc,
			tileInfo[i].GetTilePos().x + TILE_SIZE * 0.5 - CAM_MGR->GetCamaraPos().x,
			tileInfo[i].GetTilePos().y + TILE_SIZE * 0.5 - CAM_MGR->GetCamaraPos().y,
			tileInfo[i].GetTileRenderPos().x,
			tileInfo[i].GetTileRenderPos().y);

		objectTileImage->Render(hdc,
			objectInfo[i].GetTilePos().x + TILE_SIZE * 0.5 - CAM_MGR->GetCamaraPos().x,
			objectInfo[i].GetTilePos().y + TILE_SIZE * 0.5 - CAM_MGR->GetCamaraPos().y,
			objectInfo[i].GetTileRenderPos().x,
			objectInfo[i].GetTileRenderPos().y);
	}
	backGround->Render(hdc, WIN_SIZE_X+ 185, WIN_SIZE_Y / 2);
	tilePalette->Render(hdc, WIN_SIZE_X-(tilePalette->GetWidth()/2), tilePalette->GetHeight()/2);
}

void MapEditerScene::Release()
{
}


void MapEditerScene::TileMapInit(Tile* initTile)
{
	for (int y = 0; y < TILE_MAP_SIZE_Y; ++y)
	{
		for (int i = 0; i < TILE_MAP_SIZE_X; ++i)
		{
			initTile[i + (y * TILE_MAP_SIZE_X)].Init({ TILE_SIZE * i, TILE_SIZE * y }, { 1,5 });
			initTile[i + (y * TILE_MAP_SIZE_X)].SetTileType(TileType::Null);
		}
	}
}

void MapEditerScene::TileMapInit(ObjectTile* initTile)
{
	for (int y = 0; y < TILE_MAP_SIZE_Y; ++y)
	{
		for (int i = 0; i < TILE_MAP_SIZE_X; ++i)
		{
			initTile[i + (y * TILE_MAP_SIZE_X)].Init({ TILE_SIZE * i, TILE_SIZE * y }, { 2,0 });
			initTile[i + (y * TILE_MAP_SIZE_X)].SetTileType(ObjectTileType::None);
		}
	}
}

int MapEditerScene::SelectIndex()
{
	int index;
	POINT mousePos;
	mousePos.x = ((g_ptMouse.x + CAM_MGR->GetCamaraPos().x) / TILE_SIZE);
	mousePos.y = ((g_ptMouse.y + CAM_MGR->GetCamaraPos().y) / TILE_SIZE);
	return index = mousePos.x + (mousePos.y * TILE_MAP_SIZE_X);
}

TileType MapEditerScene::FindTileType(Tile* tile)
{
	POINT findType = tile->GetTileRenderPos();
		if (findType.x == 0 && findType.y == 0 || 
			findType.x == 1 && findType.y == 0 || 
			findType.x == 1 && findType.y == 1 || 
			findType.x == 0 && findType.y == 1)
		{
			return TileType::Ground;
		}
		else if (findType.x == 4 && findType.y == 0 ||
			findType.x == 0 && findType.y == 3 ||
			findType.x == 1 && findType.y == 3 ||
			findType.x == 2 && findType.y == 3)
		{
			return TileType::HalfGround;
		}
		else if (findType.x == 1 && findType.y == 5)
		{
			return TileType::Null;
		}
		else
		{
			return TileType::Wall;
		}
}

void MapEditerScene::SaveMap(int saveNum)
{
	string saveFileName = "Save/TileData_" + to_string(saveNum);
	saveFileName += ".tilemap";

	HANDLE hFile = CreateFile(saveFileName.c_str(),
		GENERIC_WRITE,
		0, NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	// 쓰기
	DWORD writtenByte;
	if (WriteFile(hFile,
		&tileInfo,
		sizeof(tileInfo),
		&writtenByte,
		NULL) == false)
	{
		MessageBox(g_hWnd, "맵 데이터 저장에 실패했습니다.", "에러", MB_OK);
	}
	CloseHandle(hFile);

	saveFileName = "Save/TileData_" + to_string(saveNum);
	saveFileName += ".objecttilemap";

	hFile = CreateFile(saveFileName.c_str(),
		GENERIC_WRITE,
		0, NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	// 쓰기
	writtenByte;
	if (WriteFile(hFile,
		&objectInfo,
		sizeof(objectInfo),
		&writtenByte,
		NULL) == false)
	{
		MessageBox(g_hWnd, "맵 데이터 저장에 실패했습니다.", "에러", MB_OK);
	}
	CloseHandle(hFile);
}

void MapEditerScene::LoadMap(int loadNum)
{
	string loadFileName = "Save/TileData_" + to_string(loadNum);
	loadFileName += ".tilemap";

	HANDLE hFile = CreateFile(loadFileName.c_str(),
		GENERIC_READ,
		0, NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	DWORD readByte;
	if (ReadFile(hFile, &tileInfo, sizeof(tileInfo),
		&readByte, NULL) == false)
	{
		MessageBox(g_hWnd, "맵 데이터 로드에 실패했습니다.", "에러", MB_OK);
	}

	CloseHandle(hFile);

	loadFileName = "Save/TileData_" + to_string(loadNum);
	loadFileName += ".objecttilemap";

	hFile = CreateFile(loadFileName.c_str(),
		GENERIC_READ,
		0, NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	readByte;
	if (ReadFile(hFile, &objectInfo, sizeof(objectInfo),
		&readByte, NULL) == false)
	{
		MessageBox(g_hWnd, "맵 데이터 로드에 실패했습니다.", "에러", MB_OK);
	}

	CloseHandle(hFile);
}
