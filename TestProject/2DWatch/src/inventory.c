﻿#include <ICE.h>
#include "inventory.h"
#include "data.h"

void inventory_create()
{
	ICE_Render_Color(ICE_Color_New(50, 50, 50));

	DATA1 * data = ICE_Data_Get(ICE_State_GetParent(NULL), 0);
	ICE_Index man = ICE_LabelManager_Insert(NULL);
	ICE_Index nb = ICE_Label_Insert
	(
		NULL, 
		0, 
		L"", 
		ICE_Vect_New(50, 20), 
		12, 
		ICE_LabelType_Screen
	);
	ICE_Label_SetString
	(
		ICE_Label_Get(NULL, man, nb), 
		"Name : %s     Damage : %.1f     Speed : %.1f", 
		data->current_weapon.name, 
		data->current_weapon.damage, 
		data->current_weapon.speed
	);
	ICE_Label_SetWrapWidth(ICE_Label_Get(NULL, man, nb), 100);
	ICE_GuiManager_Insert(NULL);
	ICE_Gui_Insert
	(
		NULL,
		0,
		ICE_Box_New
		(
			ICE_Label_GetX(ICE_Label_Get(NULL, man, nb)) - 5,
			ICE_Label_GetY(ICE_Label_Get(NULL, man, nb)),
			ICE_Label_GetWidth(ICE_Label_Get(NULL, man, nb)) + 10,
			ICE_Label_GetHeight(ICE_Label_Get(NULL, man, nb) + 2)
		),
		0,
		1
	);
}

void inventory_update()
{
	ICE_Debug_DrawFps(5);

	ICE_Label_SetPos(ICE_Label_Get(NULL, 0, 0), ICE_Vect_New(ICE_Input_MouseX() + 15, ICE_Input_MouseY() - 10));
	DATA1 * data = ICE_Data_Get(ICE_State_GetParent(NULL), 0);
	ICE_Gui_SetSize
	(
		ICE_Gui_Get(NULL, 0, 0),
		ICE_Vect_New
		(
			ICE_Label_GetWidth(ICE_Label_Get(NULL, 0, 0)) + 10,
			ICE_Label_GetHeight(ICE_Label_Get(NULL, 0, 0)) + 2
		)
	);

	ICE_Gui_SetPos
	(
		ICE_Gui_Get(NULL, 0, 0),
		ICE_Vect_New
		(
			ICE_Label_GetX(ICE_Label_Get(NULL, 0, 0)) - 5,
			ICE_Label_GetY(ICE_Label_Get(NULL, 0, 0))
		)
	);
	ICE_Debug_CameraControl();

	if (ICE_Input_Key(ICE_KEY_ESCAPE))
		ICE_State_Pause();
}

void inventory_destroy()
{

}