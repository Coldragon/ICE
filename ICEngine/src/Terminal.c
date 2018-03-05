﻿#include "hdr/Terminal.h"
#include "external/rlutil.h"
#include "hdr/TypesCore.h"
#include "hdr/Time_.h"
#include "hdr/Log.h"

extern ICE_Game game;

void ICE_TermResetColor(){
	if (game.debug)
		resetColor();
}
char ICE_TermSetColor(const int c){
	if (game.debug)
		setColor(c);
	return '\0';
}
char ICE_TermSetBgColor(const int c){
	if (game.debug)
		setBackgroundColor(c);
	return '\0';
}

void ICE_TermClear(){
	if (game.debug)
		cls();
}

void ICE_TermClock(){
	if (game.debug)
	{
		ICE_TermSetColor(iceLIGHTCYAN);
		printf("[%.3f s]", ICE_TimeClock());
		ICE_TermResetColor();
		printf("::");
	}
}

void ICE_TermWait(){
	if (game.debug)
	{
		ICE_Log_no_n(ICE_LOG_NONE, "TERMINAL]::[PRESSRETURNTOCONTINUE");
		#ifdef getch
		getch();
		puts("");
		#else
		getchar();
		#endif
	}
}