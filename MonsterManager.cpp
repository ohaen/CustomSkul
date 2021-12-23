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
}
