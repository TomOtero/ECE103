/*
	ECE 103 Engineering Programming
	Team 9: Tom Otero, Ed Rees, Kevin Deleon
	Last update: 07/25/20


*/
#ifndef GAME_VARS_H
#define GAME_VARS_H
#include "GameVariables.h"
#endif


#ifndef SST_FUN
#define SST_FUN

	void intro(void);
	void clear(GameVariables *gameVars);
	void initialize(GameVariables *gameVars);
	void eventHandler(GameVariables *gameVars);
	void commandHelp(void);
	void outOfBounds (GameVariables *gameVars);
	void longRangeScan (GameVariables *gameVars);
	void courseNavigation(GameVariables *gameVars);

	double findDistance(GameVariables *gameVars, int index);

	int findRandom(void);
	int get_rand(int iSpread);



#endif


