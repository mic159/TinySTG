#include "TinyLibrary.hpp"
#include "Global.hpp"

Global* Global::global = NULL;

Global::Global(void)
:phase(PHASE_TUCHIKURE_LOGO)
,back_color(0)
,before_button(0)
,game(NULL)
,difficulty(1)
,highscore(10000)
,score(0)
,micros_time(0)
,interval_time(0)
,display_fps(false)
{
}

Global::~Global(void)
{
}

void Global::Initialize(void)
{
	if(Global::global == NULL)
	{
		Global::global = new Global;
	}
}

void Global::Finalize(void)
{
	if(Global::global != NULL)
	{
		delete Global::global;
		Global::global = NULL;
	}
}

Global& Global::GetInstance()
{
	return *Global::global;
}
