#include "PlayerStatus.h"
#include "Image.h"

HRESULT PlayerStatus::Init()
{
    playerUI = IMG_MGR->FindImage(eImageTag::PlayerInfo);
    HPBar = IMG_MGR->FindImage(eImageTag::HPBar);
    SkulFace = IMG_MGR->FindImage(eImageTag::SkulFace);
    //HPBar->SetFrameWidth(50);
    percent = 100.0;
    return S_OK;
}

void PlayerStatus::Update()
{
}

void PlayerStatus::Render(HDC hdc)
{
    playerUI->RenderDir(hdc, 0, WIN_SIZE_Y-playerUI->GetFrameHeight()*2,0,0,2.0f);
    HPBar->RenderDir(hdc, 86, WIN_SIZE_Y- 44,0,0,2.0f);
    SkulFace->RenderDir(hdc, 12, WIN_SIZE_Y - 130, 0, 0, 2.0f);
}

void PlayerStatus::Release()
{
}

void PlayerStatus::SetHp(int maxHp, int hp)
{
    HPBar->SetFrameWidth((int)(HPBar->GetWidth() - ((HPBar->GetWidth() * 0.01) * (percent - (hp / (maxHp * 0.01))))));
}
