#pragma once
#include "Config.h"
#include "GameEntity.h"

class Collider;
class GameObject : public GameEntity
{
protected:
	Collider* collider = nullptr;
public:
	GameObject();
	~GameObject();
};

