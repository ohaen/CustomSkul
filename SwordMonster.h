#pragma once
#include "GameObject.h"

class Image;
class Physics;
class SwordMonster : public GameObject
{
public:
	enum class action
	{
		Idle,
		Attack,
		Hit,
		Walk,
		Death,
	};
private:
	Physics* myPhysics;
	Collider* collider;
	Collider* raycast;
	Collider* hitBox;

	Image* swordIdle;
	Image* swordAttack;
	Image* swordHit;
	Image* swordWalk;

	action monsterAction;

	POINT pos;
	int HP;
	int damage;

	int frame;
	int dir;
	float moveSpeed;

	float elapsd;
	float attackElapsd;
	float attackDelay;

	bool attackReady;
	bool hitReady;
public:
	virtual ~SwordMonster() {};
	HRESULT Init(POINT pos, Collider* collider, Collider* ray, Physics* physics);

	void Update();
	void Render(HDC hdc);
	void Release();
	void Animation();

	inline action GetMonsterAction() { return this->monsterAction; }

	void Move(POINT addPos);
	void TakeDamage(int damage);
	void Walk();
	void Death();

};

