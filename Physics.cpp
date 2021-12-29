#include "Physics.h"
#include "Collider.h"

Collider* Physics::CreateCollider(POINT pos, POINT bodySize, ColliderTag colliderTag, bool overlap, int damage)
{
	Collider* newCol = new Collider();
	newCol->Init(pos, bodySize, colliderTag, this, overlap, damage);
	mVecCollider.push_back(newCol);
	return newCol;
}

Collider* Physics::DeleteCollider(Collider* col)
{
	auto it = find(mVecCollider.begin(), mVecCollider.end(), col);
	SAFE_DELETE(*it);
	mVecCollider.erase(it);
	return nullptr;
}


int Physics::CheckCollided(Collider* col1)
{
	for (int i = 0; i < mVecCollider.size(); ++i)
	{
		if (mVecCollider[i] == col1)
		{
			continue;
		}
		if (IsCollided(col1, mVecCollider[i]))
		{
			if (col1->GetOverlap() && mVecCollider[i]->GetOverlap())
			{
				return -1;
			}
			return 0;
		}
	}
	return 1;
}

Collider* Physics::FindTagCollider(Collider* col, ColliderTag findTag)
{
	for (int i = 0; i < mVecCollider.size(); ++i)
	{
		if (mVecCollider[i] == col)
		{
			continue;
		}
		if (IsCollided(col, mVecCollider[i]))
		{
			if ((col->GetOverlap() && mVecCollider[i]->GetOverlap())&& mVecCollider[i]->GetColliderTag() == findTag)
			{
				return mVecCollider[i];
			}
		}
	}
	return nullptr;
}

bool Physics::IsCollided(Collider* col1, Collider* col2)
{
	if (col1->GetColliderBody().left >= col2->GetColliderBody().right) { return false; }
	if (col1->GetColliderBody().right <= col2->GetColliderBody().left) { return false; }
	if (col1->GetColliderBody().top >= col2->GetColliderBody().bottom) { return false; }
	if (col1->GetColliderBody().bottom <= col2->GetColliderBody().top) { return false; }

	return true;
}

void Physics::Render(HDC hdc)
{
	for (int i = 0; i < mVecCollider.size(); ++i)
	{
		mVecCollider[i]->Render(hdc);
	}
}

void Physics::Update()
{
	for (int i = 0; i < mVecCollider.size(); ++i)
	{
		mVecCollider[i]->Update();
	}
}

void Physics::Release()
{
	Collider* col;
	for (auto it = mVecCollider.begin(); it != mVecCollider.end();)
	{
		col = (*it);
		it = mVecCollider.erase(it);
		SAFE_DELETE(col);
	}
	mVecCollider.clear();
}
