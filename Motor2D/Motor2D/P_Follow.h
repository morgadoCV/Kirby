#pragma once
#ifndef _P_FOLLOW_H_
#define _P_FOLLOW_H_

#include "ParticleManager.h"
#include "p2DynArray.h"

class Particle;

class P_Follow
{
public:
	P_Follow(iPoint* object_follow, fPoint offset, SDL_Rect initial_rect = { 0,0,8,2 }, iPoint area = { 12, 2 }, iPoint timelife = { 15,5 }, int Size = 1, int num_textures = 4, int num_particles = 20, bool active_ = false, bool isMouse = false);
	~P_Follow();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	void render(fPoint pos);

	void Update_position(iPoint* pos);


public:
	//TODO 2: ---------------------------------------------------------------------
	//Create a Particle Vector, use std::vector
	//Also, create a pointer to an entity (SceneElement*)
	//And finally a pointer to an iPoint (iPoint*)
	p2DynArray<Particle*> particle;
	iPoint* object_follow;
	//-----------------------------------------------------------------------------
	//Num of particles
	int number_particles;
	int sizeParticle;

	//iPoints
	iPoint area;
	iPoint timelife;

	//position
	fPoint pos;
	fPoint offset;
	int size_rect;
	int n_textures;

	//velocity
	//fPoint speed;
	bool active;
	bool isMouse;

	bool godelete;

};


#endif /*_P_FOLLOW_H_*/