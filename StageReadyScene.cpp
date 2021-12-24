#include "StageReadyScene.h"

HRESULT StageReadyScene::Init()
{
	SCENE_MGR->ChangeScene(eSceneTag::TutorialScene);
	return S_OK;
}

void StageReadyScene::Update()
{
}

void StageReadyScene::Render(HDC hdc)
{
}

void StageReadyScene::Release()
{
}
