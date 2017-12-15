#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include "Game.hpp"

class Global
{
public:
	enum
	{
		PHASE_TUCHIKURE_LOGO = 0,
		PHASE_DAIMON_LOGO,
		PHASE_TITLE,
		PHASE_INITIALIZE_GAME,
		PHASE_GAME,
	};
	Global(void);
	~Global(void);
	static Global* global;
	static Global& GetInstance();
	static void Initialize(void);
	static void Finalize(void);
	int phase;
	unsigned char back_color;
	unsigned int before_button;
	Game* game;
	int count;
	int difficulty;
	int highscore;
	int score;
	unsigned long micros_time;
	unsigned long interval_time;
	bool display_fps;
private:
	Global(Global&);
	Global& operator = (Global&);
};

#endif
