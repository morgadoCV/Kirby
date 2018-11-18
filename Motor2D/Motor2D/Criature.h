#pragma once
#include "p2SString.h"
#include "j1Collision.h"
#include "p2Log.h"

struct SDL_Texture;


enum State
{
	IDLE,
	W_LEFT,
	W_RIGHT,
	RUN_LEFT,
	RUN_RIGHT,
	JUMP_LEFT,
	JUMP_RIGHT,
	FLY_LEFT,
	FLY_RIGHT,
	DEAD
};

enum Direction
{
	NON,
	UP,
	LEFT,
	DOWN,
	RIGHT
};

class Criature
{
public:
	Criature() {};
	virtual ~Criature() {};
	// Called before render is available
	virtual bool Awake()
	{
		return true;
	}
	// Called before the first frame
	virtual bool Start()
	{
		return true;
	}
	// Called each loop iteration
	virtual bool PreUpdate()
	{
		return true;
	}
	// Called each loop iteration
	virtual bool Update(float dt)
	{
		return true;
	}
	// Called each loop iteration
	virtual bool PostUpdate()
	{
		return true;
	}
	// Called before quitting
	virtual bool CleanUp()
	{
		return true;
	}

	//virtual load/save function
	virtual bool Load(pugi::xml_node&)
	{
		return true;
	}

	virtual bool Save(pugi::xml_node&)const
	{
		return true;
	}

	virtual void OnCollision(Collider*, Collider*) {}

public:
	State		state;
	Direction	direction;
	p2SString	name;
	bool		active;
	Collider*	collision_feet = nullptr;
};