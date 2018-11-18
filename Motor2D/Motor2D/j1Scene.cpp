#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Scene.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	App->audio->PlayMusic("audio/music/Music_LVL1.ogg");
	App->audio->LoadFx("audio/fx/jump.wav"); //Fx---->1
	App->audio->LoadFx("audio/fx/float.wav"); //Fx----->2
	App->audio->LoadFx("audio/fx/dead.wav"); //Fx----->3
	App->map->Load("LVL3.tmx");
	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	// TODO 5: Call load / save methods when pressing l/s

	//if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	//	App->render->camera.y -= 10;

	//if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	//	App->render->camera.y += 10;

	//if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	//	App->render->camera.x -= 10;

	//if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	//	App->render->camera.x += 10;

	if (App->input->GetKey(SDL_SCANCODE_KP_PLUS) == KEY_DOWN)
	{
		App->audio->volume += 10;
		App->audio->Changevolume(App->audio->volume);
	}


	if (App->input->GetKey(SDL_SCANCODE_KP_MINUS) == KEY_DOWN)
	{
		App->audio->volume -= 10;
		App->audio->Changevolume(App->audio->volume);
	}

	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		App->Load();

	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		App->Save();



	p2SString title("Map:%dx%d Tiles : %dx%d Tilesets : %d", App->map->mapdata.width, App->map->mapdata.height, App->map->mapdata.tile_width, App->map->mapdata.tile_height, App->map->mapdata.tilesets.count());


	//App->map->Draw();
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;
	App->map->Draw(-1);
	App->map->Draw(0);

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
