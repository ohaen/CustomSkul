#include "Skul.h"
#include "Image.h"
#include "Collider.h"
#include "Physics.h"


#define GRAVITY 60
#define JUMPFORCE 1000
#define MOVESPEED 600
#define MAXHP 100

Skul* Skul::Init(Collider* collider, Physics* physics)
{
	action = eStatus::Idle;
	firstSkulType = skulType::Nomal;
	mainSkul = IMG_MGR->FindImage(eImageTag::Skul);
	mainSkulWalk = IMG_MGR->FindImage(eImageTag::SkulWalk);
	littleBone = IMG_MGR->FindImage(eImageTag::SkulLittleBone);

	skulCollider = collider;
	myPhysics = physics;
	hitBox = nullptr;

	elapsd = 0;
	hitElapsd = 0;
	skulFrame = 0;
	skulDir = 1;
	dashCount = 2;
	invinvibilityElapsd = 0;

	jump = false;
	doJump = false;
	doDown = true;
	doubleJump = false;
	delay = false;
	comboAttack = false;
	hitReady = true;
	invinvibility = false;
	doRender = true;

	moveSpeed = MOVESPEED;
	jumpForce = JUMPFORCE;
	downForce = 0;
	skulPos.x = WIN_SIZE_X / 2-53;		//Temp pos
	skulPos.y = WIN_SIZE_Y / 2-65;

	damage = 10;
	MaxHP = MAXHP;
	currHP = MAXHP;
	return this;
}

void Skul::Update()
{
	elapsd += DELTA_TIME;

	if (dashCount < 2)
	{
		if (dashElapsd >= 2)
		{
			dashElapsd = 0;
			++dashCount;
		}
		else
		{
			dashElapsd += DELTA_TIME;
		}
	}

	if (dashTime > 0)
	{
		dashTime -= DELTA_TIME;
		Dash();
	}

	if (invinvibility)
	{
		invinvibilityCount -= DELTA_TIME;
		invinvibilityElapsd += DELTA_TIME;

		if (invinvibilityElapsd >= 0.1f)
		{
			invinvibilityElapsd = 0;
			doRender = !doRender;
		}

		if (invinvibilityCount < 0)
		{
			invinvibilityCount = 0;
			invinvibility = false;
			hitReady = true;
			doRender = true;
		}
	}

	if (jump)			//jump status
	{
		Jump();
	}
	if (!(dashTime > 0))
	{
		Down();
	}
	//if(jumpForce > 800.0f)
		//(skulCollider->CheckCollider({ 0, (int)(jumpForce * DELTA_TIME) }))

	//if (doubleJump)
	//{
	//	this->downForce = 0;
	//	this->jumpForce = JUMPFORCE;
	//	doubleJump = false;
	//}
	if (InputManager::GetButton(VK_RIGHT) && ((action != eStatus::Attatk && action != eStatus::ComboAttack)||jump))
	{
		if (!(GetDelay()))
		{
			SetSkulAction(Skul::eStatus::Move);
		}

		SetSkulDir(1);
		Walk();
	}
	else if (InputManager::GetButton(VK_LEFT) && ((action != eStatus::Attatk && action != eStatus::ComboAttack)||jump))
	{
		if (!(GetDelay()))
		{
			SetSkulAction(Skul::eStatus::Move);
		}

		SetSkulDir(-1);
		Walk();
	}
	else if (!(GetDelay()))
	{
		SetSkulAction(Skul::eStatus::Idle);
	}

	if (InputManager::GetButtonDown('C') && !(GetDelay()))
	{
		//if (GetJumpStatus())
		{
			Jump();
		}

	}
	if (InputManager::GetButtonDown('X'))
	{
		if (!(GetDelay()))
		{
			Attack();
		}
		else
		{
			ComboAttack();
		}
	}

	if (InputManager::GetButtonDown('Z'))
	{
		if (dashCount)
		{
			dashTime = 0.1f;
			--dashCount;
		}
	}

	if (InputManager::GetButtonDown('A'))
	{
		SCENE_MGR->ChangeScene(eSceneTag::TutorialScene);
	//	for (int i = 0; i < 100; ++i)
	//	{
	//		for (int j = 0; j < 100; ++j)
	//		{
	//			cout << '1';
	//		}
	//	}
	}

	Collider* hit = skulCollider->FindTagCollider(skulCollider, ColliderTag::MonsterAttack);
	if (hit != nullptr && hitReady)
	{
		TakeDamage(hit->GetDamage());
		cout << "히트다히트\n";
	}
	Collider* exit = skulCollider->FindTagCollider(skulCollider, ColliderTag::Exit);
	if (exit != nullptr && InputManager::GetButtonDown('F'))
	{
		SCENE_MGR->SetStageInfo(SCENE_MGR->GetStageInfo() + 1);
		//SCENE_MGR->ChangeScene(eSceneTag::TutorialScene);
		SCENE_MGR->ChangeScene(eSceneTag::MainMenuScene);
	}

	Animation();



}

