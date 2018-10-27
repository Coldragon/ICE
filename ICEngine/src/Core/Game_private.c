﻿#include "Game_private.h"

#include "TypesCore.h"

#include "../Framework/Log.h"

#include <stdio.h>
#include "../Core/Window.h"
#include "Core_private.h"

ICE_Game game = { 0 };
extern ICE_Core core;

void ICE_GameObject_Create(char *window_title, const unsigned int width_window, const unsigned int height_window, int argc, char **argv)
{
	core.argc = argc;
	core.argv = argv;

	// Window and Render
	core.window.handle = SDL_CreateWindow(
		window_title,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width_window,
		height_window,
		SDL_WINDOW_OPENGL | SDL_RENDERER_PRESENTVSYNC | SDL_WINDOW_RESIZABLE
	);
	core.window.render = SDL_CreateRenderer(core.window.handle, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(core.window.render, SDL_BLENDMODE_BLEND);

#if defined(_DEBUG)
	core.lateDrawDebug = NULL;
#endif
	game.current = &game.state_main;
	core.window.w = (ICE_Float)width_window; core.window.h = (ICE_Float)height_window;

	core.window.auto_clear = ICE_True;
	core.window.auto_render = ICE_True;

	SDL_SetRenderDrawBlendMode(core.window.render, SDL_BLENDMODE_BLEND);

	ICE_Window_SetIcon(0);

	ICE_Core_Info(window_title);

	ICE_Log(ICE_LOG_FINISH, "Engine :: Init :: Ok");
	ICE_Log_Line();
	printf("\n");
}

void ICE_GameObject_Destroy()
{
	SDL_DestroyWindow(core.window.handle);
	SDL_DestroyRenderer(core.window.render);
}