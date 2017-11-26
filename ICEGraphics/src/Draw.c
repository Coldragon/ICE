#include "hdr/Draw.h"
#include "hdr/Texture.h"
#include "hdr/Camera.h"
#include "hdr/Text.h"

int iceDrawClearColor(SDL_Renderer *render, const iceColor rgba_hex){
	const int r = rgba_hex >> 24 & 255;
	const int g = rgba_hex >> 16 & 255;
	const int b = rgba_hex >> 8 & 255;
	const int a = rgba_hex & 255;
	return SDL_SetRenderDrawColor(render, r, g, b, a);
}

void iceDrawSetColor(iceGame *game, iceColor color)
{
	game->background = color;
}

int iceDrawClear(SDL_Renderer *render){
	return SDL_RenderClear(render);
}
void iceDrawPresent(SDL_Renderer *render){
	SDL_RenderPresent(render);
}

void iceDrawAllEntity(iceGame *game)
{
	for (int i = 0; i < game->entitymanager_size; i++)
		for (int j = 0; j < game->entitymanager[i].nb_existing; j++)
		{
			if (game->entitymanager[i].entity[j].have_texture && game->entitymanager[i].entity[j].exist)
			{
				iceBox rect = iceCameraWorldScreen(iceBoxNew(
					game->entitymanager[i].entity[j].x,
					game->entitymanager[i].entity[j].y,
					game->entitymanager[i].entity[j].w,
					game->entitymanager[i].entity[j].h), &game->camera);

				iceTextureRenderCentered(
					game,
					game->entitymanager[i].entity[j].man,
					game->entitymanager[i].entity[j].text,
					NULL, &rect);
			}
		}
}

void iceDrawAllText(iceGame *game)
{
	for (int i = 0; i < game->textmanager_size; i++)
		for (int j = 0; j < game->textmanager[i].nb_existing; j++)
		{
			// Fixed to screen
			if (game->textmanager[i].text[j].exist)
			{
				if (
					strcmp(game->textmanager[i].text[j].text, game->textmanager[i].text[j].old_text) ||
					game->textmanager[i].text[j].size != game->textmanager[i].text[j].old_size ||
					game->textmanager[i].text[j].color != game->textmanager[i].text[j].old_color
					)
				{
					iceTextUpdateTexture(game, i, j);
					game->textmanager[i].text[j].old_color = game->textmanager[i].text[j].color;
					game->textmanager[i].text[j].old_size = game->textmanager[i].text[j].size;
					free(game->textmanager[i].text[j].old_text);
					game->textmanager[i].text[j].old_text = STRDUP(game->textmanager[i].text[j].text);
				}
				
				iceBox box = iceBoxNew(
					game->textmanager[i].text[j].pos.x,
					game->textmanager[i].text[j].pos.y,
					game->textmanager[i].text[j].texture.w,
					game->textmanager[i].text[j].texture.h
				);

				// Fixed to screen 
				if(!game->textmanager[i].text[j].isFixedToWorld)
					iceTextureRenderCenteredTexture(game, &game->textmanager[i].text[j].texture, NULL, &box);
				// Fixed to world
				else
					iceTextureRenderCenteredTexture(game, &game->textmanager[i].text[j].texture, NULL, (iceBox[]) { iceCameraWorldScreen(box, &game->camera) });
			}	
		}
}