void Skul::Render(HDC hdc)
{
	if (doRender)
	{
		if (action == eStatus::Idle)
		{
			if (skulFrame > 3) //idle maxframe
			{
				skulFrame = 0;
			}
			if (skulDir == 1)
			{
				//mainRender(hdc, (int)skulPos.x, (int)skulPos.y, skulFrame, 0, 2.0f);
				littleBone->Render(hdc, (int)skulPos.x, (int)skulPos.y, skulFrame, 0, 2.0f);
			}
			else
			{
				//mainRender(hdc, (int)skulPos.x, (int)skulPos.y, skulFrame, 1, 2.0f);
				littleBone->Render(hdc, (int)skulPos.x, (int)skulPos.y, skulFrame, 11, 2.0f);
			}
		}
		else if (action == eStatus::Move)
		{
			if (skulDir == 1)
			{
				//mainSkulWalk->Render(hdc, (int)skulPos.x, (int)skulPos.y, skulFrame, 0, 2.0f);
				littleBone->Render(hdc, (int)skulPos.x, (int)skulPos.y, skulFrame, 1, 2.0f);
			}
			else
			{
				//mainSkulWalk->Render(hdc, (int)skulPos.x, (int)skulPos.y, skulFrame, 1, 2.0f);
				littleBone->Render(hdc, (int)skulPos.x, (int)skulPos.y, skulFrame, 12, 2.0f);
			}
		}
		else if (action == eStatus::Attatk)
		{
			if (skulDir == 1)
			{
				littleBone->Render(hdc, (int)skulPos.x, (int)skulPos.y, skulFrame, 3, 2.0f);
			}
			else
			{
				littleBone->Render(hdc, (int)skulPos.x, (int)skulPos.y, 4 - skulFrame, 14, 2.0f);
			}
		}
		else if (action == eStatus::ComboAttack)
		{
			if (skulDir == 1)
			{
				littleBone->Render(hdc, (int)skulPos.x, (int)skulPos.y, skulFrame, 4, 2.0f);
			}
			else
			{
				littleBone->Render(hdc, (int)skulPos.x, (int)skulPos.y, 3 - skulFrame, 15, 2.0f);
			}
		}
	}
}

void Skul::Release()
{
	SAFE_RELEASE(skulCollider);
	SAFE_RELEASE(hitBox);
	myPhysics = nullptr;
}

