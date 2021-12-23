#include "TutorialScene.h"
#include "Skul.h"
#include "Image.h"
#include "Physics.h"
#include "GameManager.h"

HRESULT TutorialScene::Init()
{
	debug = 0;
	gameManager = new GameManager;
	gameManager->Init();
	skul = new Skul;
	CAM_MGR->SetCameraPos(-WIN_SIZE_X / 2, -WIN_SIZE_Y / 2);
	backGround = IMG_MGR->FindImage(eImageTag::StageBackGround);

	tileImage = IMG_MGR->FindImage(eImageTag::TileGrass);
	objectTileImage = IMG_MGR->FindImage(eImageTag::TileObject);
	exitDoor = IMG_MGR->FindImage(eImageTag::Exit);
	playerUI = IMG_MGR->FindImage(eImageTag::PlayerInfo);
	HPBar = IMG_MGR->FindImage(eImageTag::HPBar);
	enemyCount = 0;
	LoadMap(1);
	for (int i = 0; i < TILE_MAP_SIZE_X * TILE_MAP_SIZE_Y; ++i)
	{
		if (objectInfo[i].GetTileType() == ObjectTileType::Start)
		{
			CAM_MGR->AddCameraPos(objectInfo[i].GetTilePos().x + TILE_SIZE / 2, objectInfo[i].GetTilePos().y + TILE_SIZE / 2);
			break;
		}
	}

	for (int i = 0; i < TILE_MAP_SIZE_X * TILE_MAP_SIZE_Y; ++i)
	{
		if (tileInfo[i].GetTileType() == TileType::Wall ||
			tileInfo[i].GetTileType() == TileType::Ground)
		{
			POINT pos;
			pos.x = tileInfo[i].GetTilePos().x + TILE_SIZE / 2;
			pos.y = tileInfo[i].GetTilePos().y + TILE_SIZE / 2;
			gameManager->CreateCollider(pos, { TILE_SIZE , TILE_SIZE }, ColliderTag::Ground);
		}
		if (tileInfo[i].GetTileType() == TileType::HalfGround)
		{
			POINT pos;
			pos.x = tileInfo[i].GetTilePos().x + TILE_SIZE / 2;
			pos.y = tileInfo[i].GetTilePos().y + TILE_SIZE / 2;
			gameManager->CreateCollider(pos, { TILE_SIZE ,TILE_SIZE }, ColliderTag::HalfGround, true);
		}
	}

	for (int i = 0; i < TILE_MAP_SIZE_X * TILE_MAP_SIZE_Y; ++i)
	{
		if (objectInfo[i].GetTileType() == ObjectTileType::SwordMan)
		{
			POINT pos;
			pos.x = tileInfo[i].GetTilePos().x + TILE_SIZE / 2;
			pos.y = tileInfo[i].GetTilePos().y + TILE_SIZE / 2;
			gameManager->CreateSwordMonster(pos, gameManager->CreateCollider(pos, { 65 ,76 }, ColliderTag::Monster, true)
			, gameManager->CreateCollider(pos, { 600 ,50 }, ColliderTag::RayCast, true));
			++enemyCount;
		}
		if (objectInfo[i].GetTileType() == ObjectTileType::Exit)
		{
			exitDoorPos.x = tileInfo[i].GetTilePos().x + TILE_SIZE / 2;
			exitDoorPos.y = tileInfo[i].GetTilePos().y + TILE_SIZE / 2 - 75;
			gameManager->CreateCollider(exitDoorPos, { 225 ,225 }, ColliderTag::Exit, true);
		}
	}
	skul = gameManager->SpawnSkul(gameManager->CreateCollider({ WIN_SIZE_X / 2 + CAM_MGR->GetCamaraPos().x + 15
		, WIN_SIZE_Y / 2 + CAM_MGR->GetCamaraPos().y }, { 40,40 }, ColliderTag::Player, true));

	percent = 100;
	HPBarPercent = (int)(skul->GetCurrHP() / (skul->GetMaxHP() * 0.01));
	doorFrame = 0;
	doorFrameElapsd = 0;
	
	return S_OK;
}

void TutorialScene::Update()
{
	doorFrameElapsd += DELTA_TIME;
	if (doorFrameElapsd > 0.1)
	{
		if (doorFrame < 7)
		{
			++doorFrame;
		}
		else
		{
			doorFrame = 0;
		}
		doorFrameElapsd = 0;
	}

	HPBarPercent = (int)(skul->GetCurrHP() / (skul->GetMaxHP() * 0.01));
	skul->Update();
	gameManager->PhysicsUpdate();
	gameManager->SwordMonsterUpdate();

	if (InputManager::GetButtonDown(VK_TAB))
	{
		debug ? debug = 0 : debug = 1;
	}
	
}

void TutorialScene::Render(HDC hdc)
{
	backGround->Render(hdc, WIN_SIZE_X-CAM_MGR->GetCamaraPos().x / 10, WIN_SIZE_Y-CAM_MGR->GetCamaraPos().y/10);
	for (int i = 0; i < TILE_MAP_SIZE_X * TILE_MAP_SIZE_Y; ++i)
	{
		if (!(tileInfo[i].GetTileType() == TileType::Null))
		{
			tileImage->Render(hdc,
				(int)(tileInfo[i].GetTilePos().x + TILE_SIZE * 0.5 - CAM_MGR->GetCamaraPos().x),
				(int)(tileInfo[i].GetTilePos().y + TILE_SIZE * 0.5 - CAM_MGR->GetCamaraPos().y),
				tileInfo[i].GetTileRenderPos().x,
				tileInfo[i].GetTileRenderPos().y);

		}
	}
	if (gameManager->GetEnemyCount() > 0)
	{
		exitDoor->Render(hdc, exitDoorPos.x - CAM_MGR->GetCamaraPos().x - 95, exitDoorPos.y - CAM_MGR->GetCamaraPos().y - 55, 8, 0, 2.0f);
	}
	else
	{
		exitDoor->Render(hdc, exitDoorPos.x - CAM_MGR->GetCamaraPos().x - 95, exitDoorPos.y - CAM_MGR->GetCamaraPos().y - 55, doorFrame, 0, 2.0f);
	}

	if (debug)
	{
		gameManager->PhysicsRender(hdc);
	}
	gameManager->SwordMonsterRender(hdc);
	skul->Render(hdc);

	playerUI->Render(hdc, (int)(playerUI->GetFrameWidth() * 0.5), (int)(WIN_SIZE_Y - playerUI->GetFrameHeight() *1.5), 0, 0, 2.0f);
	HPBar->Render(hdc, (int)((84)+ HPBarPercent *0.6), (int)(WIN_SIZE_Y - 39), 0, 0, 2.0f);
	HPBar->SetFrameWidth((int)((double)HPBar->GetWidth() - (double)(HPBar->GetWidth() * 0.01) * ((double)percent - (double)HPBarPercent)));

}

void TutorialScene::Release()
{	
	skul->Release();
	gameManager->Release();
	delete skul;
	delete gameManager;
}


void TutorialScene::LoadMap(int stage)
{
	string loadFileName = "Save/TileData_" + to_string(stage);
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

	loadFileName = "Save/TileData_" + to_string(stage);
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
