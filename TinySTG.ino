#include "MainLoop.hpp"
#include "Global.hpp"

void setup()
{
	MainLoop_Setup();
	Global& global = Global::GetInstance();
	global.micros_time = micros();
}

void loop()
{
	Global& global = Global::GetInstance();
	global.interval_time = micros() - global.micros_time;
//	if(global.interval_time > 33333) // 30FPS
	if(global.interval_time > 16667) // 60FPS
	{
		MainLoop_Loop();
		global.micros_time = micros();
	}
	MainLoop_NoWaitLoop();
}
