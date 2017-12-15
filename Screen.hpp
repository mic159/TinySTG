#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <TinyScreen.h>

#define USE_DMA
#define COLOR8(r,g,b)  ((b>>5)<<5|(g>>5)<<2|(r>>6))               // BBBGGGRR
#define COLOR16(r,g,b) ((((g<<3)&0xE)|(r>>3))<<8)+(b&0xF8)|(g>>5) // GGGRRRRRBBBBBGGG

class Screen
{
public:
	enum
	{
		WIDTH = 96,
		HEIGHT = 64
	};
	static Screen* screen;
	Screen(int color_mode);
	~Screen(void);
	static void Initialize(int color_mode);
	static void Finalize(void);
	static Screen& GetInstance();
	void Clear(unsigned int color);
	void DrawBegin(void);
	void DrawEnd(void);
	void DrawSprite(const void* buffer, int x, int y, int width, int height, int color_key);
	void DrawSprite(const void* buffer, int x, int y, int width, int height, int source_x, int source_y, int source_width, int color_key);
	void DrawSprite(int destination_x, int destination_y, int destination_left, int destination_top, int destination_right, int destination_bottom, const void* source_buffer, int source_x, int source_y, int source_width, int source_height, int color_key, int rotate, int scale);
	void DrawFont(int x, int y, const char* text, ...);
	void DrawNumberFont(int x, int y, const char* text, ...);
	TinyScreen* GetTinyScreen(void);
private:
	void DrawSpriteNoClip(const void* buffer, int x, int y, int width, int height, int color_key, int source_width);
	Screen(Screen&);
	Screen& operator = (Screen&);
	TinyScreen tiny_screen;
	int color_mode;
	unsigned char* screen_buffer[2];
	int current_screen_buffer;
	int buffer_size;
};

#endif
