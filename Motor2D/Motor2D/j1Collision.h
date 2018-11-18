#pragma once
#ifndef __j1Collision_H__
#define __j1Collision_H__

#define MAX_COLLIDERS 100

#include "j1Module.h"

#include "SDL\include\SDL_rect.h"

class Criature;

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_PLAYER,
	COLLIDER_ENEMY_NORMAL,
	COLLIDER_ENEMY_FLY,

	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete = false;
	COLLIDER_TYPE type;
	Criature* callback = nullptr;

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, Criature* callback = nullptr) :
		rect(rectangle),
		type(type),
		callback(callback)
	{}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	bool CheckCollision(const SDL_Rect& r) const;
};

class ModuleCollision : public j1Module
{
public:

	ModuleCollision();
	~ModuleCollision();

	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Criature* callback = nullptr);
	bool EraseCollider(Collider* collider);
	void DebugDraw();

private:

	Collider* colliders[MAX_COLLIDERS];
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
public:
	bool debug = false;
};

#endif // __ModuleCollision_H__