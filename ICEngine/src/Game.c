#include "hdr/Game.h"

void ICE_SetWindowIcon(ICE_Window *window, char * path)
{
	if (!path){
		#include "raw/Raw_icon.c"

		Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		int shift = (ice_raw_img_icon.bytes_per_pixel == 3) ? 8 : 0;
		rmask = 0xff000000 >> shift;
		gmask = 0x00ff0000 >> shift;
		bmask = 0x0000ff00 >> shift;
		amask = 0x000000ff >> shift;
#else // little endian, like x86
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = (ice_raw_img_icon.bytes_per_pixel == 3) ? 0 : 0xff000000;
#endif

		SDL_Surface* icon = SDL_CreateRGBSurfaceFrom((void*)ice_raw_img_icon.pixel_data, ice_raw_img_icon.width,
			ice_raw_img_icon.height, ice_raw_img_icon.bytes_per_pixel * 8, ice_raw_img_icon.bytes_per_pixel*ice_raw_img_icon.width,
			rmask, gmask, bmask, amask);

		SDL_SetWindowIcon(window, icon);

		SDL_FreeSurface(icon);
	}
	else
	{
		SDL_Surface *icon = SDL_LoadBMP(path);
		SDL_SetWindowIcon(window, icon);
		SDL_FreeSurface(icon);
	}
}

ICE_Game ICE_CreateGame(char *window_title, const unsigned int width_window, const unsigned int height_window)
{
	ICE_Game game = {0};

	// Window and Render
	game.window = SDL_CreateWindow(
		window_title, 
		SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED, 
		width_window, 
		height_window, 
		SDL_WINDOW_OPENGL | SDL_RENDERER_PRESENTVSYNC | SDL_WINDOW_RESIZABLE
	);
	game.render = SDL_CreateRenderer(game.window, -1, SDL_RENDERER_ACCELERATED);
	ICE_SetRenderClearColor(game.render, NewColor(100, 25, 12));    

	// Render Info
	SDL_RendererInfo info;
	SDL_GetRendererInfo(game.render, &info);
	printf("Graphic API : %s \n", info.name);
	SDL_SetRenderDrawBlendMode(game.render, SDL_BLENDMODE_BLEND);

	// Input
	game.input = (ICE_Input*)calloc(1, sizeof(ICE_Input));
	//

	// TextureManager
	game.texturemanager_size = 0;
	ICE_CreateTextureManager(&game);
	
	// Time
	memset(&game.time, 0, sizeof(ICE_Time));
	game.time.fps = 120; game.time.ticks = (double)1000 / game.time.fps;

	// Sound
	ICE_CreateSoundManager(&game); // Create the Sound Manager

	game.camera.x = 0; game.camera.y = 0; 
	game.camera.w = width_window; game.camera.h = height_window;
	ICE_SetWindowIcon(game.window, 0);

	game.data = malloc(0);
	game.nb_data = 0;
	return game;    
}

void ICE_DestroyGame(ICE_Game *app)
{
	SDL_DestroyWindow(app->window);
	SDL_DestroyRenderer(app->render);
	free(app->input);
}

/// Make a Data and create a pointer in the game->data array (return the pointer created)
void* ICE_AddData(ICE_Game *game, size_t _size)
{
	game->nb_data++;
	game->data = realloc(game->data, sizeof(void*)*game->nb_data);
	game->data[game->nb_data-1] = calloc(1, _size);
	void * _pointer = game->data[game->nb_data - 1];
	return _pointer;
}

/// Return pointer to a Data
void* ICE_GetData(ICE_Game *game, int nb_data)
{
	void * _pointer;

	if (nb_data <= game->nb_data)
		_pointer = game->data[nb_data];

	////////////////////////////////////////////
	//                                        //
	// If you see this assert, you choosed    //
	// a data that doesn't exist              //
	//                                        //
	////////////////////////////////////////////

	else
	{
		_pointer = NULL;
		//assert(("Pointer is null so there is no data at this number", _pointer));
		ICE_Assert(_pointer != NULL, "Pointer is null so there is no data at this number");
	}

	return _pointer;
}

/// Destroy a Data
void ICE_DestroyData(ICE_Game *game, int nb_data)
{
	void * _pointer;
	
	if (nb_data <= game->nb_data)
		_pointer = game->data[nb_data];
	
	////////////////////////////////////////////
	//                                        //
	// If you see this assert, you choosed    //
	// a data that doesn't exist              //
	//                                        //
	////////////////////////////////////////////
	
	else
	{
		_pointer = NULL;
		//assert("Pointer is null so there is no data at this number", _pointer);
		ICE_Assert(_pointer!=NULL, "Pointer is null so there is no data at this number");
	}
	 
	free(_pointer);
}

/// WINDOW EFFECT

void ICE_GameResizable(ICE_Game *game, int yn)
{
	SDL_SetWindowResizable(game->window, yn);
}

void ICE_GameTitle(ICE_Game *game, const char *title)
{
	SDL_SetWindowTitle(game->window, title);
}