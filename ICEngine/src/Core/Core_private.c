﻿#include "Core_private.h"

#include "Time_private.h"
#include "TypesCore.h"
#include "Label.h"

#include "../Framework/Terminal_private.h"
#include "../Framework/Log.h"
#include "../Graphics/Gui.h"
#include "../Graphics/Texture.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "../Audio/Audio.h"
#include "../Audio/Sound.h"

extern ICE_Game game;

int ICE_Core_Init() {
	// Other
	ICE_Term_SaveColor();
	printf("------------------------\n");
	ICE_Log(ICE_LOG_RUNNING, "Engine]::[Init]::[Start");
	printf("------------------------\n");
	ICE_Term_HideCursor();

	// SDL
	SDL_Init(SDL_INIT_VIDEO);
	ICE_Audio_Init();
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	TTF_Init();
	
	// SDL_gfx
	ICE_Time_Init();

	return 0;
}

int ICE_Core_Close() {
	printf("------------------------\n");
	ICE_Log(ICE_LOG_RUNNING, "Engine]::[Close]::[Start");
	printf("------------------------\n");

	// Manager Clean
	ICE_LabelManager_DestroyAll();
	ICE_GuiManager_DestroyAll();
	ICE_TextureManager_DestroyAll();
	ICE_SoundManager_DestroyAll();

	// SDL
	TTF_Quit();
	ICE_Audio_Close();
	SDL_Quit();

	printf("------------------------\n");
	ICE_Log(ICE_LOG_SUCCES, "Engine]::[Close]::[Finish");
	printf("------------------------\n\n");


	return 0;
}