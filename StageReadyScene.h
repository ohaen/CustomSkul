#pragma once
#include "GameEntity.h"

class StageReadyScene : public GameEntity
{
public:
	virtual ~StageReadyScene() {};
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();
};

