#include "Config.h"
#include "Collider.h"
#include "Physics.h"

HRESULT Collider::Init(POINT pos, POINT bodySize, ColliderTag tag, Physics* physics, bool overlap, int damage)
{
	this->overlap = overlap;
	mTag = tag;
	mColliderBodySize = bodySize;
	this->damage = damage;

	mColliderPos.x = pos.x;
	mColliderPos.y = pos.y;
	mColliderBody.left = mColliderPos.x - (mColliderBodySize.x / 2);
	mColliderBody.top = mColliderPos.y - (mColliderBodySize.y / 2);
	mColliderBody.right = mColliderBody.left + mColliderBodySize.x;
	mColliderBody.bottom = mColliderBody.top + mColliderBodySize.y;

	mPhysics = physics;

	return S_OK;
}

void Collider::Update()
{
	mColliderBody.left = mColliderPos.x- (mColliderBodySize.x / 2) - CAM_MGR->GetCamaraPos().x;
	mColliderBody.top = mColliderPos.y- (mColliderBodySize.y / 2) - CAM_MGR->GetCamaraPos().y;
	mColliderBody.right = mColliderBody.left + mColliderBodySize.x;
	mColliderBody.bottom = mColliderBody.top + mColliderBodySize.y;
}

void Collider::Render(HDC hdc)
{
	Rectangle(hdc, mColliderBody.left, mColliderBody.top, mColliderBody.right, mColliderBody.bottom);

	//char mxText[16];
	//wsprintf(mxText, "x : %d", (int)mColliderBody.top);
	//TextOut(hdc, mColliderPos.x - CAM_MGR->GetCamaraPos().x- 20, mColliderPos.y - CAM_MGR->GetCamaraPos().y, mxText, strlen(mxText));
	//char myText[16];
	//wsprintf(myText, "y : %d", (int)mColliderBody.bottom);
	//TextOut(hdc, mColliderPos.x - CAM_MGR->GetCamaraPos().x- 20, mColliderPos.y + 15 - CAM_MGR->GetCamaraPos().y, myText, strlen(myText));
	//wsprintf(myText, "y : %d", (int)mColliderBody.top);
	//TextOut(hdc, mColliderPos.x - CAM_MGR->GetCamaraPos().x - 20, mColliderPos.y - 15 - CAM_MGR->GetCamaraPos().y, myText, strlen(myText));
}

void Collider::Release()
{
}

bool Collider::MoveTo(POINT addPos)
{
	POINT oldPos = mColliderPos;
	this->mColliderPos.x += addPos.x;
	this->mColliderPos.y += addPos.y;
	Update();
	if (mPhysics->CheckCollided(this) == false)
	{
		SetPos(oldPos);
		return false;
	}
	Update();
	return true;
}


bool Collider::CheckCollided()
{
	return mPhysics->CheckCollided(this);
}

Collider* Collider::FindTagCollider(Collider* col, ColliderTag findTag)
{
	return mPhysics->FindTagCollider(col, findTag);
}

void Collider::DeleteCollider()
{
	mPhysics->DeleteCollider(this);
}

