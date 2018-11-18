#include "EnemyFly.h"

EnemyFly::EnemyFly()
{

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