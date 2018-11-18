#pragma once
#include "j1Module.h"
#include "p2Point.h"
#include "Animation.h"
//#include "ParticleManager.h"
//#include "P_Follow.h"
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
class EnemyNormal : public j1Module
{
public:
	EnemyNormal();
	~EnemyNormal();
	// Called before render is available
	bool Awake(pugi::xml_node& conf);
	// Called before the first frame
	bool Start();
	// Called before all Updates
	bool PreUpdate();
	// Called each loop iteration
	bool Update(float dt);
	void processPos();
	void processGravity();
	void ReturnToZero();
	void Draw();
	// Called before all Updates
	bool PostUpdate();
	//Save and Load functions
	bool Load(pugi::xml_node &);
	bool Save(pugi::xml_node&)const;
	int GetDirection() const;
	fPoint* Getposition() const;
	// Called before quitting
	bool CleanUp();
};