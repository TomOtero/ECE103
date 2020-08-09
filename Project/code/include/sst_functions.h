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
	void zeros(GameVariables *gameVars);
	void eventHandler(GameVariables *gameVars);
	void commandHelp(void);
	void intro(void);
	void clear(GameVariables *gameVars);
	void initialize(GameVariables *gameVars);
	void newQuadrant(GameVariables *gameVars);
	void _courseControl(GameVariables *gameVars);
	void _completeManeuver(GameVariables *gameVars);
	void _outOfBounds (GameVariables *gameVars);
	void maneuverEnergy(GameVariables *gameVars);
	void shortRangeScan(GameVariables *gameVars);
	void _longRangeScan (GameVariables *gameVars);
	void _phaserControl(GameVariables *gameVars);
	void photonTorpedoes(GameVariables *gameVars);
	void torpedoHit(GameVariables *gameVars);
	void damageControl(GameVariables *gameVars);
	void shieldControl(GameVariables *gameVars);
	void libraryComputer(GameVariables *gameVars);
	void _galacticRecord(GameVariables *gameVars);
	void _statusReport(GameVariables *gameVars);
	void _torpedoData(GameVariables *gameVars);
	void _navData(GameVariables *gameVars);
	void dirdistCalc(GameVariables *gameVars);
	void galaxyMap(GameVariables *gameVars);
	void computeVector(GameVariables *gameVars);
	void _direction_calc1(GameVariables *gameVars);
	void _direction_calc2(GameVariables *gameVars);
	void shipDestroyed(GameVariables *gameVars);
	void endOfTime(GameVariables *gameVars);
	void endMission(GameVariables *gameVars);
	void wonGame(GameVariables *gameVars);
	void endOfGame(GameVariables *gameVars);
	void _klingonsMove(GameVariables *gameVars);
	void klingonsShoot(GameVariables *gameVars);
	void _repairDamage(GameVariables *gameVars);
	void findEmptyPlace(GameVariables *gameVars);
	void insertInQuadrant(GameVariables *gameVars);
	void getDeviceName(GameVariables *gameVars);
	void stringCompare(GameVariables *gameVars);
	void quadrantName(GameVariables *gameVars);
	void midStr(char *a, char *b, int x, int y); 

	double findDistance(GameVariables *gameVars, int index);
	double RandomToOne(void);

	int findRandom(void);
	int getRandRange(int iSpread);
	int doubleToInt (double dubs);

	// char* MID(char* str1; int pos, int length);
#endif


