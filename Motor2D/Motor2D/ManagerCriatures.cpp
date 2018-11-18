#include "ManagerCriatures.h"
#include "j1App.h"
#include "p2Defs.h"
#include "p2Log.h"
#include "j1Input.h"

ManagerCriatures::ManagerCriatures() : j1Module()
{
	name = "Criatures";
}

ManagerCriatures::~ManagerCriatures()
{
	p2List_item<Criature*>* item = elements.start;
	while (item != NULL)
	{
		item->data->~Criature();
		elements.del(item);
		item = item->next;
	}
	elements.clear();
}

bool ManagerCriatures::Awake(pugi::xml_node& conf)
{
	CreatePlayer();
	return true;
}

bool ManagerCriatures::Start()
{
	p2List_item<Criature*>* item = elements.start;
	while (item != NULL)
	{
		if (item->data->type == Criature::Type::PLAYER)
		{
			item->data->Start();
		}
		item = item->next;
	}
	return true;
}

bool ManagerCriatures::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdate", Profiler::Color::Red);
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
	BROFILER_CATEGORY("Update", Profiler::Color::Blue);
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
	BROFILER_CATEGORY("PostUpdate", Profiler::Color::Green);
	p2List_item<Criature*>* item = elements.start;
	while (item != NULL)
	{
		item->data->PostUpdate();
		if (newMap)
		{
			newMap = false;
			break;
		}
		item = item->next;
	}
	return true;
}

void ManagerCriatures::CreatePlayer()
{
	BROFILER_CATEGORY("CreatePlayer", Profiler::Color::Black);
	player = new Player();
	player->Awake();
	elements.add(player);
	LOG("Player Created!");
}

void ManagerCriatures::CreateEnemyFly(iPoint position)
{
	BROFILER_CATEGORY("CreateEnemyFly", Profiler::Color::Black);
	EnemyFly* enemy_fly = new EnemyFly();
	enemy_fly->Awake();
	enemy_fly->Start();
	enemy_fly->position = position;
	elements.add(enemy_fly);
	LOG("Enemy Fly Created!");
}

void ManagerCriatures::CreateEnemyNormal(iPoint position)
{
	BROFILER_CATEGORY("CreateEnemyNormal", Profiler::Color::Black);
	EnemyNormal* enemy_normal = new EnemyNormal();
	enemy_normal->Awake();
	enemy_normal->Start();
	enemy_normal->position = position;
	elements.add(enemy_normal);
	LOG("Enemy Normal Created!");
}

void ManagerCriatures::DeleteEnemyFly(Criature* enemyFly)
{
	int i = elements.find(enemyFly);
	int ds = 0;
	p2List_item<Criature*>* item = elements.start;
	while (item != NULL)
	{
		if (i == ds)
		{
			item->data->~Criature();
			elements.del(item);
			return;
		}
		ds++;
		item = item->next;
	}
}

void ManagerCriatures::DeleteAllEnemies()
{
	p2List_item<Criature*>* item = elements.start;
	while (item != NULL)
	{
		if (item->data->type != Criature::Type::PLAYER)
		{
			item->data->~Criature();
			elements.del(item);
		}
		item = item->next;
	}
}

void ManagerCriatures::DeleteEnemyNormal(Criature* enemy_normal)
{
	int i = elements.find(enemy_normal);
	int ds = 0;
	p2List_item<Criature*>* item = elements.start;
	while (item != NULL)
	{
		if (i == ds)
		{
			item->data->~Criature();
			elements.del(item);
			return;
		}
		ds++;
		item = item->next;
	}
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