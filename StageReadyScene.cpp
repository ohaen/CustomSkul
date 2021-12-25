#include "StageReadyScene.h"

HRESULT StageReadyScene::Init()
{
	
	return S_OK;
}

void StageReadyScene::Update()
{
	SCENE_MGR->ChangeScene(eSceneTag::TutorialScene);
}

void StageReadyScene::Render(HDC hdc)
{
}

void StageReadyScene::Release()
{
}
