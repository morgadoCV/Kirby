#include "P_Fire.h"
#include "Particle.h"
#include "j1Window.h"

P_Fire::P_Fire(fPoint position_static, SDL_Rect initial_rect, iPoint area_, iPoint timelife_, fPoint speed_particle, P_Direction p_direction, int size, int num_particles, int num_textures, bool active_)
{
	pos.x = position_static.x;
	pos.y = position_static.y;

	speed = speed_particle;


	//
	area = area_;
	timelife = timelife_;
	number_particles = num_particles;
	sizeParticle = size;
	godelete = false;
	active = active_;
	n_textures = num_textures;
	size_rect = initial_rect.w;
	for (int i = 0; i < num_particles; i++)//
	{
		Particle* temp = new Particle(pos, area, timelife, speed, p_direction, initial_rect, size_rect, n_textures, true);
		particle.PushBack(temp);
	}
}

P_Fire::~P_Fire()
{
}

bool P_Fire::Update(float dt)
{

	MoveParticles();


	return true;
}

bool P_Fire::PostUpdate()
{
	render(pos);
	return true;
}

void P_Fire::render(fPoint pos)
{
	if (active)
	{
		//Check if the particle dead
		for (int i = 0; i < number_particles; i++)
		{
			if (particle[i]->isDead())
			{
				particle[i]->Modify(pos, area, timelife, iPoint(0, n_textures));
			}
		}
	}

	//Draw particles
	for (int i = 0; i < number_particles; i++)
	{
		particle[i]->render(sizeParticle);
	}
}

void P_Fire::MoveParticles()
{
	for (int i = 0; i < number_particles; i++)
	{
		particle[i]->Move(fPoint(particle[i]->GetSpeed().x, particle[i]->GetSpeed().y));
	}
}
