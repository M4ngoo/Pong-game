#include "game.h"
#include "graphics.h"
#include "config.h"
#include "string"
#include "sstream"
#include "iostream"
#include "ctime"
#include "random"

void Game::update()
{
	if (!music_flag)
		graphics::playMusic(std::string(ASSET_PATH) + "bg-music.MP3", 0.1f);
		music_flag = true;
	if (!game_flag)
		updateStartScreen();
	else if (game_end_flag)
		updateEndScreen();
	else
		updateGame();
}

void Game::draw()
{
	if (!game_flag)
		drawStartScreen();
	else if (game_end_flag)
		drawEndScreen();
	else
		drawGame();
}

void Game::drawGame()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "bg.png";
	br.outline_opacity = 0.0f;

	//float offset = CANVAS_HEIGHT * sinf(graphics::getGlobalTime()/1000.0f) / 4;

	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	graphics::Brush splr1;
	graphics::Brush splr2;

	if (ball)
	{
		int player_score = ball->getPlayerScore();
		int opponent_score = ball->getOpponentScore();

		if (player_score == 10)
		{
			game_end_flag = true;
		}
	
		std::stringstream ss;
		ss << player_score;
		std::string str1 = ss.str();
		splr1.fill_color[0] = 1.0f;
		splr1.fill_color[1] = 0.0f;
		splr1.fill_color[2] = 0.0f;
		graphics::drawText(CANVAS_WIDTH / 2 - 590, CANVAS_HEIGHT / 2 + 35, 100, str1, splr1);
		
		if (opponent_score == 10)
		{
			game_end_flag = true;
		}
		std::stringstream sss;
		sss << opponent_score;
		std::string str2 = sss.str();
		splr2.fill_color[0] = 0.0f;
		splr2.fill_color[1] = 0.0f;
		splr2.fill_color[2] = 1.0f;
		graphics::drawText(CANVAS_WIDTH / 2 + 530, CANVAS_HEIGHT / 2 + 35, 100, str2, splr2);
	}

	if (player)
		player->draw();
	if (opponent)
		opponent->draw();
	if (ball)
		ball->draw();
	if (checkCollision())
		ball->onCollision();
}

void Game::drawStartScreen()
{		
	drawHelp();

	graphics::Brush br;
	char info[40];
	sprintf_s(info, "Pongo");
	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.15f;
	graphics::drawText(CANVAS_WIDTH / 2 - 155, CANVAS_HEIGHT / 2 - 550, 100, info, br);
	sprintf_s(info, "Press ENTER to play vs a player");
	graphics::drawText(CANVAS_WIDTH / 2 - 480, CANVAS_HEIGHT / 2 - 400, 55, info, br);
	sprintf_s(info, "Press SPACE to play vs an ai");
	graphics::drawText(CANVAS_WIDTH / 2 - 420, CANVAS_HEIGHT / 2 - 280, 55, info, br);
	sprintf_s(info, "controls");
	graphics::drawText(CANVAS_WIDTH / 2 - 140, CANVAS_HEIGHT / 2 + 250, 55, info, br);
	sprintf_s(info, "A and D");
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	graphics::drawText(CANVAS_WIDTH / 2 - 100, CANVAS_HEIGHT / 2 + 480, 55, info, br);
	sprintf_s(info, "arrow keys");
	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 1.0f;
	graphics::drawText(CANVAS_WIDTH / 2 - 170, CANVAS_HEIGHT / 2 + 360, 55, info, br);
}

void Game::drawEndScreen()
{
	drawHelp();

	int player_score = ball->getPlayerScore();
	int opponent_score = ball->getOpponentScore();

	std::stringstream ss1;
	ss1 << player_score;
	std::string str1 = ss1.str();

	std::stringstream ss2;
	ss2 << opponent_score;
	std::string str2 = ss2.str();

	graphics::Brush br;
	char info[40];
	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.15f;

	std::string str = str1 + "   " + str2;
	graphics::drawText(CANVAS_WIDTH / 2 - 100, CANVAS_HEIGHT / 2 - 400, 100, str, br);
	sprintf_s(info, "Press ENTER to play again vs a player");
	graphics::drawText(CANVAS_WIDTH / 2 - 465, CANVAS_HEIGHT / 2 + 280, 45, info, br);
	sprintf_s(info, "Press SPACE to play again vs an ai");
	graphics::drawText(CANVAS_WIDTH / 2 - 420, CANVAS_HEIGHT / 2 + 350, 45, info, br);
	sprintf_s(info, "Press ESC to quit the game");
	graphics::drawText(CANVAS_WIDTH / 2 - 330, CANVAS_HEIGHT / 2 + 420, 45, info, br);
	if (player_score >= opponent_score)
	{
		sprintf_s(info, "Red wins!");
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 0.0f;
		br.fill_color[2] = 0.0f;
		graphics::drawText(CANVAS_WIDTH / 2 - 245, CANVAS_HEIGHT / 2 - 550, 100, info, br);
	}
	else if (player_score < opponent_score)
	{
		sprintf_s(info, "Blue wins!");
		br.fill_color[0] = 0.0f;
		br.fill_color[1] = 0.0f;
		br.fill_color[2] = 1.0f;
		graphics::drawText(CANVAS_WIDTH / 2 - 260, CANVAS_HEIGHT / 2 - 550, 100, info, br);
	}

}

