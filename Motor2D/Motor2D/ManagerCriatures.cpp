#include "ManagerCriatures.h"
#include "j1App.h"
#include "p2Defs.h"

ManagerCriatures::ManagerCriatures() : j1Module()
{
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
}
void ManagerCriatures::CreateEnemyFly()
{
	EnemyFly* enemy_fly = new EnemyFly();
	enemy_fly->Awake();
	elements.add(enemy_fly);
}
void ManagerCriatures::CreateEnemyNormal()
{
	EnemyNormal* enemy_normal = new EnemyNormal();
	enemy_normal->Awake();
	elements.add(enemy_normal);
}