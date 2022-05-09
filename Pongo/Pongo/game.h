#pragma once
#include "player.h"
#include "opponent.h"
#include "ball.h"

class Game
{
	Player * player = nullptr;
	Opponent * opponent = nullptr;
	Ball * ball = nullptr;
	Ball * ball_2 = nullptr;
	int temp = -1;
	float start_opp_posx = CANVAS_WIDTH / 2, start_plr_posx = CANVAS_WIDTH / 2;
	float start_opp_posy = 75, start_plr_posy = CANVAS_HEIGHT - 75;
	float start_ball_posx = CANVAS_WIDTH / 2, start_ball_posy = CANVAS_HEIGHT / 2;
	float start_ball_speedx = 5.0f, start_ball_speedy = 5.0f;
	int end_startscreen_time;
	bool player_flag = false;
	bool opponent_flag = false;
	bool ball_flag = false;
	bool game_flag = false;
	bool ai_flag = false;
	bool music_flag = false;
	bool game_end_flag = false;
	bool slow_flag;
	bool sound_flag;
	bool endscreen_flag = false;
	bool checkCollision();

public:
	void update();
	void updateGame();
	void updateStartScreen();
	void updateEndScreen();
	void draw();
	void drawGame();
	void drawStartScreen();
	void drawEndScreen();
	void drawHelp();
	void start_end_update();
	void init();
	Game();
	~Game();
};
