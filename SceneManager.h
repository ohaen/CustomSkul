#pragma once
#include "Singleton.h"

enum class eSceneTag
{
	None,
	MainMenuScene,
	TutorialScene,
	MapEditerScene,
};

class GameEntity;
class SceneManager : public Singleton<SceneManager>
{
private:
	map<eSceneTag, GameEntity*>	mapScenes;
	map<eSceneTag, GameEntity*>	mapLoadingScenes;

public:
	static GameEntity* currScene;		// ���� ��� ���� ��
	static GameEntity* readyScene;		// �غ� ���� ��
	static GameEntity* loadingScene;	// �ε� ��

	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void AddScene(eSceneTag tag, GameEntity* scene);
	void AddLoadingScene(eSceneTag tag, GameEntity* scene);

	HRESULT ChangeScene(eSceneTag tag);
	HRESULT ChangeScene(eSceneTag tag, eSceneTag loadingSceneName);
};

