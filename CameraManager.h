#pragma once
#include "Config.h"
#include "Singleton.h"

class CameraManager : public Singleton<CameraManager>
{
private:
	POINT CameraPos = { 0,0 };
public:
	~CameraManager() {};
	HRESULT Init();
	inline POINT GetCamaraPos() { return CameraPos; }
	inline void SetCameraPos(float cameraPosX, float camaraPosY) { this->CameraPos.x = cameraPosX; this->CameraPos.y = camaraPosY; }
	inline void AddCameraPos(float addPosX, float addPosY) { this->CameraPos.x += addPosX; this->CameraPos.y += addPosY; }
};

