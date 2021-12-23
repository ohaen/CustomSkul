#include "SwordMonster.h"
#include "Image.h"
#include "Collider.h"
#include "Physics.h"

HRESULT SwordMonster::Init(POINT pos, Collider* collider, Collider* ray, Physics* physics)
{
	swordIdle = IMG_MGR->FindImage(eImageTag::SwordIdle);
	swordAttack = IMG_MGR->FindImage(eImageTag::SwordAttack);
	swordHit = IMG_MGR->FindImage(eImageTag::SwordHit);
	swordWalk = IMG_MGR->FindImage(eImageTag::SwordWalk);

	monsterAction = action::Idle;
	this->raycast = ray;
	this->collider = collider;
	this->pos = pos;
	myPhysics = physics;


	HP = 100;
	damage = 5;
	attackDelay = 3;
	moveSpeed = 200;

	frame = 0;
	dir = 0;
	elapsd = 0;

	hitReady = true;
	attackReady = true;
	return S_OK;
}

void SwordMonster::Update()
{
	if (monsterAction != action::Death)
	{
		elapsd += DELTA_TIME;
		if (!attackReady)
		{
			attackElapsd += DELTA_TIME;
		}

		if (attackElapsd > attackDelay)
		{
			attackElapsd = 0;
			attackReady = true;
		}

		Collider* skul = raycast->FindTagCollider(raycast, ColliderTag::Player);
		if (skul != nullptr && attackReady && monsterAction != action::Death && monsterAction != action::Hit)
		{
			if (abs(skul->GetColliderPos().x - collider->GetColliderPos().x) < 100)
			{
				cout << "공격범위 안\n";
				if (skul->GetColliderPos().x < collider->GetColliderPos().x)
				{
					dir = 0;
				}
				else
				{
					dir = 1;
				}
				cout << "뭔가 닿긴함\n";
				frame = 0;
				attackReady = false;
				monsterAction = action::Attack;
			}
			else
			{
				if (skul->GetColliderPos().x < collider->GetColliderPos().x)
				{
					dir = 0;
				}
				else
				{
					dir = 1;
				}
				if (monsterAction != action::Walk)
				{
					frame = 0;
				}
				Walk();
				monsterAction = action::Walk;

			}
		}
		else if (monsterAction != action::Attack && monsterAction != action::Hit)
		{
			monsterAction = action::Idle;
		}

		Collider* hit = collider->FindTagCollider(collider, ColliderTag::PlayerAttack);
		if (hit != nullptr && hitReady)
		{
			TakeDamage(hit->GetDamage());
			cout << "히트다히트\n";
		}

		if (hitBox != nullptr && monsterAction != action::Attack)
		{
			hitBox = myPhysics->DeleteCollider(hitBox);
		}

		Animation();
	}
}

void SwordMonster::Render(HDC hdc)
{
	if (monsterAction == action::Idle)
	{
		if (dir == 0)
		{
			swordIdle->Render(hdc,pos.x - CAM_MGR->GetCamaraPos().x - 15 ,pos.y - CAM_MGR->GetCamaraPos().y - 20, frame, 0, 2.0f);
		}
		else
		{
			swordIdle->Render(hdc, pos.x - CAM_MGR->GetCamaraPos().x - 15, pos.y - CAM_MGR->GetCamaraPos().y - 20, frame, 1, 2.0f);
		}
	}

	if (monsterAction == action::Attack)
	{
		if (dir == 0)
		{
			swordAttack->Render(hdc, pos.x - CAM_MGR->GetCamaraPos().x - 20, pos.y - CAM_MGR->GetCamaraPos().y - 35, frame, 0, 2.0f);
		}
		else
		{
			swordAttack->Render(hdc, pos.x - CAM_MGR->GetCamaraPos().x - 20, pos.y - CAM_MGR->GetCamaraPos().y - 35, frame, 1, 2.0f);
		}
	}

	if (monsterAction == action::Hit)
	{
		if (dir == 0)
		{
			swordHit->Render(hdc, pos.x - CAM_MGR->GetCamaraPos().x - 15, pos.y - CAM_MGR->GetCamaraPos().y - 20, frame, 0, 2.0f);
		}
		else
		{
			swordHit->Render(hdc, pos.x - CAM_MGR->GetCamaraPos().x - 15, pos.y - CAM_MGR->GetCamaraPos().y - 20, frame, 1, 2.0f);
		}
	}

	if (monsterAction == action::Walk)
	{
		if (dir == 0)
		{
			swordWalk->Render(hdc, pos.x - CAM_MGR->GetCamaraPos().x - 15, pos.y - CAM_MGR->GetCamaraPos().y - 20, frame, 0, 2.0f);
		}
		else
		{
			swordWalk->Render(hdc, pos.x - CAM_MGR->GetCamaraPos().x - 15, pos.y - CAM_MGR->GetCamaraPos().y - 20, frame, 1, 2.0f);
		}
	}

}

