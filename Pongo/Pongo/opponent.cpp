#include "opponent.h"
#include "graphics.h"
#include "config.h"
#include "iostream"

void Opponent::update()
{
	if (!inversion_flag && !slow_flag)
	{
		if (graphics::getKeyState(graphics::SCANCODE_LEFT))
		{
			pos_x -= speed * graphics::getDeltaTime() / 10.0f;
		}

		if (graphics::getKeyState(graphics::SCANCODE_RIGHT))
		{
			pos_x += speed * graphics::getDeltaTime() / 10.0f;
		}
	}
	else if (inversion_flag && slow_flag)
	{
		if (graphics::getKeyState(graphics::SCANCODE_RIGHT))
		{
			pos_x -= speed * graphics::getDeltaTime() / 15.0f;
		}

		if (graphics::getKeyState(graphics::SCANCODE_LEFT))
		{
			pos_x += speed * graphics::getDeltaTime() / 15.0f;
		}
	}
	else
	{
		if (slow_flag)
		{
			if (graphics::getKeyState(graphics::SCANCODE_LEFT))
			{
				pos_x -= speed * graphics::getDeltaTime() / 15.0f;
			}

			if (graphics::getKeyState(graphics::SCANCODE_RIGHT))
			{
				pos_x += speed * graphics::getDeltaTime() / 15.0f;
			}
		}
		else
		{
			if (graphics::getKeyState(graphics::SCANCODE_RIGHT))
			{
				pos_x -= speed * graphics::getDeltaTime() / 10.0f;
			}

			if (graphics::getKeyState(graphics::SCANCODE_LEFT))
			{
				pos_x += speed * graphics::getDeltaTime() / 10.0f;
			}
		}
	}

	if (!small_flag)
	{
		if (pos_x >= CANVAS_WIDTH - 230)
		{
			pos_x = CANVAS_WIDTH - 230;
		}

		if (pos_x <= 233)
		{
			pos_x = 233;
		}
	}
	else 
	{
		if (pos_x >= CANVAS_WIDTH - 193)
		{
			pos_x = CANVAS_WIDTH - 193;
		}

		if (pos_x <= 193)
		{
			pos_x = 193;
		}
	}
}

void Opponent::ai_update(float ball_pos)
{
	if (!slow_flag)
	{
		if (pos_x >= ball_pos)
		{
			pos_x -= speed * graphics::getDeltaTime() / 18.0f;
		}

		if (pos_x <= ball_pos)
		{
			pos_x += speed * graphics::getDeltaTime() / 18.0f;
		}
	}
	else
	{
		if (pos_x >= ball_pos)
		{
			pos_x -= speed * graphics::getDeltaTime() / 22.0f;
		}

		if (pos_x <= ball_pos)
		{
			pos_x += speed * graphics::getDeltaTime() / 22.0f;
		}
	}

	if (!small_flag)
	{
		if (pos_x >= CANVAS_WIDTH - 230)
		{
			pos_x = CANVAS_WIDTH - 230;
		}

		if (pos_x <= 233)
		{
			pos_x = 233;
		}
	}
	else
	{
		if (pos_x >= CANVAS_WIDTH - 193)
		{
			pos_x = CANVAS_WIDTH - 193;
		}

		if (pos_x <= 193)
		{
			pos_x = 193;
		}
	}
}

void Opponent::draw()
{
	//float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime()/100);

	graphics::Brush br;
	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f; //+ glow * 0.5f;
	br.fill_color[2] = 1.0f;
	br.fill_opacity = 1.0f;
	br.gradient = true;
	br.outline_opacity = 0.0f;
	br.gradient_dir_u = 0.0f;
	br.gradient_dir_v = 0.7f;
	if (!small_flag)
		graphics::drawRect(pos_x, pos_y, PLAYER_WIDTH, PLAYER_HEIGHT, br);
	else
		graphics::drawRect(pos_x, pos_y, PLAYER_WIDTH - 80, PLAYER_HEIGHT, br);
}

Rect Opponent::getCollisionHull() const
{
	Rect rect;
	rect.rx = pos_x;
	rect.ry = pos_y;
	if (!small_flag)
		rect.width = PLAYER_WIDTH;
	else
		rect.width = PLAYER_WIDTH - 80;
	rect.height = PLAYER_HEIGHT;
	return rect;
}

void Opponent::setInversionFlag(bool flag)
{
	inversion_flag = flag;
}

void Opponent::setSlowFlag(bool flag)
{
	slow_flag = flag;
}

void Opponent::setSmall(bool flag)
{
	small_flag = flag;
}

void Opponent::init()
{
}