/*
	ECE 103 Engineering Programming
	Team 9: Tom Otero, Ed Rees, Kevin Deleon
	Last update: 08/02/20
*/


#ifndef GAME_VARS_H
#define GAME_VARS_H
#include "GameVariables.h"
#endif


#ifndef SST_FUN
#define SST_FUN
	
	void eventHandler(GameVariables *gameVars);
	void commandHelp(void);
	void intro(void);
	void clear(GameVariables *gameVars);
	void initialize(GameVariables *gameVars);
	void newQuadrant(GameVariables *gameVars);
	void courseControl(GameVariables *gameVars);
	void outOfBounds (GameVariables *gameVars);
	void shortRangeScan(GameVariables *gameVars);
	void longRangeScan (GameVariables *gameVars);
	void klingonsMove(GameVariables *gameVars);
	void klingonsShoot(GameVariables *gameVars);
	void repairDamage(GameVariables *gameVars);
	void findEmptyPlace(GameVariables *gameVars);
	void insertInQuadrant(GameVariables *gameVars);
	void getDeviceName(GameVariables *gameVars);
	void stringCompare(GameVariables *gameVars);
	void quadrantName(GameVariables *gameVars);
	void midStr(char *a, char *b, int x, int y); 

	double findDistance(GameVariables *gameVars, int index);
	double rnd(void);

	int findRandom(void);
	int getRand(int iSpread);
	int cint (double d);



#endif


