#include "EnemyFly.h"
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


EnemyFly::EnemyFly() : Criature()
{
	name.create("enemyfly");
	type = Type::FLY;

	idle.PushBack({ 10,  14, 30, 29 });
	idle.PushBack({ 73,  14, 32, 31 });
	idle.PushBack({ 134, 11, 32, 32 });
	idle.speed = AnimationSpeed3;
	idle_left.PushBack({ 13,193, 30, 29 });
	idle_left.PushBack({ 75,192, 32, 28 });
	idle_left.PushBack({ 151,192, 32,31 });
	idle_left.speed = AnimationSpeed4;
	//Left---------------------------------------
	fly_right.PushBack({ 10,  14, 30, 29 });
	fly_right.PushBack({ 73,  14, 32, 31 });
	fly_right.PushBack({ 134, 11, 32, 32 });
	fly_right.speed = AnimationSpeed4;

	//Right--------------------------------------
	fly_left.PushBack({ 13,193, 30, 29 });
	fly_left.PushBack({ 75,192, 32, 28 });
	fly_left.PushBack({ 151,192, 32,31 });
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
	current_animation = nullptr;
	delete astar;;
	App->tex->UnLoad(graphics);
	collision_feet->to_delete = true;
	graphics = nullptr;
}

bool EnemyFly::Awake()
{
	velocity.create(0, 0);
	return true;
}

bool EnemyFly::Start()
{
	graphics = App->tex->Load("textures/Fly_enemy.png");
	current_animation = &idle;
	state = IDLE;
	astar = new j1Astar();
	PlayerLastPos = App->managerC->player->Getposition();
	path = astar->GenerateAstar(position, App->managerC->player->Getposition());
	collision_feet = App->collision->AddCollider({ position.x, position.y, 64, 64 }, COLLIDER_ENEMY_FLY, this);
	return true;
}

bool EnemyFly::PreUpdate()
{
	return true;
}

bool EnemyFly::Update(float dt)
{
	if (PlayerLastPos.DistanceTo(App->managerC->player->Getposition()) > 10)
	{
		path = astar->GenerateAstar(position, App->managerC->player->Getposition());
		PlayerLastPos = App->managerC->player->Getposition();
	}
	MoveEnemy(dt);
	processPos();

	//Collider follows 
	if (collision_feet != nullptr)
	{
		collision_feet->SetPos(position.x, position.y - 32);
	}

	return true;
}

void EnemyFly::MoveEnemy(float dt)
{
	if (App->managerC->player->Getposition().DistanceTo(position) < 350)
	{
		iPoint temp = *path->At(path->Count() - 1);
		int moveX = temp.x - position.x;
		if (moveX < 0)
		{
			position.x -= ceil(-moveX * dt);
		}
		else
		{
			position.x += ceil(moveX * dt);
		}
		int moveY = temp.y - position.y;
		if (moveY < 0)
		{
			position.y -= ceil(-moveY * dt);
		}
		else
		{
			position.y += ceil(moveY * dt);
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

void EnemyFly::processPos()
{
	position.y = position.y + velocity.y;   // current velocity components.
}

void EnemyFly::processGravity()
{

}

void EnemyFly::ReturnToZero()
{

}

void EnemyFly::Draw()
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
		current_animation = &fly_left;
		break;
	}
	case RUN_RIGHT:
	{
		current_animation = &fly_right;
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

bool EnemyFly::PostUpdate()
{
	Draw();
	return true;
}

bool EnemyFly::Load(pugi::xml_node &)
{
	return true;
}

bool EnemyFly::Save(pugi::xml_node &) const
{
	return false;
}

int EnemyFly::GetDirection() const
{
	return 0;
}

iPoint EnemyFly::Getposition() const
{
	return position;
}

bool EnemyFly::CleanUp()
{
	return true;
}