#pragma once

#define WIN_START_POS_X	400
#define WIN_START_POS_Y	100
#define WIN_SIZE_X	1280
#define WIN_SIZE_Y	720
#define PI 3.14159265357989
#define PI2 (3.14159265357989 * 2)

#define DEGREE_TO_RADIAN(x)		(x * PI / 180.0f)
#define SAFE_RELEASE(p)	{ if (p) { p->Release(); delete p; p = nullptr; } }
#define SAFE_DELETE(p)	{ if (p) { delete p; p = nullptr; } }

//#define TIMER_MGR TimerManager::GetSingleton()
#define KEY_MGR KeyManager::GetSingleton()
#define SCENE_MGR SceneManager::GetSingleton()
#define IMG_MGR ImageManager::GetSingleton()
#define CAM_MGR CameraManager::GetSingleton()

//#define DELTA_TIME TIMER_MGR->GetDeltaTime()
#define DELTA_TIME Timer::GetDeltaTime()
#define RANDOM(min, max) (rand() % ((max) - (min) + 1) + (min))
#define A 12
#define TILE_SIZE 76
#define TILE_MAP_SIZE_X 60
#define TILE_MAP_SIZE_Y 30

#define GET_CAM_X CAM_MGR->GetCamaraPos().x
#define GET_CAM_Y CAM_MGR->GetCamaraPos().y

enum class TileType
{
	Null,
	Wall,
	Ground,
	HalfGround,
	Start,
	Exit,
};

enum class ObjectTileType
{
	None,
	Start,
	Exit,
	SwordMan,
};

enum class ColliderTag
{
	None,
	Ground,
	HalfGround,
	Player,
	Monster,
	Exit,
	NPC,
	RayCast,
	PlayerAttack,
	MonsterAttack,
};

enum class skulType
{
	Nomal,
};