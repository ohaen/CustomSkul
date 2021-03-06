#include "MainMenuScene.h"
#include "Image.h"

#define LOGO_X WIN_SIZE_X/2
#define LOGO_Y WIN_SIZE_Y/2

HRESULT MainMenuScene::Init()
{
	
	title = IMG_MGR->FindImage(eImageTag::Title);
	
	logo = IMG_MGR->FindImage(eImageTag::Logo);

	startMenu = IMG_MGR->FindImage(eImageTag::StartMenu);

	mapEditerMenu = IMG_MGR->FindImage(eImageTag::MapEditerMenu);

	onStart = false;
	onMapEditer = false;
	

	return S_OK;
}

void MainMenuScene::Update()
{
	if (g_ptMouse.x > 560 && g_ptMouse.x < 720 && g_ptMouse.y > 450 && g_ptMouse.y < 490)
	{
		onStart = true;
		if (InputManager::GetButtonDown(MK_LBUTTON))
		{
			SCENE_MGR->ChangeScene(eSceneTag::StageReadyScene);
			//SCENE_MGR->ChangeScene(eSceneTag::TutorialScene);
		}
	}
	else if (g_ptMouse.x > 560 && g_ptMouse.x < 720 && g_ptMouse.y > 500 && g_ptMouse.y < 545)
	{
		onMapEditer = true;
		if (InputManager::GetButtonDown(MK_LBUTTON))
		{
			//cout << "click" << endl;
			SCENE_MGR->ChangeScene(eSceneTag::MapEditerScene);
		}
	}
	else
	{
		onMapEditer = false;
		onStart = false;
	}
	if (1 != SCENE_MGR->GetStageInfo())
	{
		SCENE_MGR->ChangeScene(eSceneTag::TutorialScene);
	}
}

void MainMenuScene::Render(HDC hdc)
{
	title->Render(hdc, WIN_SIZE_X/2, WIN_SIZE_Y/2);
	logo->Render(hdc,LOGO_X, LOGO_Y);
	startMenu->Render(hdc, LOGO_X, LOGO_Y+ 110,onStart,0);
	mapEditerMenu->Render(hdc, LOGO_X, LOGO_Y + 160, onMapEditer, 0);



}

void MainMenuScene::Release()
{
	//delete title;
	//delete logo;
	//delete startMenu;
}
