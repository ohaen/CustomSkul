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
	Physics* physics;
	MonsterManager* monsterManager;
	Skul* skul;
public:
	HRESULT Init();

	//inline Physics* GetPhysics() { return this->physics; };

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

