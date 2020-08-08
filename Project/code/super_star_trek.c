/*
	ECE 103 Engineering Programming
	Team 9: Tom Otero, Ed Rees, Kevin Deleon
	Last update: 08/02/20

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <stdbool.h>

#include "./include/sst_functions.h"

#ifndef GAME_VARS_H
#define GAME_VARS_H
#include "./include/GameVariables.h"
#endif



/*
NEEDED TO ACTIVATE 80-COLUMN TEXT MODE ON APPLE IIE
SUPER STARTREK - MAY 16,1978 - REQUIRES 24K MEMORY

       **** STAR TREK ****        ****
SIMULATION OF A MISSION OF THE STARSHIP ENTERPRISE,
AS SEEN ON THE STAR TREK TV SHOW.
ORIGINAL PROGRAM BY MIKE MAYFIELD, MODIFIED VERSION
PUBLISHED IN DEC'S "101 BASIC GAMES", BY DAVE AHL.
MODIFICATIONS TO THE LATTER (PLUS DEBUGGING) BY BOB
LEEDOM - APRIL & DECEMBER 1974,
WITH A LITTLE HELP FROM HIS FRIENDS . . .
COMMENTS, EPITHETS, AND SUGGESTIONS SOLICITED --
SEND TO : R. C. LEEDOM
          WESTINGHOUSE DEFENSE & ELECTRONICS SYSTEMS CNTR.
          BOX 746, M.S. 338
          BALTIMORE, MD  21203

CONVERTED TO MICROSOFT 8 K BASIC 3/16/78 BY JOHN GORDERS
LINE NUMBERS FROM VERSION STREK7 OF 1/12/75 PRESERVED AS
MUCH AS POSSIBLE WHILE USING MULTIPLE STATEMENTS PER LINE
SOME LINES ARE LONGER THAN 72 CHARACTERS; THIS WAS DONE
BY USING "?" INSTEAD OF "PRINT " WHEN ENTERING LINES
*/




void game(GameVariables *gameVars)
{
	/*
	The game function will hold the main game loop
	This will be called in the main loop to start a new game
	*/
	intro();
	initialize(gameVars);
	newQuadrant(gameVars);
	shortRangeScan(gameVars);
	gameVars->currGame = true;
	while(gameVars->currGame)
	{
		eventHandler(gameVars);
	}
}



int main()
{
	/*
	The Main Loop
	*/

	// Struct for game variables
	GameVariables gameVars;

	gameVars.running = true;
	while(gameVars.running)
	{
		game(&gameVars);
	}
	return EXIT_SUCCESS;
}
