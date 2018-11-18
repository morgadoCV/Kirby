#include "Player.h"
#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Textures.h"
#include "j1FadeToBlack.h"
#include "j1Map.h"
#include "j1Scene.h"
#include "ManagerCriatures.h"


Player::Player() : Criature()
{

	name.create("player");
	type = Type::PLAYER;

	idle.PushBack({ 3,  5, 24, 21 });
	idle.PushBack({ 33, 5, 24, 21 });
	idle.PushBack({ 62, 5, 24, 21 });
	idle.PushBack({ 93, 5, 24, 21 });
	idle.speed = AnimationSpeed4;

	walk_right.PushBack({ 1,  35, 26, 21 });
	walk_right.PushBack({ 35, 35, 26, 21 });
	walk_right.PushBack({ 64, 35, 26, 21 });
	walk_right.PushBack({ 94, 35, 26, 21 });
	walk_right.speed = AnimationSpeed4;

	jump_right.PushBack({ 2, 66,  24, 21 });
	jump_right.PushBack({ 32, 66, 24, 21 });
	jump_right.PushBack({ 63, 66, 24, 21 });
	jump_right.speed = AnimationSpeed3;

	run_right.PushBack({ 3,  94, 23, 21 });
	run_right.PushBack({ 32, 94, 23, 21 });
	run_right.PushBack({ 62, 94, 23, 21 });
	run_right.PushBack({ 92, 94, 23, 21 });
	run_right.speed = AnimationSpeed4;

	fly_right.PushBack({ 0,  121,  30, 30 });
	fly_right.PushBack({ 30, 121, 30, 30 });
	fly_right.PushBack({ 60, 121, 30, 30 });
	fly_right.speed = AnimationSpeed3;

	//Left---------------------------------------

	walk_left.PushBack({ 4,  155, 23, 22 });
	walk_left.PushBack({ 31, 155, 23, 22 });
	walk_left.PushBack({ 63, 155, 23, 22 });
	walk_left.PushBack({ 91, 155, 23, 22 });
	walk_left.speed = AnimationSpeed4;

	jump_left.PushBack({ 5,  184, 23, 22 });
	jump_left.PushBack({ 35, 184, 24, 22 });
	jump_left.PushBack({ 65, 184, 24, 22 });
	jump_left.speed = AnimationSpeed3;

	run_left.PushBack({ 6,  215, 23, 21 });
	run_left.PushBack({ 34, 215, 23, 21 });
	run_left.PushBack({ 65, 215, 23, 21 });
	run_left.PushBack({ 94, 215, 23, 21 });
	run_left.speed = AnimationSpeed4;

	fly_left.PushBack({ 0,  240,  30, 30 });
	fly_left.PushBack({ 30, 240,  30, 30 });
	fly_left.PushBack({ 60, 240,  30, 30 });
	fly_left.speed = AnimationSpeed3;
	//Death--------------------------------------
	dead.PushBack({ 1,  274,  27, 26 });
	dead.PushBack({ 31, 274,  30, 30 });
	dead.PushBack({ 62, 274,  30, 30 });
	dead.speed = AnimationSpeedDead;

}

Player::~Player()
{
}

bool Player::Awake()
{
	position.create(85, 354);
	velocity.create(0, 0);
	//TODO SERGIO 2: Init start position
	actualvl = LVL_1;
	// Sprites
	return true;
}

bool Player::Start()
{
	graphics = App->tex->Load("textures/Kirby.png");
	current_animation = &idle;
	state = IDLE;
	App->Save();
	fade = false;
	collision_feet = App->collision->AddCollider({ (int)position.x, (int)position.y - 45, 45, 45 }, COLLIDER_PLAYER, this);
	return true;
}

bool Player::PreUpdate()
{
	return true;
}

bool Player::Update(float dt)
{
	

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		App->managerC->DeleteAllEnemies();
		StartFromFirstLvl();
	}
	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		App->managerC->DeleteAllEnemies();
		StartFromBeginCurrentLvl();
	}

	if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
	{
		GodMode = !GodMode;
	}

	if (state != DEAD && GoDead == false)
	{
		Input(dt);
	}

	processPos();
	processGravity(dt);

	if (GodMode == false)
	{

		if (App->map->CheckDead(position.x, position.y, current_animation->frames[0].w, current_animation->frames[0].h))
		{
			if (GoDead == false)
			{
				fade = false;
				GoDead = true;
				notRepeatDead = true;
				current_animation->SetZero();
				dead.SetZero();
				current_animation = &dead;
			}
		}
	}
	if (GoDead)
	{
		if (current_animation->FinishAnimation())
		{
			if (fade == false)
			{
				App->fade->FadeToBlack();
				fade = true;
				now_switch = true;
			}
		}

		if (App->fade->Checkfadetoblack() && now_switch)
		{
	
			now_switch = false;
			App->Load();
			if (actualvl != LVL_2)
			{
				App->render->camera.x = 0;
				App->render->camera.y = 0;
			}
			else
			{
				App->render->camera.x = 0;
				App->render->camera.y = App->win->GetHeight() - App->map->mapdata.height * App->map->mapdata.tile_height;
			}
		}
			

		if (state != DEAD && notRepeatDead)
		{
			App->audio->StopMusic();
			App->audio->PlayFx(3);
			state = DEAD;
			notRepeatDead = false;
		}
	}

	//Collision follows 
	collision_feet->SetPos(position.x, position.y - 23);

	return true;
}

