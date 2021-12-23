#include "GameManager.h"
#include "Physics.h"
#include "Collider.h"
#include "MonsterManager.h"
#include "SwordMonster.h"
#include "Skul.h"

HRESULT GameManager::Init()
{
	physics = new Physics;
	monsterManager = new MonsterManager;
	skul = new Skul;
	return S_OK;
}

Skul* GameManager::SpawnSkul(Collider* collider)
{
	skul->Init(collider, this->physics);
	return skul;
}

void GameManager::CreateSwordMonster(POINT pos, Collider* collider, Collider* raycast)
{
	monsterManager->CreateMonster(pos, collider, raycast, this->physics);
}

Collider* GameManager::CreateCollider(POINT pos, POINT bodySize, ColliderTag colliderTag, bool overlap, int damage)
{
	return physics->CreateCollider(pos, bodySize, colliderTag, overlap, damage);
}

void GameManager::PhysicsRender(HDC hdc)
{
	physics->Render(hdc);
}

void GameManager::PhysicsUpdate()
{
	physics->Update();
}

void GameManager::SwordMonsterRender(HDC hdc)
{
	monsterManager->Render(hdc);
}

void GameManager::SwordMonsterUpdate()
{
	monsterManager->Update();
}

void GameManager::DeleteMonster(SwordMonster* monster)
{
	monsterManager->DeleteMonster(monster);
}

int GameManager::GetEnemyCount()
{
	return monsterManager->GetEnemyCount();
}