void Skul::Animation()
{
	if (action == eStatus::Idle)
	{
		if (skulFrame > 4)
		{
			skulFrame = 1;
		}
		if (elapsd > 0.17)
		{
			if (skulFrame < 3)
			{
				skulFrame++;
			}
			else
			{
				skulFrame = 0;
			}
			elapsd = 0;
		}
	}
	else if (action == eStatus::Move)
	{
		if (elapsd > 0.07)
		{
			if (skulFrame < 6)
			{
				skulFrame++;
			}
			else
			{
				skulFrame = 0;
			}
			elapsd = 0;
		}
	}

	if (action == eStatus::Attatk)
	{
		if (elapsd > 0.1)
		{
			if (skulFrame < 4)
			{
				skulFrame++;
				if (skulFrame == 2)
				{
					if (skulDir == 1)
					{
						hitBox = myPhysics->CreateCollider(
							{ skulCollider->GetColliderPos().x + 30 ,skulCollider->GetColliderPos().y },
							{ 100, 100 }, ColliderTag::PlayerAttack, true, damage);

					}
					else
					{
						hitBox = myPhysics->CreateCollider(
							{ skulCollider->GetColliderPos().x - 30 ,skulCollider->GetColliderPos().y },
							{ 100, 100 }, ColliderTag::PlayerAttack, true, damage);
					}
				}
				if (skulFrame == 3)
				{
					myPhysics->DeleteCollider(hitBox);
				}
			}
			else
			{
				skulFrame = 0;
				if (comboAttack)
				{
					action = eStatus::ComboAttack;
				}
				else
				{
					action = eStatus::Idle;
					delay = false;
				}
			}
			elapsd = 0;
		}
	}
	if (action == eStatus::ComboAttack)
	{
		if (elapsd > 0.1)
		{
			if (skulFrame < 3)
			{
				skulFrame++;
				if (skulFrame == 1)
				{
					if (skulDir == 1)
					{
						hitBox = myPhysics->CreateCollider(
							{ skulCollider->GetColliderPos().x + 30 ,skulCollider->GetColliderPos().y },
							{ 100, 100 }, ColliderTag::PlayerAttack, true, damage);

					}
					else
					{
						hitBox = myPhysics->CreateCollider(
							{ skulCollider->GetColliderPos().x - 30 ,skulCollider->GetColliderPos().y },
							{ 100, 100 }, ColliderTag::PlayerAttack, true, damage);
					}
				}
				if (skulFrame == 2)
				{
					hitBox = myPhysics->DeleteCollider(hitBox);
				}
			}
			else
			{
				skulFrame = 0;
				delay = false;
				comboAttack = false;
				action = eStatus::Idle;
			}
			elapsd = 0;
		}
	}
}

void Skul::Walk()
{
	if (skulCollider->MoveTo({ skulDir * (int)(moveSpeed * DELTA_TIME),0 }))
	{
		CAM_MGR->AddCameraPos(skulDir * (int)(moveSpeed * DELTA_TIME), 0);
	}
}

void Skul::Jump()
{
	if (jump == false)
	{
		this->jump = true;
		this->doJump = true;
		this->doDown = false;
	}
	if (doJump)
	{
		if (skulCollider->MoveTo({ 0,(int)-(jumpForce * DELTA_TIME) }))
		{
			CAM_MGR->AddCameraPos(0, (int)-(jumpForce * DELTA_TIME));
			jumpForce -= GRAVITY;

		}
		else
		{
			this->jumpForce = JUMPFORCE;
			doJump = false;
			doDown = true;
		}
	}
}

void Skul::Down()
{
	if (doDown)
	{
		if (skulCollider->MoveTo({ 0,(int)(downForce * DELTA_TIME) }))
		{
			CAM_MGR->AddCameraPos(0, (int)(downForce * DELTA_TIME));
			if (downForce < 1200)
			{
				downForce += GRAVITY;
			}
		}
		else
		{

			this->jump = false;
			this->doJump = false;
			this->doDown = true;
			this->downForce = 0;

		}
	}
}

void Skul::Attack()
{

	action = eStatus::Attatk;
	skulFrame = 0;
	delay = true;
}

void Skul::ComboAttack()
{
	if (!jump)
	{
		comboAttack = true;
	}
}

void Skul::TakeDamage(int damage)
{
	currHP -= damage;
	if (currHP <= 0)
	{
		SCENE_MGR->ChangeScene(eSceneTag::MainMenuScene);
		cout << "death\n";
	}
	else
	{
		hitReady = false;
		Invinvibility(1);
	}
}

void Skul::Invinvibility(int second)
{
	invinvibility = true;
	invinvibilityCount = (float)second;
}

void Skul::Dash()
{
	if (skulCollider->MoveTo({ skulDir * (int)(moveSpeed*4 * DELTA_TIME),0 }))
	{
		CAM_MGR->AddCameraPos(skulDir * (int)(moveSpeed*4 * DELTA_TIME), 0);
	}
}

