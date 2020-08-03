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
	void completeManeuver(GameVariables *gameVars);
	void outOfBounds (GameVariables *gameVars);
	void maneuverEnergy(GameVariables *gameVars);
	void shortRangeScan(GameVariables *gameVars);
	void longRangeScan (GameVariables *gameVars);
	void damageControl(GameVariables *gameVars);
	void libraryComputer(GameVariables *gameVars);
	void galacticRecord(GameVariables *gameVars);
	void statusReport(GameVariables *gameVars);
	void torpedoData(GameVariables *gameVars);
	void navData(GameVariables *gameVars);
	void dirdistCalc(GameVariables *gameVars);
	void galaxyMap(GameVariables *gameVars);
	void computeVector(GameVariables *gameVars);
	void sub1(GameVariables *gameVars);
	void sub2(GameVariables *gameVars);
	void shipDestroyed(GameVariables *gameVars);
	void endOfTime(GameVariables *gameVars);
	void resignCommision(GameVariables *gameVars);
	void wonGame(GameVariables *gameVars);
	void endOfGame(GameVariables *gameVars);
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


