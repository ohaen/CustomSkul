#include "Config.h"
#include "SceneManager.h"
#include "GameEntity.h"

#include "MainMenuScene.h"
#include "TutorialScene.h"
#include "MapEditerScene.h"

GameEntity* SceneManager::currScene = nullptr;
GameEntity* SceneManager::readyScene = nullptr;
GameEntity* SceneManager::loadingScene = nullptr;

DWORD CALLBACK LoadingThread(LPVOID pvParam)
{
	// ������� �ʱ�ȭ�Ѵ�.
	SceneManager::readyScene->Init();
	SceneManager::currScene = SceneManager::readyScene;

	SceneManager::loadingScene->Release();
	SceneManager::loadingScene = nullptr;
	SceneManager::readyScene = nullptr;

	return 0;
}

void SceneManager::Init()
{
	AddScene(eSceneTag::MainMenuScene, new MainMenuScene);
	AddScene(eSceneTag::TutorialScene, new TutorialScene);
	AddScene(eSceneTag::MapEditerScene, new MapEditerScene);
}

void SceneManager::Release()
{
}

void SceneManager::Update()
{
	if (currScene)
		currScene->Update();
}

void SceneManager::Render(HDC hdc)
{
	if (currScene)
		currScene->Render(hdc);
}

void SceneManager::AddScene(eSceneTag tag, GameEntity* scene)
{
	if (scene == nullptr)	return;

	if (mapScenes.find(tag) != mapScenes.end())
	{
		return;
	}

	mapScenes.insert(pair<eSceneTag, GameEntity*>(tag, scene));

}

void SceneManager::AddLoadingScene(eSceneTag tag, GameEntity* scene)
{
	if (scene == nullptr)	return;

	if (mapLoadingScenes.find(tag) != mapLoadingScenes.end())
	{
		return;
	}

	mapLoadingScenes.insert(pair<eSceneTag, GameEntity*>(tag, scene));
}

HRESULT SceneManager::ChangeScene(eSceneTag tag)
{
	map<eSceneTag, GameEntity*>::iterator it = mapScenes.find(tag);

	if (it == mapScenes.end())
		return E_FAIL;

	if (SUCCEEDED((it->second)->Init()))
	{
		if (currScene)
			currScene->Release();

		currScene = it->second;

		return S_OK;
	}

	return E_FAIL;
}

HRESULT SceneManager::ChangeScene(eSceneTag tag, eSceneTag loadingSceneName)
{
	map<eSceneTag, GameEntity*>::iterator it = mapScenes.find(tag);

	if (it == mapScenes.end())
		return E_FAIL;

	// �ε��� Ȯ��
	map<eSceneTag, GameEntity*>::iterator itLoading = mapLoadingScenes.find(loadingSceneName);
	if (itLoading == mapLoadingScenes.end())
	{
		return ChangeScene(tag);
	}

	// �ε��� ���� ��
	if (SUCCEEDED((itLoading->second)->Init()))
	{
		if (currScene)
			currScene->Release();

		readyScene = it->second;
		loadingScene = itLoading->second;

		currScene = loadingScene;

		// ��Ƽ������ ó��
		DWORD loadThread;
		HANDLE hThread = CreateThread(NULL, 0,
			LoadingThread/*���� ��ų �Լ�������(�Լ��̸�)*/,
			NULL /*���� ��ų �Լ��� �� �Ű�����*/,
			0, &loadThread);

		CloseHandle(hThread);

		return S_OK;
	}

	return E_FAIL;
}
