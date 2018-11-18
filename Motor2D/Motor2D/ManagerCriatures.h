#pragma once
#include "j1Module.h"
#include "p2List.h"
#include "EnemyFly.h"
#include "EnemyNormal.h"
#include "Player.h"
#include "Criature.h"


class ManagerCriatures : public j1Module
{
public:
	ManagerCriatures();
	virtual ~ManagerCriatures();
	// Called before render is available
	bool Awake(pugi::xml_node& conf);
	// Called before the first frame
	bool Start();
	// Called before all Updates
	bool PreUpdate();
	// Called each loop iteration
	bool Update(float dt);
	// Called before all Updates
	bool PostUpdate();
	void CreatePlayer();
	void CreateEnemyFly();
	void CreateEnemyNormal();
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&)const;

public:
	p2List<Criature*> elements;
	Player* player = nullptr;
	//EnemyFly* enfly = nullptr;
	//EnemyNormal* ennormal = nullptr;
	//p2List<EnemyFly> enFly;
	//p2List<EnemyNormal> enNormal;
};