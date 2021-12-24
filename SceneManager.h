#pragma once
#include "Singleton.h"

enum class eSceneTag
{
	None,
	MainMenuScene,
	TutorialScene,
	MapEditerScene,
	StageReadyScene,
};

class GameEntity;
class SceneManager : public Singleton<SceneManager>
{
private:
	map<eSceneTag, GameEntity*>	mapScenes;
	map<eSceneTag, GameEntity*>	mapLoadingScenes;
	int stage = 1;

public:

	static GameEntity* currScene;		// ���� ��� ���� ��
	static GameEntity* readyScene;		// �غ� ���� ��
	static GameEntity* loadingScene;	// �ε� ��

	~SceneManager() {};
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	inline int GetStageInfo() { return this->stage; }
	inline void SetStageInfo(int stage) { this->stage = stage; }
	void AddScene(eSceneTag tag, GameEntity* scene);
	void AddLoadingScene(eSceneTag tag, GameEntity* scene);

	HRESULT ChangeScene(eSceneTag tag);
	HRESULT ChangeScene(eSceneTag tag, eSceneTag loadingSceneName);
};

