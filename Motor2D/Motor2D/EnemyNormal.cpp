#include "EnemyNormal.h"

EnemyNormal::EnemyNormal()
{
	name.create("enemynormal");
	idle.PushBack({ 12,  16, 28, 30 });
	idle.PushBack({ 73,  18, 29, 29 });
	idle.PushBack({ 134, 15, 31, 28 });
	idle.PushBack({ 192, 16, 29, 29 });
	idle.PushBack({ 254, 16, 28, 30 });
	idle.PushBack({ 314, 16, 28, 30 });
	idle.speed = AnimationSpeed4;
	//Left---------------------------------------
	run_rignt.PushBack({ 16, 72, 26, 30 });
	run_rignt.PushBack({ 71, 74, 29, 27 });
	run_rignt.PushBack({ 133,74, 31, 25 });
	run_rignt.PushBack({ 133,74, 27, 28 });
	run_rignt.PushBack({ 195,71, 27, 29 });
	run_rignt.PushBack({ 254,74, 25, 30 });
	run_rignt.PushBack({ 314,71, 27, 29 });
	run_rignt.PushBack({ 375,70, 25, 30 });
	run_rignt.speed = AnimationSpeed4;
	run_rignt.PushBack({ 16, 194, 26, 30 });
	run_rignt.PushBack({ 78, 196, 29, 27 });
	run_rignt.PushBack({ 134,196, 31, 25 });
	run_rignt.PushBack({ 199,193, 27, 28 });
	run_rignt.PushBack({ 199,194, 27, 29 });
	run_rignt.PushBack({ 257,196, 25, 30 });
	run_rignt.PushBack({ 317,193, 27, 29 });
	run_rignt.PushBack({ 378,192, 25, 30 });
	run_left.speed = AnimationSpeed4;
	//Death--------------------------------------
	dead.PushBack({ 13, 131, 22, 30 });
	dead.PushBack({ 73, 133, 28, 28 });
	dead.PushBack({ 135,140, 29, 22 });
	dead.PushBack({ 196,141, 28, 20 });
	dead.speed = AnimationSpeedDead;
}

EnemyNormal::~EnemyNormal()
{

}

bool EnemyNormal::Awake(pugi::xml_node & conf)
{
	return false;
}

bool EnemyNormal::Start()
{
	return false;
}

bool EnemyNormal::PreUpdate()
{
	return false;
}

bool EnemyNormal::Update(float dt)
{
	return false;
}

void EnemyNormal::processPos()
{

}

void EnemyNormal::processGravity()
{

}

void EnemyNormal::ReturnToZero()
{

}

void EnemyNormal::Draw()
{

}

bool EnemyNormal::PostUpdate()
{
	return false;
}

bool EnemyNormal::Load(pugi::xml_node &)
{
	return false;
}

bool EnemyNormal::Save(pugi::xml_node &) const
{
	return false;
}

int EnemyNormal::GetDirection() const
{
	return 0;
}

fPoint* EnemyNormal::Getposition() const
{
	return nullptr;
}

bool EnemyNormal::CleanUp()
{
	return false;
}