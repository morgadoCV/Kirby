#include "EnemyFly.h"

EnemyFly::EnemyFly()
{
	name.create("enemyfly");
	idle.PushBack({ 10,  14, 30, 29 });
	idle.PushBack({ 73,  14, 32, 31 });
	idle.PushBack({ 134, 11, 32, 32 });
	idle.speed = AnimationSpeed4;
	idle_left.PushBack({ 13,193, 30, 29 });
	idle_left.PushBack({ 75,192, 32, 28 });
	idle_left.PushBack({ 151,192, 32,31 });
	idle_left.speed = AnimationSpeed4;
	//Left---------------------------------------
	fly_rignt.PushBack({ 9,  63, 36, 48 });
	fly_rignt.PushBack({ 70, 64, 36, 46 });
	fly_rignt.PushBack({ 127,66, 39, 32 });
	fly_rignt.PushBack({ 190,75, 39, 32 });
	fly_rignt.PushBack({ 251,76, 37, 30 });
	fly_rignt.speed = AnimationSpeed4;
	fly_left.PushBack({ 13, 245, 36, 48 });
	fly_left.PushBack({ 72, 245, 36, 46 });
	fly_left.PushBack({ 129,244, 39, 32 });
	fly_left.PushBack({ 190,251, 39, 32 });
	fly_left.PushBack({ 250,252, 37, 30 });
	fly_left.speed = AnimationSpeed4;

	//Death--------------------------------------
	dead.PushBack({ 12, 132, 31, 29 });
	dead.PushBack({ 72, 132, 31, 31 });
	dead.PushBack({ 132,132, 32, 31 });
	dead.PushBack({ 194,133, 26, 32 });
	dead.PushBack({ 254,136, 32, 29 });
	dead.PushBack({ 318,139, 32, 23 });
	dead.speed = AnimationSpeedDead;
}

EnemyFly::~EnemyFly()
{

}

bool EnemyFly::Awake(pugi::xml_node & conf)
{
	return false;
}

bool EnemyFly::Start()
{
	return false;
}

bool EnemyFly::PreUpdate()
{
	return false;
}

bool EnemyFly::Update(float dt)
{
	return false;
}

void EnemyFly::processPos()
{

}

void EnemyFly::processGravity()
{

}

void EnemyFly::ReturnToZero()
{

}

void EnemyFly::Draw()
{

}

bool EnemyFly::PostUpdate()
{
	return false;
}

bool EnemyFly::Load(pugi::xml_node &)
{
	return false;
}

bool EnemyFly::Save(pugi::xml_node &) const
{
	return false;
}

int EnemyFly::GetDirection() const
{
	return 0;
}

fPoint * EnemyFly::Getposition() const
{
	return nullptr;
}

bool EnemyFly::CleanUp()
{
	return false;
}