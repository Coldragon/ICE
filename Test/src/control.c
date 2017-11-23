#include "hdr/control.h"

void Control(ICE_Game *game) {
	DATA0 *data = ICE_GetData(game, 0); // Make DATA0 avaible in the scope
	if (game->input->key[SDL_SCANCODE_D] || game->input->key[SDL_SCANCODE_RIGHT]) ICE_CameraShiftPos(game, iceVectNew(data->speed_camera, 0));
	if (game->input->key[SDL_SCANCODE_A] || game->input->key[SDL_SCANCODE_LEFT]) ICE_CameraShiftPos(game, iceVectNew (-data->speed_camera, 0));
	if (game->input->key[SDL_SCANCODE_S] || game->input->key[SDL_SCANCODE_DOWN]) ICE_CameraShiftPos(game, iceVectNew(0, data->speed_camera));
	if (game->input->key[SDL_SCANCODE_W] || game->input->key[SDL_SCANCODE_UP]) ICE_CameraShiftPos(game, iceVectNew(0, -data->speed_camera));
	if (game->input->key[SDL_SCANCODE_SPACE]) ICE_CameraMovePos(game, iceVectNew(0,0), data->speed_camera);
	if (game->input->key[SDL_SCANCODE_ESCAPE]) ICE_SubstateLoop(game, menu_create, menu_update, menu_destroy);
}
