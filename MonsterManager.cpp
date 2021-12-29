#include "MonsterManager.h"
#include "SwordMonster.h"
#include "Collider.h"

void MonsterManager::CreateMonster(POINT pos, Collider* collider, Collider* raycast, Physics* physics)
{
	SwordMonster* newMonster = new SwordMonster;
	newMonster->Init(pos, collider, raycast, physics);
	vecSword.push_back(newMonster);
}

void MonsterManager::DeleteMonster(SwordMonster* monster)
{
	auto it = find(vecSword.begin(), vecSword.end(), monster);
	SAFE_DELETE(*it);
	vecSword.erase(it);
}

void MonsterManager::Render(HDC hdc)
{
	for (int i = 0; i < vecSword.size(); ++i)
	{
		vecSword[i]->Render(hdc);
	}
}

void MonsterManager::Update()
{
	for (int i = 0; i < vecSword.size(); ++i)
	{
		if (vecSword[i]->GetMonsterAction() == SwordMonster::action::Death)
		{
			DeleteMonster(vecSword[i]);
		}
	}
	for (int i = 0; i < vecSword.size(); ++i)
	{
		vecSword[i]->Update();
	}
}

void MonsterManager::Release()
{
	SwordMonster* monster;
	for (auto it = vecSword.begin(); it != vecSword.end();)
	{
		monster = (*it);
		it = vecSword.erase(it);
		SAFE_DELETE(monster);
	}
	vecSword.clear();
}
