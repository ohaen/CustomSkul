#pragma once
#include "GameEntity.h"

class Physics;
class Collider : public GameEntity
{
private:
	POINT mColliderPos;
	RECT mColliderBody;
	POINT mColliderBodySize;
	ColliderTag mTag;
	Physics* mPhysics;
	bool overlap = false;
	int damage;
public:
	virtual ~Collider() {};
	HRESULT Init(POINT pos, POINT bodySize, ColliderTag tag, Physics* physics, bool overlap, int damage);
	void Update() override;

	void Render(HDC hdc) override;
	void Release();

	bool MoveTo(POINT addPos);
	void SetPos(POINT setPos) 
	{
		this->mColliderPos = setPos;
		Update();	
	}
	//bool CheckCollider(POINT addPos);
	bool CheckCollided();
	Collider* FindTagCollider(Collider* col, ColliderTag findTag);

	POINT RayCast(Collider* col, ColliderTag findTag);
	void DeleteCollider();

	inline POINT GetColliderPos() { return this -> mColliderPos; }
	inline RECT GetColliderBody() { return this->mColliderBody; }
	inline POINT GetColliderBodySize() { return this->mColliderBodySize; }
	inline ColliderTag GetColliderTag() { return this->mTag; }
	inline bool GetOverlap() { return this->overlap; }
	inline void SetOverlap(bool overlap) { this->overlap = overlap; }
	inline int GetDamage() { return this->damage; }
};