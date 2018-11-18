#pragma once
#include "j1Module.h"
#include "p2Point.h"
#include "Animation.h"
//#include "ParticleManager.h"
//#include "P_Follow.h"

#define AnimationSpeed4 0.15f
#define AnimationSpeedDead 0.019f

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
class EnemyFly : public j1Module
{
public:
	EnemyFly();
	~EnemyFly();
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

private:
	Animation idle;
	Animation idle_left;
	Animation fly_rignt;
	Animation fly_left;
	Animation dead;

};