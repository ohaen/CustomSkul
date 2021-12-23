#pragma once
#include "Config.h"
#include "GameObject.h"

class Image;
class Physics;
class Skul : public GameObject
{
public:

	enum class eStatus
	{
		Idle,
		Move,
		Attatk,
		ComboAttack,
		JumpAttack,
		Jump,
		doDown,
		Dash,
	};
private:
	Image* mainSkul;
	Image* mainSkulWalk;
	Image* littleBone;

	skulType firstSkulType;
	Collider* skulCollider;
	Collider* hitBox;
	Physics* myPhysics;

	eStatus action;
	bool jump;
	bool doJump;
	bool doDown;
	bool doubleJump;
	bool delay;
	bool comboAttack;
	bool hitReady;
	bool invinvibility;
	bool doRender;

	int skulFrame;
	float elapsd;
	float moveSpeed;
	float jumpForce;
	float downForce;
	float hitElapsd;
	float dashElapsd;
	float dashTime;

	float invinvibilityCount;
	float invinvibilityElapsd;
	
	int skulDir;
	POINT skulPos;
	int dashCount;

	int damage;
	int MaxHP;
	int currHP;
public:
	virtual ~Skul() {};
	Skul* Init(Collider* collider, Physics* physics);
	void Update();
	void Render(HDC hdc);
	void Release();
	void Animation();

	inline void SetSkulDir(int skulDir) { this->skulDir = skulDir; };
	inline void SetSkulAction(eStatus action) { this->action = action; };
	inline bool GetJumpStatus() { return this->jump; }
	inline bool GetDelay() { return this->delay; }
	inline int GetDamage() { return this->damage; }
	inline int GetMaxHP() { return this->MaxHP; }
	inline int GetCurrHP() { return this->currHP; }
	inline skulType GetSkulType() { return this->firstSkulType; }


	void Walk();
	void Jump();
	void Down();
	void Attack();
	void ComboAttack();
	void TakeDamage(int damage);
	void Invinvibility(int second);
	void Dash();


	
};
