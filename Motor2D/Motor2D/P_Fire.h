#pragma once
#ifndef _P_FIRE_H_
#define _P_FIRE_H_

#include "ParticleManager.h"
#include "p2DynArray.h"

class Particle;

class P_Fire
{
public:
	P_Fire(fPoint position_static, SDL_Rect initial_rect = { 0,0,8,2 }, iPoint area = { 12, 2 }, iPoint timelife = { 15,5 }, fPoint speed = { 0,0 }, P_Direction p_direction = P_NON, int size = 1, int num_particles = 20, int num_textures = 4, bool active_ = false);

	~P_Fire();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	void render(fPoint pos);

	void MoveParticles();

public:
	p2DynArray<Particle*> particle;
	//Num of particles
	int number_particles;
	int sizeParticle;

	//test
	fPoint* object_follow;

	//wind
	iPoint timelife;

	//position
	fPoint pos;
	int size_rect;
	int n_textures;
	iPoint area;

	//velocity
	fPoint speed;
	bool active;

	bool godelete;

};


#endif /*_P_FIRE_H_*/