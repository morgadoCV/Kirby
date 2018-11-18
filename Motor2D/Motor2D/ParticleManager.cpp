#include "ParticleManager.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "Player.h"
#include "j1Audio.h"
#include "j1TimeNormal.h"
#include "P_Follow.h"
#include "P_Fire.h"
#include "j1Input.h"

ParticleManager::ParticleManager()
{
}

ParticleManager::~ParticleManager()
{
	
}

bool ParticleManager::Awake()
{
	return true;
}

bool ParticleManager::Start()
{
	//texture
	atlas_particle = App->tex->Load("textures/atlas_particle.png"); //1

	//Link Follow
	//Group_Follow.push_back(new P_Follow(App->scene->player, nullptr, SDL_Rect{ 0,6,2,0 }, iPoint(5, 2), iPoint(15, 5), 4, 20, true, true));

	////TODO 8: ----------------------------------------------------------------------------------
	////Uncomment
	//Group_Follow.push_back(new P_Follow(nullptr, App->input->GetMousePosition_p(), SDL_Rect{ 0,2,2,0 }, iPoint(0, 0), iPoint(15, 5), 4, 20, true, true));

	//Group_Fire.push_back(new P_Fire(nullptr, App->input->GetMousePosition_p(), iPoint(0,0), SDL_Rect{ 0,2,2,0 }, iPoint(5, 2), iPoint(12, 4), fPoint(60, -60), P_RANDOM, 65, 4, true, W_NON));
	//// ---------------------------------------------------------------------------------------

	return true;
}

bool ParticleManager::PreUpdate()
{
	return true;
}

bool ParticleManager::Update(float dt)
{
	////SET FIRE
	//if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
	//{
	//	Group_Fire.add(new P_Fire(nullptr, nullptr, App->input->GetMousePosition(), SDL_Rect{ 0,2,2,0 }, iPoint(5, 2), iPoint(12, 4), fPoint(0, -60), P_NON, 65, 4, true, W_NON));
	//}

	//Iterate all list
	//Group FOLLOW -------------------------------------------------
	p2List_item<P_Follow*>* item = Group_Follow.start;
	while (item != NULL)
	{
		item->data->Update(dt);
		item = item->next;
	}

	//Group FIRE -------------------------------------------------
	p2List_item<P_Fire*>* item_2 = Group_Fire.start;
	while (item_2 != NULL)
	{
		item_2->data->Update(dt);
		item_2 = item_2->next;
	}

	return true;
}

bool ParticleManager::PostUpdate()
{
	//Iterate all list
	//Group FOLLOW -------------------------------------------------
	p2List_item<P_Follow*>* item = Group_Follow.start;
	while (item != NULL)
	{
		item->data->PostUpdate();
		item = item->next;
	}
	//Group FRIE -------------------------------------------------
	p2List_item<P_Fire*>* item_2 = Group_Fire.start;
	while (item_2 != NULL)
	{
		item_2->data->PostUpdate();
		item_2 = item_2->next;
	}


	return true;
}

bool ParticleManager::CleanUp()
{
	p2List_item<P_Fire*>* item = Group_Fire.start;
	while (item != NULL)
	{
		item->data->particle.Clear();
		item = item->next;
	}
	Group_Fire.clear();
	
	p2List_item<P_Follow*>* item2 = Group_Follow.start;
	while (item2 != NULL)
	{
		item2->data->particle.Clear();
		item2 = item2->next;
	}
	Group_Follow.clear();

	App->tex->UnLoad(atlas_particle);
	return true;
}

//CREATE GROUPS -------------------------------------------------------------------------------------------------------------------------------------

void ParticleManager::CreateFollow_P(iPoint* object_follow, fPoint offset, SDL_Rect initial_rect, iPoint area, iPoint timelife, int size, int num_textures, int num_particles, bool active, bool isMouse)
{
	Group_Follow.add(new P_Follow(object_follow, offset, initial_rect, area, timelife, size, num_textures, num_particles, active, isMouse));
}

void ParticleManager::CreateFire_Particle(fPoint position_static, SDL_Rect initial_rect, iPoint area, iPoint timelife, fPoint speed, P_Direction p_direction, int size, int num_particles, int num_textures, bool active)
{
	Group_Fire.add(new P_Fire(position_static, initial_rect, area, timelife, speed, p_direction, size, num_particles, num_textures, active));
}

//DELETE GROUPS -------------------------------------------------------------------------------------------------------------------------------------

bool ParticleManager::DeleteFollow_p(P_Follow* group)
{
	p2List_item<P_Follow*>* item = Group_Follow.start;
	while (item != NULL)
	{
		if (item->data == group)
		{
			Group_Follow.del(item);
		}
		item = item->next;
	}
	return true;
}

bool ParticleManager::DeleteFire_p(P_Fire* group)
{
	p2List_item<P_Fire*>* item = Group_Fire.start;
	while (item != NULL)
	{
		if (item->data == group)
		{
			Group_Fire.del(item);
		}
		item = item->next;
	}
	return true;
}

void ParticleManager::DeleteFireGroup()
{
	p2List_item<P_Fire*>* item = Group_Fire.start;
	while (item != NULL)
	{
		item->data->particle.Clear();
		item = item->next;
	}
	Group_Fire.clear();
}