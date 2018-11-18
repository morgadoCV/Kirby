#include <iostream> 
#include <sstream> 

#include "p2Defs.h"
#include "p2Log.h"

#include "j1Window.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Scene.h"
#include "j1App.h"
#include "Player.h"
#include "ParticleManager.h"
#include "j1FadeToBlack.h"
#include "j1Map.h"

// Constructor
j1App::j1App(int argc, char* args[]) : argc(argc), args(args)
{
	frames = 0;

	input = new j1Input();
	win = new j1Window();
	render = new j1Render();
	tex = new j1Textures();
	audio = new j1Audio();
	scene = new j1Scene();
	map = new j1Map();
	player = new Player();
	particles = new ParticleManager();
	fade = new j1FadeToBlack();

	// Ordered for awake / Start / Update
	// Reverse order of CleanUp
	AddModule(input);
	AddModule(win);
	AddModule(tex);
	AddModule(audio);
	AddModule(map);
	AddModule(scene);
	AddModule(player);
	AddModule(particles);
	AddModule(fade);

	// render last to swap buffer
	AddModule(render);
}

// Destructor
j1App::~j1App()
{
	// release modules
	p2List_item<j1Module*>* item = modules.end;

	while(item != NULL)
	{
		RELEASE(item->data);
		item = item->prev;
	}

	modules.clear();

	config_file.reset();
}

void j1App::AddModule(j1Module* module)
{
	module->Init();
	modules.add(module);
}

// Called before render is available
bool j1App::Awake()
{
	bool ret = LoadConfig();

	// self-config
	title.create(app_config.child("title").child_value());
	organization.create(app_config.child("organization").child_value());

	if(ret == true)
	{
		p2List_item<j1Module*>* item;
		item = modules.start;

		while(item != NULL && ret == true)
		{
			ret = item->data->Awake(config.child(item->data->name.GetString()));
			item = item->next;
		}
	}

	return ret;
}

// Called before the first frame
bool j1App::Start()
{
	bool ret = true;
	p2List_item<j1Module*>* item;
	item = modules.start;

	while(item != NULL && ret == true)
	{
		ret = item->data->Start();
		item = item->next;
	}
	capped_ms = 1000 / 60;
	startup_time.Start();
	return ret;
}

// Called each loop iteration
bool j1App::Update()
{
	bool ret = true;
	PrepareUpdate();

	if(input->GetWindowEvent(WE_QUIT) == true)
		ret = false;

	if(ret == true)
		ret = PreUpdate();

	if(ret == true)
		ret = DoUpdate();

	if(ret == true)
		ret = PostUpdate();

	FinishUpdate();
	return ret;
}


// ---------------------------------------------
bool j1App::LoadConfig()
{
	bool ret = true;

	pugi::xml_parse_result result = config_file.load_file("config.xml");

	if(result == NULL)
	{
		LOG("Could not load map xml file config.xml. pugi error: %s", result.description());
		ret = false;
	}
	else
	{
		config = config_file.child("config");
		app_config = config.child("app");
	}

	return ret;
}

// ---------------------------------------------
void j1App::PrepareUpdate()
{
	frame_count++;
	frame_time.Start();
}

// ---------------------------------------------
void j1App::FinishUpdate()
{
	
	if (need_load)
	{
		DocLoad();
		need_load = false;
	}
	if (need_save)
	{
		DocSave();
		need_save = false;
	}

	uint32 last_frame_ms = frame_time.Read();
	float avg_fps = float(frame_count) / startup_time.ReadSec();
	static char title[256];
	if (capped_ms > 0 && last_frame_ms < capped_ms)
	{
		SDL_Delay(capped_ms - last_frame_ms);
	}
	sprintf_s(title, 256, "Caped Av.FPS: %.2f", avg_fps);
	App->win->SetTitle(title);

}

// Call modules before each loop iteration
bool j1App::PreUpdate()
{
	bool ret = true;
	p2List_item<j1Module*>* item;
	item = modules.start;
	j1Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->active == false) {
			continue;
		}

		ret = item->data->PreUpdate();
	}

	return ret;
}

// Call modules on each loop iteration
bool j1App::DoUpdate()
{
	bool ret = true;
	p2List_item<j1Module*>* item;
	item = modules.start;
	j1Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->active == false) {
			continue;
		}

		ret = item->data->Update(dt);
	}

	return ret;
}

// Call modules after each loop iteration
bool j1App::PostUpdate()
{
	bool ret = true;
	p2List_item<j1Module*>* item;
	j1Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->active == false) {
			continue;
		}

		ret = item->data->PostUpdate();
	}

	return ret;
}

// Called before quitting
bool j1App::CleanUp()
{
	bool ret = true;
	p2List_item<j1Module*>* item;
	item = modules.end;

	while(item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}

	return ret;
}

// ---------------------------------------
int j1App::GetArgc() const
{
	return argc;
}

// ---------------------------------------
const char* j1App::GetArgv(int index) const
{
	if(index < argc)
		return args[index];
	else
		return NULL;
}

// ---------------------------------------
const char* j1App::GetTitle() const
{
	return title.GetString();
}

// ---------------------------------------
const char* j1App::GetOrganization() const
{
	return organization.GetString();
}

void j1App::Load()
{
	need_load = true;

}

void j1App::Save()const
{

	need_save = true;

}


bool j1App::DocLoad()
{
	bool ret = true;
	pugi::xml_document doc;
	pugi::xml_node node;
	pugi::xml_parse_result result = doc.load_file("savegame.xml");

	if (result == NULL)
		ret = false;
	else
	{

		node = doc.child("save");

		p2List_item<j1Module*>* item = modules.start;

		while (item != NULL && ret == true)
		{
			ret = item->data->Load(node.child(item->data->name.GetString()));
			item = item->next;
		}
		doc.reset();

		need_load = false;
		LOG("load complete, not existing errors");
		return ret;
	}

}

bool j1App::DocSave() const
{
	bool ret = true;
	pugi::xml_document doc;
	pugi::xml_node node;
	
		node = doc.append_child("save");

		p2List_item<j1Module*>* item = modules.start;

		while (item != NULL && ret == true)
		{
			ret = item->data->Save(node.append_child(item->data->name.GetString()));
			item = item->next;
		}

		if (ret == true)
		{
			doc.save_file("savegame.xml");
			LOG("... finished saving", );
		}
		
		doc.reset();
		need_save = false;
		return ret;

}

