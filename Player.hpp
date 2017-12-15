#ifndef PLAYER_HPP
#define PLAYER_HPP

class Enemy;
class Bullet;

class Player
{
public:
	enum
	{
		WIDTH = 10 << 10,
		HEIGHT = 10 << 10,
		WIDTH_HALF = WIDTH / 2,
		HEIGHT_HALF = HEIGHT / 2,
		START_X = 43 << 10,
		START_Y = 45 << 10,
		START_TAKEOFF_Y = 70 << 10,
		SPEED = 1 << 10,
		SPEED_ASLANT = (SPEED >> 10) * 724,
		LIMIT_X = (96 << 10) - WIDTH_HALF,
		LIMIT_Y = (64 << 10) - HEIGHT_HALF,
		// Shot
		SHOT_UP_MAX = 8,
		SHOT_COOL_TIME = 8,
		// Status
		STATUS_DEAD = 0,
		STATUS_ALIVE,
		// Phase
		PHASE_TAKEOFF = 0,
		PHASE_INVINCIBLE,
		PHASE_MOVE,
		PHASE_WAIT,
	};
	Player(void);
	~Player(void);
	void Initialize(void);
	void Update(void);
	void Draw(void);
	unsigned int GetStatus(void);
	void SetStatus(unsigned int status);
	void GetPosition(int& x, int& y);
	void GetVector(int& vx, int& vy);
	bool Collision(Bullet& bullet);
	int GetShotPower(void);
	bool ShotPowerUp(void);
	bool IsInvincinle(void);
	int GetBomber(void);
	bool Bomber(void);
private:
	Player(Player&);
	Player& operator = (Player&);
	int x;
	int y;
	int vx;
	int vy;
	int status;
	int phase;
	int draw_counter;
	int counter;
	int shot_cool_time_count;
	int shot_power;
	bool before_bomber;
	int bomber;
#if defined(_WIN32) || defined(__ANDROID__)
	bool before_button;
	float before_x;
	float before_y;
#endif
};

#endif
