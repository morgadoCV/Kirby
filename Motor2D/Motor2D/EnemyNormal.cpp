#include "EnemyNormal.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Textures.h"
#include "Player.h"
#include "ManagerCriatures.h"
#include "j1Map.h"
#include "j1Astar.h"

EnemyNormal::EnemyNormal() : Criature()
{
	name.create("enemynormal");
	type = Type::NORMAL;

	idle.PushBack({ 12,  16, 28, 30 });
	idle.PushBack({ 73,  19, 29, 29 });
	idle.PushBack({ 134, 19, 32, 28 });
	idle.PushBack({ 192, 19, 31, 28 });
	idle.PushBack({ 254, 18, 29, 29 });
	idle.PushBack({ 314, 17, 28, 30 });
	idle.speed = AnimationSpeed4;
	//Left---------------------------------------
	run_left.PushBack({ 16, 72, 24, 30 });
	run_left.PushBack({ 71, 74, 27, 28 });
	run_left.PushBack({ 134,73, 27, 29 });
	run_left.speed = AnimationSpeed4;
	//Right--------------------------------------
	run_right.PushBack({ 16, 194, 24, 30 });
	run_right.PushBack({ 78, 196, 27, 28 });
	run_right.PushBack({ 134,196, 27, 30 });
	run_right.speed = AnimationSpeed4;
	//Death--------------------------------------
	dead.PushBack({ 14, 194, 22, 30 });
	dead.PushBack({ 74, 196, 28, 28 });
	dead.PushBack({ 134,194, 29, 22 });
	dead.speed = AnimationSpeedDead;
}

EnemyNormal::~EnemyNormal()
{
	current_animation = nullptr;
	delete astar;
	App->tex->UnLoad(graphics);
	collision_feet->to_delete = true;
	graphics = nullptr;
}

bool EnemyNormal::Awake()
{
	velocity.create(0, 0);
	return true;
}

bool EnemyNormal::Start()
{
	graphics = App->tex->Load("textures/Snow_Man.png");
	current_animation = &idle;
	state = IDLE;
	astar = new j1Astar();
	PlayerLastPos = App->managerC->player->Getposition();
	path = astar->GenerateAstar(position, App->managerC->player->Getposition());
	collision_feet = App->collision->AddCollider({ (int)position.x, (int)position.y, 50, 50 }, COLLIDER_ENEMY_NORMAL, this);
	return true;
}

bool EnemyNormal::PreUpdate()
{
	return true;
}

bool EnemyNormal::Update(float dt)
{

	if (PlayerLastPos.DistanceTo(App->managerC->player->Getposition()) > 10)
	{
		path = astar->GenerateAstar(position, App->managerC->player->Getposition());
		PlayerLastPos = App->managerC->player->Getposition();
	}

	MoveEnemy(dt);
	processPos();
	processGravity(dt);

	//Collision follows
	if (collision_feet != nullptr)
	{
		collision_feet->SetPos(position.x, position.y - 25);
	}

	return true;
}

void EnemyNormal::MoveEnemy(float dt)
{
	if (App->managerC->player->Getposition().DistanceTo(position) < 250)
	{
		iPoint temp = *path->At(path->Count() - 1);
		int distancetoMove = temp.x - position.x;
		if (distancetoMove < 0)
		{
			position.x -= ceil(-distancetoMove * dt);
		}
		else
		{
			position.x += ceil(distancetoMove * dt);
		}
		if (position.DistanceTo(temp) < 5)
		{
			iPoint popiPoint;
			path->Pop(popiPoint);
		}
	}
	else
	{
		//LOG("NO!");
	}
}

void EnemyNormal::processPos()
{
	position.y = position.y + velocity.y;   // current velocity components.
}

void EnemyNormal::processGravity(float dt)
{
	if (velocity.y < 0)
	{
		if (App->map->MovementCost(position.x, position.y - OFFSET_Y, current_animation->frames[0].w, current_animation->frames[0].h, UP) == false && isFly)
		{
			velocity.y = 0;
			isInPlataform = true;
		}
	}
	if (App->map->MovementCost(position.x, position.y, current_animation->frames[0].w, current_animation->frames[0].h, DOWN) && state != FLY_LEFT && state != FLY_RIGHT)
	{
		velocity.y += ceil(Gravity * dt);
	}
	else if (isFly == false)
	{
		if (App->map->MovementCost(position.x, position.y + OFFSET_Y, current_animation->frames[0].w, current_animation->frames[0].h, DOWN) == false)
		{
			isInPlataform = true;
		}
		velocity.y = 0;
	}
	else
	{
		if (App->map->MovementCost(position.x, position.y, current_animation->frames[0].w, current_animation->frames[0].h, DOWN) == false)
		{
			isFly = false;
			velocity.y = 0;
			state = IDLE;
		}
		else
		{
			velocity.y = ceil(Gravity_LOW * dt);
		}
	}
}

void EnemyNormal::Draw()
{
	switch (state)
	{
	case IDLE:
	{
		current_animation = &idle;
		break;
	}
	case RUN_LEFT:
	{
		current_animation = &run_left;
		break;
	}
	case RUN_RIGHT:
	{
		current_animation = &run_right;
		break;
	}
	case DEAD:
	{
		current_animation = &dead;
		break;
	}
	}
	SDL_Rect r = current_animation->GetCurrentFrame(App->GetDT());
	App->render->Blit(graphics, position.x / 2, position.y / 2 - 10, &r, 2);
	Uint8 alpha = 80;
	if (path != nullptr && App->collision->debug)
	{
		for (int i = 0; i < path->Count(); i++)
		{
			iPoint temp = *path->At(i);
			SDL_Rect t = { temp.x,temp.y,10,10 };
			App->render->DrawQuad(t, 255, 255, 255, alpha);
		}
	}
	
}


bool EnemyNormal::PostUpdate()
{
	Draw();
	return true;
}

bool EnemyNormal::Load(pugi::xml_node &)
{
	return true;
}

bool EnemyNormal::Save(pugi::xml_node &) const
{
	return true;
}

int EnemyNormal::GetDirection() const
{
	return 0;
}

iPoint EnemyNormal::Getposition() const
{
	return position;
}

bool EnemyNormal::CleanUp()
{
	return true;
}