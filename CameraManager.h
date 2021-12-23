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
	inline void SetCameraPos(int cameraPosX, int camaraPosY) { this->CameraPos.x = cameraPosX; this->CameraPos.y = camaraPosY; }
	inline void AddCameraPos(int addPosX, int addPosY) { this->CameraPos.x += addPosX; this->CameraPos.y += addPosY; }
};

