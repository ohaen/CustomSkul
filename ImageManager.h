#pragma once

#include <map>
#include "Singleton.h"

enum class eImageTag
{
	None,
	BackGround,
	StageBackGround,

	//Main Menu Image
	Title,
	Logo,
	StartMenu,
	MapEditerMenu,

	//Skul Image
	Skul,
	SkulWalk,
	SkulLittleBone,

	//MapEditer
	TileGrass,
	TileObject,

	//Monster
	SwordAttack,
	SwordHit,
	SwordIdle,
	SwordWalk,

	//Object
	Exit,

	//PlayerUI
	PlayerInfo,
	HPBar,
	SkulFace,
};

class Image;
class ImageManager : public Singleton<ImageManager>
{
private:
	std::map<eImageTag, Image*>	mapImages;

public:
	virtual ~ImageManager() {}
	void Init();
	void Release();

	Image* AddImage(eImageTag tag, const char* fileName, int width, int height,
		bool isTrans = false, COLORREF transColor = NULL);
	
	Image* AddImage(eImageTag tag, const char* fileName, int width, int height,
		int maxFrameX, int maxFrameY,
		bool isTrans = false, COLORREF transColor = NULL);
	
	Image* FindImage(eImageTag tag);
	void DeleteImage(eImageTag tag);
};