void Game::drawHelp() 
{
	graphics::Brush bg;
	bg.texture = std::string(ASSET_PATH) + "bg.png";
	bg.outline_opacity = 0.0f;

	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, bg);
	graphics::setFont(std::string(ASSET_PATH) + "Font.ttf");

	graphics::Brush ball;
	ball.texture = std::string(ASSET_PATH) + "football.png";
	ball.outline_opacity = 0.0f;
	graphics::drawRect(start_ball_posx, start_ball_posy, 60, 60, ball);

	graphics::Brush opp;
	opp.fill_color[0] = 0.0f;
	opp.fill_color[1] = 0.0f;
	opp.fill_color[2] = 1.0f;
	opp.fill_opacity = 1.0f;
	opp.gradient = true;
	opp.outline_opacity = 0.0f;
	opp.gradient_dir_u = 0.0f;
	opp.gradient_dir_v = 0.7f;
	graphics::drawRect(start_opp_posx, start_opp_posy, PLAYER_WIDTH, PLAYER_HEIGHT, opp);

	graphics::Brush plr;
	plr.fill_color[0] = 1.0f;
	plr.fill_color[1] = 0.0f;
	plr.fill_color[2] = 0.0f;
	plr.fill_opacity = 1.0f;
	plr.gradient = true;
	plr.outline_opacity = 0.0f;
	plr.gradient_dir_u = 0.0f;
	plr.gradient_dir_v = 0.7f;
	graphics::drawRect(start_plr_posx, start_plr_posy, PLAYER_WIDTH, PLAYER_HEIGHT, plr);

}

void Game::updateGame()
{	
	if (graphics::getGlobalTime() > 1000 && !player_flag && !opponent_flag && !ball_flag)
	{
		player = new Player();
		opponent = new Opponent();
		ball = new Ball();
		ball->init();
		if (end_startscreen_time - 1000 <= 0)
			ball->setTime(1000);
		else
			ball->setTime(end_startscreen_time);
		ball->reset();
		player_flag = true;
		opponent_flag = true;
		ball_flag = true;
	}

	if (player)
		player->update();

	if (opponent)
	{
		if (!ai_flag)
			opponent->update();
		else
			opponent->ai_update(ball->getpos_x());
	}
	
	if (ball)
	{
		if (ball->resetAll())
		{
			ball->setInvisibleFlag(false);
			ball->setTiny(false);
			opponent->setSmall(false);
			player->setSmall(false);
			opponent->setInversionFlag(false);
			player->setInversionFlag(false);
			opponent->setSlowFlag(false);
			player->setSlowFlag(false);
		}
		int rng = ball->getRngDebuff();
		int rng_2 = -1;
		if (rng == 5)
		{
			rng = ball->getRngDebuff2();
			rng_2 = ball->getRngDebuff3();
		}
		if (rng == 0 || rng_2 == 0)
		{
			ball->setInvisibleFlag(true);
		}
		if (rng == 1 || rng_2 == 1)
		{
			ball->setTiny(true);
		}
		if (rng == 2 || rng_2 == 2)
		{
			opponent->setSmall(true);
			player->setSmall(true);
		}
		if (rng == 3 || rng_2 == 3)
		{
			opponent->setInversionFlag(true);
			player->setInversionFlag(true);
		}
		if (rng == 4 || rng_2 == 4)
		{
			opponent->setSlowFlag(true);
			player->setSlowFlag(true);
		}
		
		ball->update();
		
	}
}

void Game::updateStartScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_RETURN))
	{
		game_flag = true;
		end_startscreen_time = graphics::getGlobalTime();
	}
	if (graphics::getKeyState(graphics::SCANCODE_SPACE))
	{
		game_flag = true;
		ai_flag = true;
		end_startscreen_time = graphics::getGlobalTime();
	}
	if (graphics::getGlobalTime() > 1000)
	{
		start_end_update();
	}

}

