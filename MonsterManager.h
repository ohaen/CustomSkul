#pragma once
#include "GameEntity.h"

class SwordMonster;
class Collider;
class Physics;
class MonsterManager : public GameEntity
{
private:
	vector<SwordMonster*> vecSword;
public:
	virtual ~MonsterManager() {};
	void CreateMonster(POINT pos, Collider* collider, Collider* raycast, Physics* physics);
	void DeleteMonster(SwordMonster* monster);

	inline size_t GetEnemyCount() { return vecSword.size(); }
	void Render(HDC hdc);
	void Update();
	void Release();
};