void Player::ChangeLVL()
{
	if (actualvl == LVL_1)
	{
		App->managerC->DeleteAllEnemies();
		ChangeMap("LVL2.tmx");
		position.create(App->map->GetPositionStart().x, App->map->GetPositionStart().y);
		App->render->camera.x = 0;
		App->render->camera.y = App->win->GetHeight() - App->map->mapdata.height * App->map->mapdata.tile_height;
		actualvl = LVL_2;
		//App->Save();
	}
	else if (actualvl == LVL_2)
	{
		App->managerC->DeleteAllEnemies();
		ChangeMap("LVL3.tmx");
		position.create(App->map->GetPositionStart().x, App->map->GetPositionStart().y);
		App->render->camera.x = 0;
		App->render->camera.y = 0;
		actualvl = LVL_1;
		//App->Save();
	}
}

bool Player::PostUpdate()
{
	if (isFly == false && isMove && isInPlataform)
		particlePlayer->active = true;
	else
		particlePlayer->active = false;
	Draw();
	App->map->Draw(1);
	if (GodMode == false)
	{
		if (App->map->NextLvl(position.x, position.y, current_animation->frames[0].w, current_animation->frames[0].h))
		{
			ChangeLVL();
			App->managerC->newMap = true;
		}
	}

	return true;
}

bool Player::Load(pugi::xml_node &node)
{
	bool ret = true;
	state = IDLE;
	if (actualvl != node.child("Player").child("position").attribute("Actual_LVL").as_int())
	{
		if (LVL_1 != node.child("Player").child("position").attribute("Actual_LVL").as_int())
		{
			ChangeMap("LVL2.tmx");
			position.x = node.child("Player").child("position").attribute("x").as_int();
			position.y = node.child("Player").child("position").attribute("y").as_int();
			actualvl = LVL_2;
		}
		else
		{
			ChangeMap("LVL3.tmx");
			position.x = node.child("Player").child("position").attribute("x").as_int();
			position.y = node.child("Player").child("position").attribute("y").as_int();
			actualvl = LVL_1;
		}
	}
	else
	{
		position.x = node.child("Player").child("position").attribute("x").as_int();
		position.y = node.child("Player").child("position").attribute("y").as_int();
	}


	return ret;
}

bool Player::Save(pugi::xml_node &node)const
{
	bool ret = true;

	pugi::xml_node playerpos = node.append_child("Player").append_child("position");

	playerpos.append_attribute("x") = position.x;
	playerpos.append_attribute("y") = position.y;
	playerpos.append_attribute("Actual_LVL") = actualvl;

	return ret;
}

int Player::GetDirection()
{
	return direction;
}

bool Player::CanFollowPlayer()
{
	if (direction == LEFT)
	{
		if (position.x > App->win->GetWidth() / 2 && position.x + App->win->GetWidth() / 2  < App->map->mapdata.width * App->map->mapdata.tile_width)
		{
			return true;
		}
	}
	if (direction == RIGHT)
	{
		if (position.x > App->win->GetWidth() / 2 && position.x + App->win->GetWidth() / 2 < App->map->mapdata.width * App->map->mapdata.tile_width)
		{
			return true;
		}
	}
	return false;
}

void Player::FollowPlayer(float speed)
{
	if (direction == LEFT)
	{
		if (position.x > App->win->GetWidth() / 2 && position.x + App->win->GetWidth() / 2  < App->map->mapdata.width * App->map->mapdata.tile_width)
		{
			App->render->camera.x += speed;
		}
	}
	if (direction == RIGHT)
	{
		if (position.x > App->win->GetWidth() / 2 && position.x + App->win->GetWidth() / 2 < App->map->mapdata.width * App->map->mapdata.tile_width)
		{
			App->render->camera.x -= speed;
		}
	}
}

