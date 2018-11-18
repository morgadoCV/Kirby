#pragma once
#ifndef __PARTICLESYSTEM_H__
#define __PARTICLESYSTEM_H__

#include "j1Module.h"
#include "j1Scene.h"
#include "j1App.h"
#include "p2Point.h"
#include "p2Defs.h"
#include "SDL\include\SDL_rect.h"

#define MAX_TIMELIFE 255
#define NORMAL_SPEED_Y 180

enum P_Direction { P_NON, P_UP, P_DOWN, P_LEFT, P_RIGHT, P_RANDOM_X, P_RANDOM_Y, P_RANDOM, P_RANDOM_FIREWORK };

class P_Follow;
class P_Fire;

class ParticleManager : public j1Module
{
public:

	ParticleManager();

	// Destructor
	~ParticleManager();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	virtual bool Update(float dt);

	// Called before all Updates
	virtual bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	//FUNCTIONS TO CREATE

	//Create & Delete Follow Group
	void CreateFollow_P(fPoint* object_follow, fPoint offset, SDL_Rect initial_rect, iPoint area = { 12, 2 }, iPoint timelife = { 15,5 }, int size = 1, int num_textures = 4, int num_particles = 20, bool active_ = false, bool isMouse = false);
	bool DeleteFollow_p(P_Follow* group);

	//Create & DeleteFire Group
	void CreateFire_Particle(fPoint position_static, SDL_Rect initial_rect, iPoint area = { 12, 2 }, iPoint timelife = { 15,5 }, fPoint speed = { 0,0 }, P_Direction p_direction = P_NON, int size = 1, int num_particles = 20, int num_textures = 4, bool active_ = false);
	bool DeleteFire_p(P_Fire* group);

	void DeleteFireGroup();



public:

	p2List<P_Follow*> Group_Follow;
	p2List<P_Fire*> Group_Fire;

	SDL_Texture* atlas_particle = nullptr;





};

#endif // __PARTICLESYSTEM_H__