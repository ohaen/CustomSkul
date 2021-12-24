#include "Config.h"
#include "MainGame.h"
#include "Image.h"



HRESULT MainGame::Init()
{
	InputManager::Init(g_hWnd);
	IMG_MGR->Init();
	Timer::Init();
	//TIMER_MGR->Init();
	SCENE_MGR->Init();

	srand((unsigned int) time(nullptr));

	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);

	mousePosX = 0;
	mousePosY = 0;
	clickedMousePosX = 0; 
	clickedMousePosY = 0; 

	backBuffer = new Image();
	backBuffer->Init("Image/mapImage.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	//SCENE_MGR->Init();

	SCENE_MGR->ChangeScene(eSceneTag::MainMenuScene);

	return S_OK;
}

void MainGame::Update()
{
	//TIMER_MGR->Update();

	SCENE_MGR->Update();

	InputManager::Update();


	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	HDC hBackBufferDC = backBuffer->GetMemDC();

	SCENE_MGR->Render(hBackBufferDC);

	//TIMER_MGR->Render(hBackBufferDC);


	backBuffer->Render(hdc);

}

void MainGame::Release()
{
	SAFE_RELEASE(backBuffer);

	//TIMER_MGR->Release();
	//TIMER_MGR->ReleaseSingleton();

	IMG_MGR->Release();
	IMG_MGR->ReleaseSingleton();


	SCENE_MGR->Release();
	SCENE_MGR->ReleaseSingleton();

	KillTimer(g_hWnd, 0);
}



