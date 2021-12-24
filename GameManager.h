#pragma once
#include "GameEntity.h"

class Skul;
class SwordMonster;
class MonsterManager;

class Physics;
class Collider;
class GameManager : public GameEntity
{
protected:
	Physics* physics = nullptr;
	MonsterManager* monsterManager = nullptr;
	Skul* skul = nullptr;
public:
	virtual ~GameManager() {};
	HRESULT Init();
	void Release();

	Skul* SpawnSkul(Collider* collider);
	void CreateSwordMonster(POINT pos, Collider* collider, Collider* raycast);
	Collider* CreateCollider(POINT pos, POINT bodySize, ColliderTag colliderTag, bool overlap = false, int damage = 0);
	void PhysicsRender(HDC hdc);
	void PhysicsUpdate();
	
	void SwordMonsterRender(HDC hdc);
	void SwordMonsterUpdate();
	void DeleteMonster(SwordMonster* monster);
	int GetEnemyCount();
};

