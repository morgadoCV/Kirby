#pragma once
#include "j1Module.h"
#include "p2Point.h"
#include "Animation.h"
#include "Criature.h"
#include "p2DynArray.h"


struct	SDL_Texture;
class	j1Astar;

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
	void MoveEnemy(float dt);
	void processPos();
	void processGravity(float dt);
	void Draw();
	// Called before all Updates
	bool PostUpdate();
	//Save and Load functions
	bool Load(pugi::xml_node &);
	bool Save(pugi::xml_node&)const;
	int GetDirection() const;
	iPoint Getposition() const;
	// Called before quitting
	bool CleanUp();
	iPoint			position;

private:

	Direction		direction;
	SDL_Texture*	graphics = nullptr;
	bool			isMove = false;
	fPoint			velocity;
	Animation* current_animation = new Animation();
	p2DynArray<iPoint>* path;
	j1Astar*		astar = nullptr;
	iPoint			PlayerLastPos;
	Animation		idle;
	Animation		run_right;
	Animation		run_left;
	Animation		dead;

};