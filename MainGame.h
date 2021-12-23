#pragma once
#include "GameEntity.h"

class Image;
class Collider;
class MainGame : public GameEntity
{
private:
	HANDLE hTimer;
	Collider* collider;

	int mousePosX;
	int mousePosY;
	int clickedMousePosX;
	int clickedMousePosY;

	Image* backBuffer;

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();
};