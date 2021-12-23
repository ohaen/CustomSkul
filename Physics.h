#pragma once
#include "GameEntity.h"

class Collider;
class Physics : public GameEntity
{
private:
	POINT mPos;
	POINT mBodySize;

	vector<Collider*> mVecCollider;

public:
	Collider* CreateCollider(POINT pos, POINT bodySize, ColliderTag colliderTag, bool overlap, int damage);
	Collider* DeleteCollider(Collider* col);
	int CheckCollided(Collider* col1);

	Collider* FindTagCollider(Collider* col, ColliderTag findTag);
	bool IsCollided(Collider* col1, Collider* col2);
	//void PreventOverlapped(Collider* col1, Collider* col2);

	void Render(HDC hdc);
	void Update();

};