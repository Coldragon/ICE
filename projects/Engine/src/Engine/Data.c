﻿#include "Data.h"
#include <stdlib.h>

#include "../Framework/Assert_.h"
#include "../Framework/Memory_.h"

#include "TypesCore.h"
#include "Scene_private.h"

extern ICE_Scene* ICE_GLOBJ_SCENE_CURRENT;

// Make a Data and create a pointer in the GAME->data array (return the pointer created)
void* ICE_Data_Insert_(ICE_Scene * state, ICE_DataID _size)
{
	if (!state)
		state = ICE_GLOBJ_SCENE_CURRENT;

	state->data_nb++;
	state->data = ICE_Realloc(state->data, sizeof(void*)*(state->data_nb));
	state->data[state->data_nb - 1] = ICE_Calloc(1, _size);
	void * _pointer = state->data[state->data_nb - 1];
	return _pointer;
}

/// Return pointer to a Data
void* ICE_Data_Get(ICE_Scene * scene_, ICE_ID data_nb_)
{
	if (!scene_)
		scene_ = ICE_GLOBJ_SCENE_CURRENT;

	void * _pointer;

	if (data_nb_ <= scene_->data_nb)
		_pointer = scene_->data[data_nb_];

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
void ICE_Data_Destroy(ICE_Scene * scene_, ICE_ID nb_data)
{
	if (!scene_)
		scene_ = ICE_GLOBJ_SCENE_CURRENT;

	void * _pointer;

	if (nb_data <= scene_->data_nb)
		_pointer = scene_->data[nb_data];

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
		ICE_Assert(_pointer != NULL, "Pointer is null so there is no data at this number");
	}

	ICE_Free(_pointer);
}

void ICE_Data_DestroyAll(ICE_Scene * scene_)
{
	if (!scene_)
		scene_ = ICE_GLOBJ_SCENE_CURRENT;

	for(ICE_ID i = 0; i < scene_->data_nb; i++)
	{
		ICE_Free(scene_->data[i]);
	}
	ICE_Free(scene_->data);
}