﻿#include "Terminal.h"

#include "../External/rlutil/rlutil.h"

#include "TypesFramework.h"
#include "Log.h"
#include <time.h>

#if defined(_DEBUG)

void ICE_Term_ResetColor(){
	resetColor();
}
void ICE_Term_SetColor(const int c){
	setColor(c);
}
void ICE_Term_SetBgColor(const int c){
	setBackgroundColor(c);
}

void ICE_Term_Clear(){
	cls();
}

void ICE_Term_Clock(){
	ICE_Term_SetColor(ICE_TERMCOLOR_LIGHTCYAN);
	printf("[%.3f s]", (ICE_Float)clock()/1000.0f);
	ICE_Term_ResetColor();
	printf("");
}

void ICE_Term_Wait(){
	ICE_Log_NoReturn(ICE_LOG_NONE, "TERMINAL]::[PRESSRETURNTOCONTINUE");
	#ifdef getch
	getch();
	puts("");
	#else
	getchar();
	#endif
}

#endif