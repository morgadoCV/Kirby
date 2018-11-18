#include "EnemyNormal.h"

EnemyNormal::EnemyNormal()
{

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