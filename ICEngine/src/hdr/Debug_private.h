﻿#ifndef DEF_ICE_DEBUG_PRIVATE
#define DEF_ICE_DEBUG_PRIVATE

#define ICE_DEBUG_GET_GAME_OBJECT extern ICE_Game game;

#ifndef NDEBUG
/**
 * \brief Stylised assert
 * \param Expr The condition you want to try
 * \param Msg A message you want to show
 */
#   define ICE_Assert(Expr, Msg) \
	ICE_Assert_(#Expr, Expr, __FILE__, __LINE__, Msg)
#else
#   define ICE_Assert(Expr, Msg) ;
#endif

void ICE_Assert_(const char* expr_str, int expr, const char* file, int line, const char* msg);

#endif