void Player::Input(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT &&
		App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
	{
		direction = LEFT;
		if (App->map->MovementCost(position.x - ceil(Velocity_X * dt), position.y, current_animation->frames[0].w, current_animation->frames[0].h, direction))
		{
			FollowPlayer(ceil(Velocity_X * dt));
			position.x -= ceil(Velocity_X * dt);
			isMove = true;
		}
		else
			isMove = false;
		if (!isFly)
			state = W_LEFT;
		else if (state == FLY_RIGHT)
			state = FLY_LEFT;
	}
	else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_UP)
	{
		direction = NON;
		isMove = false;
		if (!isFly)state = IDLE;
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_IDLE)
	{
		direction = LEFT;
		if (App->map->MovementCost(position.x - ceil(Velocity_X * 2 * dt), position.y, current_animation->frames[0].w, current_animation->frames[0].h, direction))
		{
			FollowPlayer(ceil(Velocity_X * 2 * dt));
			position.x -= ceil(Velocity_X * 2 * dt);
			isMove = true;
		}
		else
			isMove = false;
		if (!isFly)state = RUN_LEFT;
	}


	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
	{
		direction = RIGHT;
		if (App->map->MovementCost(position.x + ceil(Velocity_X * dt), position.y, current_animation->frames[0].w, current_animation->frames[0].h, direction))
		{
			FollowPlayer(ceil(Velocity_X * dt));
			position.x += ceil(Velocity_X * dt);
			isMove = true;
		}
		else
			isMove = false;
		if (!isFly)state = W_RIGHT;
		else if (state == FLY_LEFT)
			state = FLY_RIGHT;
	}
	else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_UP)
	{
		direction = NON;
		isMove = false;
		if (!isFly)state = IDLE;
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_IDLE)
	{
		direction = RIGHT;
		if (App->map->MovementCost(position.x + ceil(Velocity_X * 2 * dt), position.y, current_animation->frames[0].w, current_animation->frames[0].h, direction))
		{
			FollowPlayer(ceil(Velocity_X * 2 * dt));
			position.x += ceil(Velocity_X * 2 * dt);
			isMove = true;
		}
		else
			isMove = false;
		if (!isFly)state = RUN_RIGHT;
	}


	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		isInPlataform = false;
		if (isFly == false)
		{
			//JUMP!!!!
			if (state == W_LEFT || state == RUN_LEFT)
			{
				App->audio->PlayFx(1);
				state = JUMP_LEFT;
				velocity.y -= Velocity_Y;
				isFly = true;
			}
			if (state == W_RIGHT || state == RUN_RIGHT || state == IDLE)
			{
				App->audio->PlayFx(1);
				velocity.y -= Velocity_Y;
				state = JUMP_RIGHT;
				isFly = true;
			}
		}
		else
		{
			App->audio->PlayFx(2);
			if (state == FLY_LEFT || state == FLY_RIGHT)
			{
				isFly = false;
				state = IDLE;
			}
			else
			{
				if (direction == LEFT)
				{
					state = FLY_LEFT;
				}
				if (direction == RIGHT || direction == NON)
				{
					state = FLY_RIGHT;
				}
			}
		}

	}
	else if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		direction = NON;
	}
}



void Player::Setzero()
{
	velocity.x = 0;
	velocity.y = 0;
}

void Player::processPos()
{
	//position.x = position.x + velocity.x;   // Change position based on 
	position.y = position.y + velocity.y;   // current velocity components.
}

void Player::processGravity(float dt)
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
		apply_g = !apply_g;
		if (apply_g)
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

void Player::Draw()
{
	switch (state)
	{
	case IDLE:
	{
		current_animation = &idle;
		break;
	}
	case W_LEFT:
	{
		current_animation = &walk_left;
		break;
	}
	case W_RIGHT:
	{
		current_animation = &walk_right;
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
	case JUMP_LEFT:
	{
		current_animation = &jump_left;
		break;
	}
	case JUMP_RIGHT:
	{
		current_animation = &jump_right;
		break;
	}
	case FLY_LEFT:
	{
		current_animation = &fly_left;
		break;
	}
	case FLY_RIGHT:
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
	if (fade)
	{
		SDL_Rect r = current_animation->GetCurrentFrameSTOP();
		App->render->Blit(graphics, position.x / 2, position.y / 2 - 10, &r, 2);
	}
	else
	{
		SDL_Rect r = current_animation->GetCurrentFrame(App->GetDT());
		App->render->Blit(graphics, position.x / 2, position.y / 2 - 10, &r, 2);
	}

}

void Player::ChangeMap(const char* path)
{
	App->map->CleanUp();
	App->map->Load(path);
	Setzero();
}

void Player::StartFromFirstLvl()
{
	ChangeMap("LVL3.tmx");
	position.create(App->map->GetPositionStart().x, App->map->GetPositionStart().y);
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	actualvl = LVL_1;

}

void Player::StartFromBeginCurrentLvl()
{
	if (actualvl != LVL_1)
	{
		ChangeMap("LVL2.tmx");

		position.create(App->map->GetPositionStart().x, App->map->GetPositionStart().y);
		actualvl = LVL_2;
	}
	else if (actualvl != LVL_2)
	{
		ChangeMap("LVL3.tmx");
		position.create(App->map->GetPositionStart().x, App->map->GetPositionStart().y);
		actualvl = LVL_1;
	}
}

bool Player::CleanUp()
{
	return true;
}

iPoint Player::Getposition() const
{
	return position;
}
iPoint* Player::GetpositionPointer()
{
	return &position;
}

void Player::OnCollision(Collider* player, Collider* enemy)
{
	//LOG("HIT!");
	if (player != nullptr && enemy != nullptr)
	{
		if (enemy->callback->type == Criature::Type::FLY)
		{
			App->managerC->DeleteEnemyFly(enemy->callback);
		}
		else if (enemy->callback->type == Criature::Type::NORMAL)
		{
			App->managerC->DeleteEnemyNormal(enemy->callback);
		}
		LOG("Delete Enemy");
	}
}