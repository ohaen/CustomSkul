#pragma once
#include "Config.h"
#include "GameEntity.h"

class Image;
class MainMenuScene : public GameEntity
{
private:
	Image* title;
	Image* logo;
	Image* startMenu;
	Image* mapEditerMenu;




	bool onStart;
	bool onMapEditer;

public:
	virtual ~MainMenuScene() {};
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();
};

