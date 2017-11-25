#include <Core.h>

ICE_CREATE {
	iceGame game = iceGameCreate("ICE : Hello World", 800, 480);
	iceFontLoad(&game, "res/ttf/FiraSans-Medium.ttf");
	iceTextureCreate(&game, 0, "res/img/pic.png");
	iceTextureCreate(&game, 0, "res/img/backxc.jpg");
	return game;
}

ICE_UPDATE {
	iceTextureRenderCentered(game, 0, 0, NULL, (iceBox[]) { iceCameraWorldScreen(iceBoxNew(0, 0, 500, 750), &game->camera) });
	iceTextureRenderCentered(game, 0, 1, NULL, (iceBox[]) { iceCameraWorldScreen(iceBoxNew(0, 0, iceTextureGetWidth(game, 0, 1), iceTextureGetHeight(game, 0, 1)), &game->camera) });
	iceFontDraw(game, "Hello World", 80, iceVectNew(0, 0));
}

ICE_DESTROY {
}

int main(){
	return ICE_GAME_RUN;
}