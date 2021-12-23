#pragma once
#include "GameObject.h"

class Image;
class ExitDoor : public GameObject
{
private:
	Image* exitDoor;
public:
	HRESULT Init(POINT pos, Collider* collider);
	void Update();
	void Render(HDC hdc);
	void Release();

};

