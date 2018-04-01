﻿#include <string.h>
#include <stdio.h>

#include "Input.h"
#include "Debug.h"

#include "../Framework/Terminal.h"
#include "../Framework/Log.h"

extern ICE_Game game;

ICE_Bool ICE_Input_Press(enum ICE_InputKey button)
{
	if (button < 512)
	{
		return game.window.input.key[button];
	}
	if (button > 600 && button < ICE_INPUT_MAX)
	{
		if (button == ICE_INPUT_LEFTCLICK)
		{
			return game.window.input.leftclic;
		}
		if (button == ICE_INPUT_RIGHTCLICK)
		{
			return game.window.input.rightclic;
		}
		if (button == ICE_INPUT_WHEELUP)
		{
			return game.window.input.wheelup;
		}
		if (button == ICE_INPUT_WHEELDOWN)
		{
			return game.window.input.wheeldown;
		}
	}
	else
	{
		ICE_Log(ICE_LOG_WARNING, "INPUT]::[NOKEY]::[%d", button);
		return ICE_False;
	}

	return ICE_False;
}

void ICE_Input_Quit()
{
	game.window.input.quit = ICE_True;
}

void ICE_Input_Reset() {
	int temp = game.window.input.focus;
	int temp2 = game.window.input.quit;
	int mousex = game.window.input.mousex;
	int mousey = game.window.input.mousey;
	memset(&game.window.input, 0, sizeof(ICE_Input));
	game.window.input.focus = temp;
	game.window.input.quit = temp2;
	game.window.input.mousex = mousex;
	game.window.input.mousey = mousey;


	printf("Input Reset : ");
	ICE_Term_SetColor(ICE_T_GREEN);
	printf("OK\n");
	ICE_Term_ResetColor();
}