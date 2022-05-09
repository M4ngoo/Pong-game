#pragma once
#include "gameobj.h"
#include "config.h"
#include "random"

class Ball : public GameObj, public Collide
{
	float speed_x = 5.0f;
	float speed_y = 5.0f;
	int player_score = 0;
	int opponent_score = 0;
	float score_time, speed_time;
	float pos_x = CANVAS_WIDTH / 2, pos_y = CANVAS_HEIGHT / 2;
	float text_posx, text_posy;
	int rng_debuff = -1;
	int rng_debuff2 = -1;
	int rng_debuff3 = -1;
	std::string rng_case;
	bool flag = false;
	bool invisible_flag = false;
	bool draw_inv_flag = false;
	bool tiny_flag = false;
	bool reset_all_flag = false;
public:
	virtual void update() override;
	virtual void draw() override;
	virtual void init() override;
	virtual void reset();
	virtual void onCollision();
	virtual void increment_player_score();
	virtual void increment_opponent_score();
	virtual int getPlayerScore();
	virtual int getOpponentScore();
	virtual float getpos_x();
	virtual void resetScore();
	virtual float getTime();
	virtual float getSpeedTime();
	virtual void setTime(float time);
	virtual void setSpeedTime(float val);
	virtual void setRngDebuff(int debuff);
	virtual int getRngDebuff();
	virtual void rngGen();
	virtual void setInvisibleFlag(bool flag);
	virtual void getRng();
	virtual void setTiny(bool flag);
	virtual bool resetAll();
	virtual void setResetAll(bool flag);
	virtual void setTroubleDebuff(int debuff1, int debuff2);
	virtual int getRngDebuff2();
	virtual int getRngDebuff3();
	virtual void setDrawInvFlag(bool flag);
	virtual std::string rngCase(int rng);
	Rect getCollisionHull() const override;
};
