﻿#include "Gui_private.h"
#include "Gui.h"
#include "../Core/TypesCore.h"
#include "../Maths/Vector.h"
#include "../Graphics/TypesGraphics.h"
#include "../Graphics/Texture.h"

extern struct ICE_Game game;

void ICE_Gui_UpdateTexture(int man, int gui)
{
	ICE_Texture texture = { 0 };
	texture.handle = SDL_CreateTexture(game.window.render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, game.state_mngr.current->object.gui_mngr[man].gui[gui].box.w, game.state_mngr.current->object.gui_mngr[man].gui[gui].box.h);
	SDL_SetRenderTarget(game.window.render, texture.handle);
	SDL_SetTextureBlendMode(texture.handle, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(game.window.render, 0, 0, 0, 0);
	SDL_RenderClear(game.window.render);
	ICE_Box box2 = game.state_mngr.current->object.gui_mngr[man].gui[gui].box;
	box2.x = 0; box2.y = 0;
	ICE_Gui_Rect(ICE_Texture_Get(game.state_mngr.current->object.gui_mngr[man].gui[gui].texturemanager_nb, game.state_mngr.current->object.gui_mngr[man].gui[gui].texture_nb), box2);
	SDL_SetRenderTarget(game.window.render, NULL);
	if (game.state_mngr.current->object.gui_mngr[man].gui[gui].texture_cache.handle)
		SDL_DestroyTexture(game.state_mngr.current->object.gui_mngr[man].gui[gui].texture_cache.handle);
	game.state_mngr.current->object.gui_mngr[man].gui[gui].texture_cache = texture;
}

// Deprecated
// Unoptimized function
void ICE_Gui_Rect(ICE_Texture * texture, ICE_Box rect)
{
	ICE_Box src, dst;
	int wtext3 = texture->w / 3;
	int htext3 = texture->h / 3;

	src.w = wtext3; src.h = htext3;

	// CENTER

	src.x = wtext3; src.y = htext3;
	dst.x = rect.x + wtext3; dst.y = rect.y + htext3;
	dst.w = rect.w - (wtext3) * 2; dst.h = rect.h - (htext3) * 2;

	ICE_Texture_RenderEx(texture, &src, &dst, 0);

	dst.w = wtext3; dst.h = htext3;

	// UPMID

	src.x = wtext3; src.y = 0; dst.y = rect.y; dst.x = rect.x + wtext3;
	dst.w = rect.w - (wtext3 * 2);

	ICE_Texture_RenderEx(texture, &src, &dst, 0);

	dst.w = wtext3; dst.h = htext3;

	// LEFTMID

	src.x = 0; src.y = htext3;
	dst.x = rect.x; dst.y = rect.y + htext3;
	dst.h = rect.h - (htext3 * 2);

	ICE_Texture_RenderEx(texture, &src, &dst, 0);

	dst.w = wtext3; dst.h = htext3;

	// RIGHT MID

	src.x = wtext3 * 2; src.y = htext3;
	dst.x = rect.x + rect.w - wtext3; dst.y = rect.y + htext3;
	dst.h = rect.h - (htext3 * 2);

	ICE_Texture_RenderEx(texture, &src, &dst, 0);

	dst.w = wtext3; dst.h = htext3;


	// DOWNMID

	src.x = wtext3; src.y = htext3 * 2; dst.y = rect.y + rect.h - htext3; dst.x = rect.x + wtext3;
	dst.w = rect.w - (wtext3 * 2);

	ICE_Texture_RenderEx(texture, &src, &dst, 0);

	dst.w = wtext3; dst.h = htext3;

	// UPLEFT

	src.x = 0; src.y = 0;
	dst.x = rect.x; dst.y = rect.y;

	ICE_Texture_RenderEx(texture, &src, &dst, 0);

	dst.w = wtext3;

	// UPRIGHT

	src.x = wtext3 * 2; src.y = 0;
	dst.x = rect.x + rect.w - wtext3; dst.y = rect.y;

	ICE_Texture_RenderEx(texture, &src, &dst, 0);

	dst.h = htext3;

	// DOWNLEFT

	src.x = 0; src.y = htext3 * 2;
	dst.x = rect.x; dst.y = rect.y + rect.h - htext3;

	ICE_Texture_RenderEx(texture, &src, &dst, 0);

	// DOWNRIGHT

	src.x = wtext3 * 2; src.y = htext3 * 2;
	dst.x = rect.x + rect.w - wtext3; dst.y = rect.y + rect.h - htext3;

	ICE_Texture_RenderEx(texture, &src, &dst, 0);
}