#ifndef BOSS4_HPP
#define BOSS4_HPP

#include "Enemy.hpp"

class Boss4 : public Enemy
{
public:
	enum
	{
		WIDTH = 62 << 10,
		HEIGHT = 62 << 10,
		WIDTH_HALF = WIDTH / 2,
		HEIGHT_HALF = HEIGHT / 2,
		BULLET_COUNT = 45,
		HIT_INTERVAL = 15,
		// Phase
		PHASE_APPEAR = 0,
		PHASE_WAIT,
		// Collision
		PLAYER_COLLISION_WIDTH = 24 << 10,
		PLAYER_COLLISION_HEIGHT = 24 << 10,
		SHOT_COLLISION_WIDTH = 24 << 10,
		SHOT_COLLISION_HEIGHT = 24 << 10,
	};
	Boss4(void);
	~Boss4(void);
	void Initialize(int type, int x, int y);
	void Update(void);
	void Draw(void);
	bool Collision(Shot& shot);
	bool Collision(int x, int y);
private:
	Boss4(Boss4&);
	Boss4& operator = (Boss4&);
	int bullet_count;
	int phase;
	int hit_interval;
};

#endif
