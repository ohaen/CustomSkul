#include "Config.h"
#include "ImageManager.h"
#include "Image.h"

void ImageManager::Init()
{
	AddImage(eImageTag::BackGround, "Image/background.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	AddImage(eImageTag::StageBackGround, "Image/back5.bmp", WIN_SIZE_X*2, WIN_SIZE_Y*2);
	

	//Main Menu Image
	AddImage(eImageTag::Title, "Image/Title/Title.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	AddImage(eImageTag::Logo, "Image/Title/Logo.bmp", WIN_SIZE_X, WIN_SIZE_Y/4,true, RGB(255, 0, 255));
	AddImage(eImageTag::StartMenu, "Image/Title/GameStart.bmp", 316, 39, 2, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::MapEditerMenu, "Image/Title/MapEditer.bmp", 306, 39, 2, 1, true, RGB(255, 0, 255));

	//Skul Image
	AddImage(eImageTag::Skul, "Image/charactor/Skul2.bmp", 200, 74, 4, 2, true, RGB(255, 0, 255));
	AddImage(eImageTag::SkulWalk, "Image/charactor/Walk_0.bmp", 360, 72, 8, 2, true, RGB(255, 0, 255));
	AddImage(eImageTag::SkulLittleBone, "Image/charactor/skul_little_bone.bmp", 3780, 2400, 27, 24, true, RGB(255, 0, 255));

	//MapEditer
	AddImage(eImageTag::TileGrass, "Image/Tile/TileGrass.bmp", TILE_SIZE*6, TILE_SIZE*6, 6, 6, true, RGB(255, 0, 255));
	AddImage(eImageTag::TileObject, "Image/Tile/TileObject.bmp", TILE_SIZE * 6, TILE_SIZE * 6, 6, 6, true, RGB(255, 0, 255));

	//Monster
	AddImage(eImageTag::SwordAttack, "Image/SwordMan/Attack.bmp", 312, 128, 4, 2, true, RGB(255, 0, 255));
	AddImage(eImageTag::SwordHit, "Image/SwordMan/Hit.bmp", 92, 102, 2, 2, true, RGB(255, 0, 255));
	AddImage(eImageTag::SwordIdle, "Image/SwordMan/Idle.bmp", 204, 112, 6, 2, true, RGB(255, 0, 255));
	AddImage(eImageTag::SwordWalk, "Image/SwordMan/Walk.bmp", 416, 100, 8, 2, true, RGB(255, 0, 255));

	//Object
	AddImage(eImageTag::Exit, "Image/exit.bmp", 1566, 138, 9, 1, true, RGB(255, 255, 255));

	//PlyaerUI
	AddImage(eImageTag::PlayerInfo, "Image/UI/PlayerFrame.bmp", 168, 66, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::HPBar, "Image/UI/HpBar.bmp", 118, 10, 1, 1, true, RGB(255, 0, 255));
}

void ImageManager::Release()
{
	map<eImageTag, Image*>::iterator it;
	for (it = mapImages.begin(); it != mapImages.end();)
	{
		SAFE_RELEASE(it->second);
		it = mapImages.erase(it);
	}
	mapImages.clear();
}

Image* ImageManager::AddImage(eImageTag tag, const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	// 이미 등록한 이미지는 nullptr을 반환
	if (mapImages.find(tag) != mapImages.end()) { return nullptr; }

	Image* img = new Image;
	if (FAILED(img->Init(fileName, width, height, isTrans, transColor)))
	{
		SAFE_RELEASE(img);
		return nullptr;
	}

	mapImages.insert(make_pair(tag, img));

	return img;
}

Image* ImageManager::AddImage(eImageTag tag, const char* fileName, int width, int height,
	int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	// 이미 등록한 이미지는 nullptr을 반환
	if (mapImages.find(tag) != mapImages.end()) { return nullptr; }

	Image* img = new Image;
	if (FAILED(img->Init(fileName, width, height, maxFrameX, 
		maxFrameY, isTrans, transColor)))
	{
		SAFE_RELEASE(img);
		return nullptr;
	}

	mapImages.insert(make_pair(tag, img));

	return img;
}

Image* ImageManager::FindImage(eImageTag tag)
{
	map<eImageTag, Image*>::iterator it = mapImages.find(tag);
	if (it == mapImages.end())
	{
		return nullptr;
	}

	return it->second;
}

void ImageManager::DeleteImage(eImageTag tag)
{
	map<eImageTag, Image*>::iterator it = mapImages.find(tag);
	if (it == mapImages.end())
	{
		return;
	}

	SAFE_RELEASE(it->second);
	mapImages.erase(it);
}
