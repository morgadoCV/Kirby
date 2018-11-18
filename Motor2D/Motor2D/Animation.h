#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SDL/include/SDL_rect.h"
#define MAX_FRAMES 25

class Animation
{
public:
	float speed = 1.0f;
	SDL_Rect frames[MAX_FRAMES];

private:
	float current_frame;
	int last_frame = 0;

public:

	~Animation()
	{

	}

	void PushBack(const SDL_Rect& rect)
	{
		frames[last_frame++] = rect;
	}

	SDL_Rect& GetCurrentFrame(float dt)
	{
		current_frame += (speed * dt);
		if(current_frame >= last_frame)
			current_frame = 0;

		return frames[(int)current_frame];
	}

	SDL_Rect& GetCurrentFrameSTOP()
	{
		return frames[(int)current_frame];
	}

	void SetZero()
	{
		current_frame = 0;
	}

	bool FinishAnimation()
	{
		if (current_frame >= last_frame - 0.5f)
		{
			current_frame = 0;
			return true;
		}
		return false;
	}
};

#endif