void Game::updateEndScreen()
{
	if (!endscreen_flag)
	{
		endscreen_flag = true;
		start_ball_posx = CANVAS_WIDTH / 2;
		start_ball_posy = CANVAS_HEIGHT / 2;
		start_plr_posx = CANVAS_WIDTH / 2;
		start_plr_posy = CANVAS_HEIGHT - 75;
		start_opp_posx = CANVAS_WIDTH / 2,
		start_opp_posy = 75;
	}
	
	if (!sound_flag)
	{
		graphics::playSound(std::string(ASSET_PATH) + "applause.MP3", 0.1f);
		sound_flag = true;
	}
	if (graphics::getKeyState(graphics::SCANCODE_RETURN))
	{
		game_end_flag = false;
		ai_flag = false;
		ball->resetScore();
		ball->setTime(graphics::getGlobalTime());
		ball->reset();
	}
	if (graphics::getKeyState(graphics::SCANCODE_SPACE))
	{
		game_end_flag = false;
		ai_flag = true;
		ball->resetScore();
		ball->setTime(graphics::getGlobalTime());
		ball->reset();
	}

	start_end_update();
}

bool Game::checkCollision()
{	
	if (!player || !opponent)
	{
		return false;
	}

	Rect r1 = player->getCollisionHull();
	Rect r2 = opponent->getCollisionHull();
	Rect rb = ball->getCollisionHull();

	//player-ball collision detection
	if (r1.ry <= rb.ry + rb.height &&
		(r1.rx + r1.width / 2 + 20 >= rb.rx &&
		r1.rx - r1.width / 2 - 20 <= rb.rx))
		{
		if (rb.ry + rb.height / 2 >= r1.ry - r1.height / 2)
		{
			ball->increment_opponent_score();
			ball->setTime(graphics::getGlobalTime());
			graphics::playSound(std::string(ASSET_PATH) + "goal.MP3", 0.5f);
			ball->setResetAll(true);
			ball->getRng();
			ball->reset();
		}
		graphics::playSound(std::string(ASSET_PATH) + "collision.MP3", 1);
		return true;
	}
	
	//opponent-ball collision detection
	if (r2.ry >= rb.ry - rb.height &&
		(r2.rx + r2.width / 2 + 20 >= rb.rx &&
			r2.rx - r2.width / 2 - 20 <= rb.rx))
	{	
		if (rb.ry - rb.height / 2 <= r2.ry + r2.height / 2)
		{
			ball->increment_player_score();
			ball->setTime(graphics::getGlobalTime());
			graphics::playSound(std::string(ASSET_PATH) + "goal.MP3", 0.5f);
			ball->setResetAll(true);
			ball->getRng();
			ball->reset();
		}
		graphics::playSound(std::string(ASSET_PATH) + "collision.MP3", 1);
		return true;
	}	

	return false;
}

void Game::start_end_update()
{
	start_ball_posx += start_ball_speedx * graphics::getDeltaTime() / 8.0f;
	start_ball_posy += start_ball_speedy * graphics::getDeltaTime() / 8.0f;

	if (start_ball_posx >= CANVAS_WIDTH - 130)
	{
		start_ball_speedx *= -1;
	}

	if (start_ball_posx <= 130)
	{
		start_ball_speedx *= -1;
	}

	if (start_plr_posx >= start_ball_posx)
	{
		start_plr_posx -= 8.0f * graphics::getDeltaTime() / 8.0f;
	}

	if (start_plr_posx <= start_ball_posx)
	{
		start_plr_posx += 8.0f * graphics::getDeltaTime() / 8.0f;
	}

	if (start_plr_posx >= CANVAS_WIDTH - 230)
	{
		start_plr_posx = CANVAS_WIDTH - 230;
	}

	if (start_plr_posx <= 233)
	{
		start_plr_posx = 233;
	}

	if (start_opp_posx >= start_ball_posx)
	{
		start_opp_posx -= 8.0f * graphics::getDeltaTime() / 8.0f;
	}

	if (start_opp_posx <= start_ball_posx)
	{
		start_opp_posx += 8.0f * graphics::getDeltaTime() / 8.0f;
	}

	if (start_opp_posx >= CANVAS_WIDTH - 230)
	{
		start_opp_posx = CANVAS_WIDTH - 230;
	}

	if (start_opp_posx <= 233)
	{
		start_opp_posx = 233;
	}

	if (start_plr_posy <= start_ball_posy + 50 &&
		(start_plr_posx + 260 / 2 + 20 >= start_ball_posx &&
			start_plr_posx - 260 / 2 - 20 <= start_ball_posx))
	{
		start_ball_speedy *= -1;
	}

	if (start_opp_posy >= start_ball_posy - 50 &&
		(start_opp_posx + 260 / 2 + 20 >= start_ball_posx &&
			start_opp_posx - 260 / 2 - 20 <= start_ball_posx))
	{
		start_ball_speedy *= -1;
	}
}

void Game::init()
{
}

Game::Game()
{
}

Game::~Game()
{
	if (player) 
	{
		delete player;
	}
	if (opponent)
	{
		delete opponent;
	}
	if (ball)
	{
		delete ball;
	}
}
