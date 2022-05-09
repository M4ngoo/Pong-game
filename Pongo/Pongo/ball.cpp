#include "ball.h"
#include "graphics.h"
#include "random"
#include "iostream"
#include "ctime" 

void Ball::update()
{
	float time = graphics::getGlobalTime();
	if (time - getSpeedTime() >= 10000 && time - getSpeedTime() < 20000)
	{
		pos_x += speed_x * graphics::getDeltaTime() / 4.0f;
		pos_y += speed_y * graphics::getDeltaTime() / 4.0f;
	}
	else if (time - getSpeedTime() >= 20000)
	{
		pos_x += speed_x * graphics::getDeltaTime() / 3.0f;
		pos_y += speed_y * graphics::getDeltaTime() / 3.0f;
	}
	else
	{
		pos_x += speed_x * graphics::getDeltaTime() / 5.0f;
		pos_y += speed_y * graphics::getDeltaTime() / 5.0f;
	}

	if (pos_x >= CANVAS_WIDTH - 130)//123
	{
		speed_x *= -1;
	}

	if (pos_x <= 130)//123
	{
		speed_x *= -1;
	}

	if (pos_y <= 50 || pos_y >= CANVAS_HEIGHT - 50)
	{
		if (pos_y <= 50)
			increment_player_score();
		else
			increment_opponent_score();
		setTime(graphics::getGlobalTime());
		graphics::playSound(std::string(ASSET_PATH) + "goal.MP3", 0.5f);
		draw_inv_flag = false;
		setResetAll(true);
		getRng();
		reset();
	}

	if (getTime() != 0.0f)
	{
		reset();
	}

}

void Ball::draw()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "football.png";
	br.outline_opacity = 0.0f;

	if (invisible_flag)
	{
		if (draw_inv_flag)
			br.fill_opacity = 0.0f;
		else
			br.fill_opacity = 1.0f;
	}
	else
		br.fill_opacity = 1.0f;

	if (!tiny_flag)
	{
		graphics::drawRect(pos_x, pos_y, 60, 60, br);
	}
	else
	{
		graphics::drawRect(pos_x, pos_y, 20, 20, br);
	}
}

void Ball::init()
{
	srand(time(0));
	int a = rand() % 2;
	if (a == 0)
		a = -1;
	int b = rand() % 2;
	if (b == 0)
		b = -1;
	speed_x *= a;
	speed_y *= b;
}

Rect Ball::getCollisionHull() const
{
	Rect rect;
	rect.rx = pos_x;
	rect.ry = pos_y;
	if (!tiny_flag)
	{
		rect.width = BALL_WIDTH - 10;
		rect.height = BALL_HEIGHT - 10;
	}
	else
	{
		rect.width = 50 - 10;
		rect.height = 50 - 10;
	}
	return rect;
}

void Ball::onCollision()
{
	if (!invisible_flag)
	{
		speed_y *= -1;
	}
	else
	{
		speed_y *= -1;
		if (!draw_inv_flag)
			draw_inv_flag = true;
		else
			draw_inv_flag = false;
	}
}

void Ball::increment_player_score()
{
	player_score += 1;
}

void Ball::increment_opponent_score()
{
	opponent_score += 1;
}

int Ball::getPlayerScore()
{
	return player_score;
}

int Ball::getOpponentScore()
{
	return opponent_score;
}

void Ball::resetScore()
{
	player_score = 0;
	opponent_score = 0;
}

