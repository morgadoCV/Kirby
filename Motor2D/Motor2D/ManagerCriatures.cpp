#include "ManagerCriatures.h"
#include "j1App.h"
#include "p2Defs.h"
#include "p2Log.h"

ManagerCriatures::ManagerCriatures() : j1Module()
{
	name = "Criatures";
}

ManagerCriatures::~ManagerCriatures()
{

}

bool ManagerCriatures::Awake(pugi::xml_node & conf)
{
	CreatePlayer();
	CreateEnemyFly();
	CreateEnemyNormal();
	return true;
}

bool ManagerCriatures::Start()
{
	p2List_item<Criature*>* item = elements.start;
	while (item != NULL)
	{
		item->data->Start();
		item = item->next;
	}
	return true;
}

bool ManagerCriatures::PreUpdate()
{
	p2List_item<Criature*>* item = elements.start;
	while (item != NULL)
	{
		item->data->PreUpdate();
		item = item->next;
	}
	return true;
}

bool ManagerCriatures::Update(float dt)
{
	p2List_item<Criature*>* item = elements.start;
	while (item != NULL)
	{
		item->data->Update(dt);
		item = item->next;
	}
	return true;
}

bool ManagerCriatures::PostUpdate()
{
	p2List_item<Criature*>* item = elements.start;
	while (item != NULL)
	{
		item->data->PostUpdate();
		item = item->next;
	}
	return true;
}

void ManagerCriatures::CreatePlayer()
{
	player = new Player();
	player->Awake();
	elements.add(player);
	LOG("Player Created!");
}

void ManagerCriatures::CreateEnemyFly()
{
	EnemyFly* enemy_fly = new EnemyFly();
	enemy_fly->Awake();
	elements.add(enemy_fly);
	LOG("Enemy Fly Created!");
}

void ManagerCriatures::CreateEnemyNormal()
{
	EnemyNormal* enemy_normal = new EnemyNormal();
	enemy_normal->Awake();
	elements.add(enemy_normal);
	LOG("Enemy Normal Created!");
}

bool ManagerCriatures::Load(pugi::xml_node& node)
{
	p2List_item<Criature*>* item = elements.start;
	while (item != NULL)
	{
		item->data->Load(node);
		item = item->next;
	}
	return true;
}
bool ManagerCriatures::Save(pugi::xml_node& node) const
{
	p2List_item<Criature*>* item = elements.start;
	while (item != NULL)
	{
		item->data->Save(node);
		item = item->next;
	}
	return true;
}