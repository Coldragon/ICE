﻿#ifndef DEF_ICE_COLOR_PRIVATE
#define DEF_ICE_COLOR_PRIVATE

#include <SDL2/SDL.h>

#include "TypesGraphics.h"

/**
 * \brief Convert a ICE_Color to a SDL one
 * \param ice_color The ICE_Color to convert
 * \return A SDL_Color converted from a ICE one
 */
inline SDL_Color ICE_Color_ToSdl(const ICE_Color ice_color) {
	SDL_Color sdl_color;
	sdl_color.r = ice_color >> 24 & 255;
	sdl_color.g = ice_color >> 16 & 255;
	sdl_color.b = ice_color >> 8 & 255;
	sdl_color.a = ice_color & 255;
	return sdl_color;
}

#endif