void Ball::reset() 
{	
	float current_time = graphics::getGlobalTime();
	pos_x = CANVAS_WIDTH / 2;
	pos_y = CANVAS_HEIGHT / 2;
	graphics::Brush br;
	char info[10];
	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.15f;
	
	if (flag)
	{
		graphics::drawText(text_posx, text_posy, 80, rng_case, br);
	}

	if (current_time - getTime() < 1000)
	{
		sprintf_s(info, "3");
		graphics::drawText(CANVAS_WIDTH / 2 - 25, CANVAS_HEIGHT / 2 - 230, 100, info, br);
	}

	if (1000 < current_time - getTime() && current_time - getTime() < 2000)
	{
		sprintf_s(info, "2");
		graphics::drawText(CANVAS_WIDTH / 2 - 25, CANVAS_HEIGHT / 2 - 230, 100, info, br);
	}

	if (2000 < current_time - getTime() && current_time - getTime() < 3000)
	{
		sprintf_s(info, "1");
		graphics::drawText(CANVAS_WIDTH / 2 - 25, CANVAS_HEIGHT / 2 - 230, 100, info, br);
	}
	

	if (current_time - getTime() < 3100)
	{
		speed_x = 0;
		speed_y = 0;
	}
	else
	{
		flag = true;
		speed_x = 5.0f;
		speed_y = 5.0f;
		setTime(0.0f);
		setSpeedTime(graphics::getGlobalTime());
		init();
	}
}

void Ball::setSpeedTime(float val)
{
	speed_time = val;
}

void Ball::setTime(float time)
{
	score_time = time;
}

float Ball::getTime()
{
	return score_time;
}

float Ball::getSpeedTime()
{
	return speed_time;
}

float Ball::getpos_x()
{
	return pos_x;
}

void Ball::setRngDebuff(int debuff)
{
	rng_debuff = debuff;
}

void Ball::setTroubleDebuff(int debuff1, int debuff2)
{
	rng_debuff2 = debuff1;
	rng_debuff3 = debuff2;
}

int Ball::getRngDebuff()
{
	return rng_debuff;
}

int Ball::getRngDebuff2()
{
	return rng_debuff2;
}

int Ball::getRngDebuff3()
{
	return rng_debuff3;
}

void Ball::rngGen()
{
	srand(time(0));
	int rng = rand() % 6;
	int rng_2 = -1;
	int rng_3 = -1;
	if (rng == 5)
	{
		while (true)
		{
			int rng_3 = rand() % 6;
			int rng_2 = rand() % 6;
			if (rng_3 != 5 && rng_2 != 5 && rng_3 != rng_2)
			{
				setTroubleDebuff(rng_2, rng_3);
				break;
			}
		}
	}
	setRngDebuff(rng);
}

void Ball::getRng()
{
	rngGen();
	rng_case = rngCase(getRngDebuff());
}

std::string Ball::rngCase(int rng)
{
	switch (rng)
	{
	case 0:
		text_posx = CANVAS_WIDTH / 2 - 465;
		text_posy = CANVAS_HEIGHT / 2 - 430;
		return "the ball disappears!";
	case 1:
		text_posx = CANVAS_WIDTH / 2 - 200;
		text_posy = CANVAS_HEIGHT / 2 - 430;
		return "tiny ball!";
	case 2:
		text_posx = CANVAS_WIDTH / 2 - 380;
		text_posy = CANVAS_HEIGHT / 2 - 430;
		return "smaller rackets!";
	case 3:
		text_posx = CANVAS_WIDTH / 2 - 200;
		text_posy = CANVAS_HEIGHT / 2 - 430;
		return "inversion!";
	case 4:
		text_posx = CANVAS_WIDTH / 2 - 405;
		text_posy = CANVAS_HEIGHT / 2 - 430;
		return "slower movement!";
	case 5:
		text_posx = CANVAS_WIDTH / 2 - 350;
		text_posy = CANVAS_HEIGHT / 2 - 430;
		return "double trouble!";
	}
}

void Ball::setInvisibleFlag(bool flag)
{
	invisible_flag = flag;
}

void Ball::setTiny(bool flag)
{
	tiny_flag = flag;
}

void Ball::setResetAll(bool flag)
{
	reset_all_flag = flag;
}

bool Ball::resetAll()
{
	if (reset_all_flag)
		return true;
	return false;
}

void Ball::setDrawInvFlag(bool flag)
{
	draw_inv_flag = flag;
}
