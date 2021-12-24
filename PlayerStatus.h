#pragma once
#include "GameEntity.h"

class Image;
class PlayerStatus : public GameEntity
{
private:
	Image* playerUI;
	Image* HPBar;
	Image* SkulFace;

	double percent;
public:
	virtual ~PlayerStatus() {};
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void SetHp(int maxHp,int hp);
};

