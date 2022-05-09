#pragma once
#include "gameobj.h"
#include "config.h"

class Player : public GameObj, public Collide
{
	float speed = 8.0f;
	float pos_x = CANVAS_WIDTH /2 , pos_y = CANVAS_HEIGHT - 75;
	bool inversion_flag = false, slow_flag = false, small_flag = false;
public:
	virtual void update() override;
	virtual void draw() override;
	virtual void init() override;
	virtual void setInversionFlag(bool flag);
	virtual void setSlowFlag(bool flag);
	virtual void setSmall(bool flag);
	Rect getCollisionHull() const override;
};