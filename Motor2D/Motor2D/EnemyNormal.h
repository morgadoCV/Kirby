#pragma once
#include "j1Module.h"
#include "p2Point.h"
#include "Animation.h"
#include "Criature.h"
//#include "ParticleManager.h"
//#include "P_Follow.h"

#define AnimationSpeed4 0.15f
#define AnimationSpeedDead 0.019f

struct SDL_Texture;

class EnemyNormal : public Criature
{
public:
	EnemyNormal();
	virtual ~EnemyNormal();
	// Called before render is available
	bool Awake();
	// Called before the first frame
	bool Start();
	// Called before all Updates
	bool PreUpdate();
	// Called each loop iteration
	bool Update(float dt);
	void processPos();
	void processGravity();
	void ReturnToZero();
	void Draw();
	// Called before all Updates
	bool PostUpdate();
	//Save and Load functions
	bool Load(pugi::xml_node &);
	bool Save(pugi::xml_node&)const;
	int GetDirection() const;
	fPoint* Getposition() const;
	// Called before quitting
	bool CleanUp();

private:
	State state;
	Direction direction;
	SDL_Texture* graphics = nullptr;
	bool isMove = false;
	fPoint position;
	fPoint velocity;
	Animation* current_animation;
	Animation idle;
	Animation run_right;
	Animation run_left;
	Animation dead;

};