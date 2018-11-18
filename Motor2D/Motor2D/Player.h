#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "j1Module.h"
#include "Animation.h"
#include "ParticleManager.h"
#include "P_Follow.h"
#include "Criature.h"

#define AnimationSpeed4 0.15f
#define AnimationSpeed3 0.2f
#define AnimationSpeedDead 0.019f

#define Velocity_X 80
#define Velocity_Y 580
#define OFFSET_Y 20

#define Gravity 1
#define Gravity_LOW 1


struct SDL_Texture;



enum Levels
{
   LVL_1,
   LVL_2
};

class Player : public Criature
{
public:

	Player();

	// Destructor
	virtual ~Player();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	void ChangeLVL();

	void FollowPlayer(float speed);

	void Input(float dt);

	void Setzero();

	void processPos();

	void processGravity(float dt);

	void Draw();

	// Called before all Updates
	bool PostUpdate();

	//Save and Load functions
	bool Load(pugi::xml_node &);
	bool Save(pugi::xml_node&)const;

	int GetDirection();

	bool CanFollowPlayer();

	void ChangeMap(const char* path);
	iPoint Getposition()const;
	iPoint* GetpositionPointer();
	
	//Debuf Functions
	void StartFromFirstLvl();

	void StartFromBeginCurrentLvl();
	
	// Called before quitting
	bool CleanUp();

	void OnCollision(Collider*, Collider*);

private:
	SDL_Texture* graphics = nullptr;
	Levels actualvl;


	bool GoDead = false;
	bool fade = false;
	bool notRepeatDead = false;
	bool now_switch = false;
	bool apply_g = false;
	



public:
	State state;
	Direction direction;

	bool isMove = false;
	P_Follow* particlePlayer;
	//Animations
	Animation* current_animation;
	Animation idle;
	Animation walk_left;
	Animation walk_right;
	Animation run_left;
	Animation run_right;
	Animation jump_left;
	Animation jump_right;
	Animation fly_left;
	Animation fly_right;
	Animation dead;


};

#endif // __PLAYER_H__