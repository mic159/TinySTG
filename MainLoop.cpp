#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TinyLibrary.hpp"
#include "Global.hpp"
#include "SoundPlayer.hpp"

void MainLoop_Setup(void)
{
	Global::Initialize();
	Screen::Initialize(16);
	Controller::Initialize();
	SoundPlayer::Initialize(11025);
	Global& global = Global::GetInstance();
	global.phase = Global::PHASE_TUCHIKURE_LOGO;
	global.back_color = 0;
	global.before_button = 1;
	global.count = 0;
}

void MainLoop_Finalize(void)
{
	Global& global = Global::GetInstance();
	if(global.game != NULL)
	{
		global.game->Finalize();
		delete global.game;
		global.game = NULL;
	}
	SoundPlayer::Finalize();
	Controller::Finalize();
	Screen::Finalize();
	Global::Finalize();
}

void MainLoop_Loop(void)
{
	bool status;
	Global& global = Global::GetInstance();
	Screen& screen = Screen::GetInstance();
	Controller& controller = Controller::GetInstance();
	controller.Update();
	screen.Clear(global.back_color);
	screen.DrawBegin();
	unsigned int button = controller.GetButton();
#if defined(_WIN32) || defined(__ANDROID__)
	dms::Touch::Status touch_status = dms::Touch::GetStatus();
	if(touch_status.touch == true)
	{
		float rate = Screen::WIDTH / dms::Graphics::GetWindowWidth();
		float touch_x = touch_status.x * rate;
		float touch_y = touch_status.y * rate;
		if((touch_x > 42.0f) && (touch_y > 56.0f) && (touch_y < 64.0f) && (global.phase == Global::PHASE_TITLE))
		{
			button |= Controller::BUTTON_RIGHT;
		}
		else
		{
			button |= Controller::BUTTON_1;
		}
	}
#endif
	const ImageData* image_data;
	const unsigned char* bg_buffer;
	switch(global.phase)
	{
	case Global::PHASE_TUCHIKURE_LOGO:
		image_data = GetImageData(TUCHIKURE_LOGO);
		screen.DrawSprite(image_data->buffer, 0, 0, image_data->width, image_data->height, 0);
		global.back_color = 0;
		if((global.before_button == 0) && (button & (Controller::BUTTON_1 | Controller::BUTTON_2)))
		{
			global.phase = Global::PHASE_DAIMON_LOGO;
		}
		++ global.count;
		if(global.count > 60 * 1)
		{
			global.phase = Global::PHASE_DAIMON_LOGO;
			global.count = 0;
		}
		rand();
		break;
	case Global::PHASE_DAIMON_LOGO:
		image_data = GetImageData(DAIMON_LOGO);
		screen.DrawSprite(image_data->buffer, 0, 0, image_data->width, image_data->height, 0);
		global.back_color = 0;
		if((global.before_button == 0) && (button & (Controller::BUTTON_1 | Controller::BUTTON_2)))
		{
			global.phase = Global::PHASE_TITLE;
		}
		++ global.count;
		if(global.count > 60 * 1)
		{
			global.phase = Global::PHASE_TITLE;
			global.count = 0;
		}
		rand();
		break;
	case Global::PHASE_TITLE:
		image_data = GetImageData(BG);
		bg_buffer = reinterpret_cast<const unsigned char*>(image_data->buffer) + (265 * 96);
		screen.DrawSprite(bg_buffer, 0, 0, image_data->width, 64, -1);
		image_data = GetImageData(TITLE_LOGO);
		screen.DrawSprite(image_data->buffer, (Screen::WIDTH - image_data->width) / 2, 5, image_data->width, image_data->height, 0);
		global.back_color = 0;
		if(button != 0)
		{
			global.count = 0;
		}
		if((global.before_button == 0) && (button & (Controller::BUTTON_1 | Controller::BUTTON_2)))
		{
			global.phase = Global::PHASE_INITIALIZE_GAME;
		}
		// Menu
		if(!(global.before_button & Controller::BUTTON_RIGHT) && (button & Controller::BUTTON_RIGHT))
		{
			++ global.difficulty;
			if(global.difficulty > Game::VERY_HARD)
			{
#if defined(_WIN32) || defined(__ANDROID__)
				global.difficulty = Game::EASY;
#else
				global.difficulty = Game::VERY_HARD;
#endif
			}
		}
		else if(!(global.before_button & Controller::BUTTON_LEFT) && (button & Controller::BUTTON_LEFT))
		{
			-- global.difficulty;
			if(global.difficulty < Game::EASY)
			{
				global.difficulty = Game::EASY;
			}
		}
		if(!(global.before_button & Controller::BUTTON_UP) && (button & Controller::BUTTON_UP))
		{
			if(global.display_fps == true)
			{
				global.display_fps = false;
			}
			else
			{
				global.display_fps = true;
			}
		}
		switch(global.difficulty)
		{
		case Game::EASY:
			screen.DrawFont(72, 56, "Easy");
			break;
		case Game::NORMAL:
			screen.DrawFont(60, 56, "Normal");
			break;
		case Game::HARD:
			screen.DrawFont(72, 56, "Hard");
			break;
		case Game::VERY_HARD:
			screen.DrawFont(42, 56, "Very hard");
			break;
		}
		screen.DrawFont(0, 34, "Press button");
		screen.DrawFont(12, 42, "to game start!");
		++ global.count;
		if(global.count > 60 * 10)
		{
			global.phase = Global::PHASE_TUCHIKURE_LOGO;
			global.count = 0;
		}
		screen.DrawNumberFont(0, 0, "%8d", global.score);
		screen.DrawNumberFont(64, 0, "%8d", global.highscore);
		rand();
		break;
	case Global::PHASE_INITIALIZE_GAME:
		global.game = new Game;
		global.game->Initialize(1, global.difficulty);
		global.phase = Global::PHASE_GAME;
		break;
	case Global::PHASE_GAME:
		status = global.game->Update();
		global.game->Draw();
		global.back_color = global.game->GetBackColor();
		if(status == true)
		{
			global.game->Finalize();
			delete global.game;
			global.game = NULL;
			global.phase = Global::PHASE_TUCHIKURE_LOGO;
		}
		break;
	}
	if(global.display_fps == true)
	{
		int fps = 100000000 / global.interval_time;
		screen.DrawNumberFont(38, 0, "%2d.%2d", fps / 100, fps % 100);
	}
	screen.DrawEnd();
	global.before_button = button;
}

void MainLoop_NoWaitLoop(void)
{
	//SoundPlayer& sound_player = SoundPlayer::GetInstance();
	//sound_player.Update();
}
