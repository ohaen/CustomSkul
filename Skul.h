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
	Image* mainSkul = nullptr;
	Image* mainSkulWalk = nullptr;
	Image* littleBone = nullptr;

	skulType firstSkulType = skulType::Nomal;
	Collider* skulCollider = nullptr;
	Collider* hitBox = nullptr;
	Physics* myPhysics = nullptr;

	eStatus action = eStatus::Idle;
	bool jump = 0;
	bool doJump = 0;
	bool doDown = 0;
	bool doubleJump = 0;
	bool delay = 0;
	bool comboAttack = 0;
	bool hitReady = 0;
	bool invinvibility = 0;
	bool doRender = 0;

	int skulFrame = 0;
	float elapsd = 0.0f;
	float moveSpeed = 0.0f;
	float jumpForce = 0.0f;
	float downForce = 0.0f;
	float hitElapsd = 0.0f;
	float dashElapsd = 0.0f;
	float dashTime = 0.0f;

	float invinvibilityCount = 0.0f;
	float invinvibilityElapsd = 0.0f;
	
	int skulDir = 0;
	POINT skulPos;
	int dashCount = 0;

	int damage = 0;
	int MaxHP = 0;
	int currHP = 0;
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