void SwordMonster::Release()
{
}

void SwordMonster::Animation()
{
	if (monsterAction == action::Idle)
	{
		if (elapsd > 0.1)
		{
			if (frame < 5)
			{
				frame++;
			}
			else
			{
				frame = 0;
			}
			elapsd = 0;
		}
	}

	if (monsterAction == action::Attack)
	{
		if (frame == 0)
		{
			if (elapsd > 0.7)
			{
				++frame;
			}
		}
		else
		{
			if (elapsd > 0.1)
			{
				if (frame < 3)
				{
					if (dir == 0)
					{
						if (frame == 1)
						{
							hitBox = myPhysics->CreateCollider(
								{ collider->GetColliderPos().x -75,collider->GetColliderPos().y },
								{ 100, 100 }, ColliderTag::MonsterAttack, true, damage);
						}
						Move({-15,0});
					}
					else
					{
						if (frame == 1)
						{
							hitBox = myPhysics->CreateCollider(
								{ collider->GetColliderPos().x + 75,collider->GetColliderPos().y },
								{ 100, 100 }, ColliderTag::MonsterAttack, true, damage);
						}
						Move({ 15,0 });
					}
					frame++;
				}
				else
				{
					monsterAction = action::Idle;
					//attackReady = true;
					frame = 0;
				}
				elapsd = 0;
			}
		}
	}

	if (monsterAction == action::Hit)
	{
		if (elapsd > 0.15)
		{
			if (frame < 1)
			{
				if (dir == 0)
				{
					Move({ 15,0 });
				}
				else
				{
					Move({ -15,0 });
				}
				frame++;
			}
			else
			{
				hitReady = true;
				monsterAction = action::Idle;
				frame = 0;
			}
			elapsd = 0;
		}
	}

	if (monsterAction == action::Walk)
	{
		if (elapsd > 0.2)
		{
			if (frame < 7)
			{

				frame++;
			}
			else
			{
				frame = 0;
			}
			elapsd = 0;
		}
	}

}

void SwordMonster::Move(POINT addPos)
{
	if (collider->MoveTo({ addPos.x , addPos.y }))
	{
		raycast->SetPos(collider->GetColliderPos());
		pos.x += addPos.x;
		pos.y += addPos.y;
	}
}

void SwordMonster::TakeDamage(int damage)
{
	frame = 0;
	if (HP <= 0)
	{
		Death();
	}
	else
	{
		cout << this->HP << "\n";
		hitReady = false;
		monsterAction = action::Hit;
		HP -= damage;
	}
}

void SwordMonster::Walk()
{
	if (dir == 0)
	{
		Move({ (int)-(moveSpeed * DELTA_TIME),0 });
	}
	else
	{
		Move({ (int)(moveSpeed * DELTA_TIME),0 });
	}
}

void SwordMonster::Death()
{
	monsterAction = action::Death;
	collider = myPhysics->DeleteCollider(collider);
	raycast = myPhysics->DeleteCollider(raycast);
	cout << "주금\n";
}
