/*
	ECE 103 Engineering Programming
	Team 9: Tom Otero, Ed Rees, Kevin Deleon
	Last update: 08/02/20
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>

#include "sst_functions.h"



/* Standard Line Length */
 
#define MAXLEN     255
 
/* Standard Terminal Sizes */
 
#define MAXROW      24
#define MAXCOL      80
 
/* Standard Page Size */
 
#define MAXLINES    66




void eventHandler(GameVariables *gameVars)
{
	/*
	Initializes the game variables
	*/

	//Initialize Time
	printf("COMMAND? ");
	gets(gameVars->command);
  	printf("\n");
	if(strcmp(gameVars->command,"nav")==0)
	{
		printf("courseControl();\n");
		courseControl(gameVars);
	}
	else if (strcmp(gameVars->command,"srs")==0)
	{
		shortRangeScan(gameVars);		
	}
	else if (strcmp(gameVars->command,"lrs")==0)
	{
		longRangeScan(gameVars);		
	}
	else if (strcmp(gameVars->command,"pha")==0)
	{
		printf("pha function\n");		
	}
	else if (strcmp(gameVars->command,"tor")==0)
	{
		printf("tor function\n");		
	}
	else if (strcmp(gameVars->command,"she")==0)
	{
		printf("she function\n");		
	}
	else if (strcmp(gameVars->command,"com")==0)
	{
		printf("com function\n");		
	}
	else
	{
		commandHelp();
	}

}

void commandHelp(void)
{
      printf("Enter one of the following:\n\n");
      printf("  NAV  (TO SET COURSE)\n");
      printf("  SRS  (FOR SHORT RANGE SENSOR SCAN)\n");
      printf("  LRS  (FOR LONG RANGE SENSOR SCAN)\n");
      printf("  PHA  (TO FIRE PHASERS)\n");
      printf("  TOR  (TO FIRE PHOTON TORPEDOES)\n");
      printf("  SHE  (TO RAISE OR LOWER SHIELDS)\n");
      printf("  DAM  (FOR DAMAGE CONTROL REPORTS)\n");
      printf("  COM  (TO CALL ON LIBRARY-COMPUTER)\n");
      printf("  XXX  (TO RESIGN YOUR COMMAND)\n");
      printf("\n");
}


void intro(void)
{
	/*
	This function displays the intro message and asks if user
	wants to display the instructions.

	TODO: Update the instructions to not be "test.txt"

	*/
	char resp[1];

	printf ("\n");
	printf (" *************************************\n");
	printf (" *                                   *\n");
	printf (" *                                   *\n");
	printf (" *      * * Super Star Trek * *      *\n");
	printf (" *                                   *\n");
	printf (" *                                   *\n");
	printf (" *************************************\n\n");

	printf("\nDo you need instructions (y/n): ");

	gets(resp);

	printf ("\n");
	if (resp[0] == 'y' || resp[0] == 'Y')
	{	
		FILE *file;
		char fileC;	
		file = fopen("stinstr.txt","r");
		while((fileC=fgetc(file))!=EOF)
		{
			printf("%c",fileC);
		}
		printf("\n\n");
	}
	// Print the Enterprise	
	printf("                                 ,------*------,\n");
	printf("                 ,-------------   '---  ------'\n");
	printf("                  '-------- --'      / /\n");
	printf("                      ,---' '-------/ /--,\n");
	printf("                       '----------------'\n");
	printf("                 THE USS ENTERPRISE --- NCC-1701\n");

}


void clear(GameVariables *gameVars)
{
	//Initializing time
	gameVars->stardateCurr		=(int)(rand()*20+20)*100;  	// T
	gameVars->stardateStart		=gameVars->stardateCurr;	// T0
	gameVars->stardateEnd 		= 25+(int)(rand()*10); 	 	// T9

	//Initialize general
	gameVars->dockFlag 			 = 0;						// D0
	gameVars->startEnergy 		 = 3000;					// E
	gameVars->currEnergy 		 = gameVars->startEnergy;	// E0
	gameVars->torpCap 			 = 10;						// P
	gameVars->torpLeft 			 = gameVars->torpCap;		// P0
	gameVars->shields 			 = 0;						// S
	gameVars->klingPow 			 = 200;						// S9
	gameVars->klingLeft 		 = 0;						// K9
	gameVars->starbaseTotal 	 = 2;						// B9

	//Initialize strings
	strcpy(gameVars->tempStr[0], "");
	strcpy(gameVars->tempStr[1], "is");
	const char tempCommandList[9][6] = {{"nav"},{"srs"},{"lrs"},
										{"pha"},{"tor"},{"she"},
										{"dam"},{"com"},{"xxx"}};
	memcpy(gameVars->commandList, tempCommandList, sizeof tempCommandList); // 710

	// Initializing arrays // 820
	memset(gameVars->galaxy,0,sizeof gameVars->galaxy);
	//memset(gameVars->galaxyRecord,0,sizeof gameVars->galaxyRecord);
	memset(gameVars->klingData,0,sizeof gameVars->klingData);


}


void initialize(GameVariables *gameVars)
{
	// Clear game vars to default
	clear(gameVars);

	// Initialize Enterprise
	gameVars->entQuad[0] = findRandom();
	gameVars->entQuad[1] = findRandom();
	gameVars->entSect[0] = (double)findRandom();
	gameVars->entSect[1] = (double)findRandom();
	memset(gameVars->damage,0,sizeof gameVars->damage);
	static const long tempArray[9][2] = {{0,1}, {-1,1}, {-1,0},		// 530 - 600
	   								     {-1,-1}, {0-1}, {1,-1},
								         {1,0}, {1,1}, {0,1}};

	memcpy(gameVars->locationMove, tempArray, sizeof tempArray);
	

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		  {
		  	gameVars->klingQuad = 0;
            gameVars->galaxyRecord[i][j] = 0;
		    gameVars->tempPos[0] = getRand(100);
		    if (gameVars->tempPos[0]  > 98)
		      gameVars->klingQuad = 3;
		    else if (gameVars->tempPos[0]  > 95)
		      gameVars->klingQuad = 2;
		    else if (gameVars->tempPos[0]  > 80)
		      gameVars->klingQuad = 1;

		    gameVars->klingLeft = gameVars->klingLeft + gameVars->klingQuad;
		    gameVars->starbaseQuadrant = 0;

		    if (getRand(100) > 96)
		      gameVars->starbaseQuadrant = 1;

		    gameVars->starbaseTotal = gameVars->starbaseTotal + 
		    						gameVars->starbaseQuadrant;

		    gameVars->galaxy[i][j] = gameVars->klingQuad * 100 + 
		    						gameVars->starbaseQuadrant * 10 + findRandom();
		  }
	}
	if (gameVars->klingLeft > gameVars->stardateEnd)
	{
    	gameVars->stardateEnd = gameVars->klingLeft + 1;
	}
  	if (gameVars->starbaseTotal == 0)
    {
      	if (gameVars->galaxy[gameVars->entQuad[0]][gameVars->entQuad[1]] < 200)
        {
	  		gameVars->galaxy[gameVars->entQuad[0]][gameVars->entQuad[1]] = 
	  			gameVars->galaxy[gameVars->entQuad[0]][gameVars->entQuad[1]] + 100;
          	gameVars->klingLeft;
        }

	  	gameVars->galaxy[gameVars->entQuad[0]][gameVars->entQuad[1]] = 
	  			gameVars->galaxy[gameVars->entQuad[0]][gameVars->entQuad[1]] + 100;
	  	gameVars->starbaseTotal++;

	  	gameVars->entQuad[0] = findRandom();
  		gameVars->entQuad[1] = findRandom();
    }

  	gameVars->klingStart = gameVars->klingLeft;

  	if (gameVars->starbaseTotal != 1)
    {
      	strcpy(gameVars->tempStr[0], "s");
      	strcpy(gameVars->tempStr[1], "are");
    }

	printf("YOUR ORDERS ARE AS FOLLOWS :\n\n");
	printf("   DESTROY THE %d KLINGON WARSHIPS WHICH HAVE INVADED\n", gameVars->klingLeft);
	printf("   THE GALAXY BEFORE THEY CAN ATTACK FEDERATION HEADQUARTERS\n");
	printf("   ON STARDATE %d. THIS GIVES YOU %d DAYS. THERE %s\n",
	gameVars->stardateStart + gameVars->stardateEnd, gameVars->stardateEnd, gameVars->tempStr[1]);
	printf(" %d STARBASE%s IN THE GALAXY FOR RESUPPLYING YOUR SHIP.\n\n",
	gameVars->starbaseTotal, gameVars->tempStr[0]);

	printf("HIT ANY KEY WHEN READY TO ACCEPT COMMAND ");
	getchar();
}


void newQuadrant(GameVariables *gameVars)
{
	int i;

	gameVars->tempQuadCoord[0] = gameVars->entQuad[0];
	gameVars->tempQuadCoord[1] = gameVars->entQuad[1];
	gameVars->klingQuad = 0;
	gameVars->starbaseQuadrant = 0;
	gameVars->stars = 0;
	gameVars->quadName = 0; 
	gameVars->repairTime = (double) getRand(100) / 100 / 50;
	gameVars->galaxyRecord[gameVars->tempQuadCoord[0]][gameVars->tempQuadCoord[1]] = 
			gameVars->galaxy[gameVars->entQuad[0]][gameVars->entQuad[1]];

	if (gameVars->entQuad[0] >= 1 && gameVars->entQuad[0] <= 8 && 
		gameVars->entQuad[1] >= 1 && gameVars->entQuad[1] <= 8)
	{
	  quadrantName(gameVars);

	  if (gameVars->stardateStart != gameVars->stardateCurr)
	    printf("NOW ENTERING %s QUADRANT . . .\n\n", gameVars->strResults);
	  else
	    {
	      printf("\nYOUR MISSION BEGINS WITH YOUR STARSHIP LOCATED\n");
	      printf("IN THE GALACTIC QUADRANT %s.\n\n", gameVars->strResults);
	    }
	}

	gameVars->klingQuad = (int)(gameVars->galaxy[gameVars->entQuad[0]][gameVars->entQuad[1]] * .01);
	gameVars->starbaseQuadrant = (int)(gameVars->galaxy[gameVars->entQuad[0]][gameVars->entQuad[1]] * .1 - 10 * gameVars->klingQuad);
	gameVars->stars = gameVars->galaxy[gameVars->entQuad[0]][gameVars->entQuad[1]] - 100 * gameVars->klingQuad - 10 * gameVars->starbaseQuadrant;

	if (gameVars->klingQuad > 0)
	{
	  	printf("COMBAT AREA  CONDITION RED\n");
	  	if (gameVars->shields < 200)
	  	{
	    	printf("SHIELDS DANGEROUSLY LOW\n");
		}
	}

	for (i = 0; i < 3; i++)
	{
	  	gameVars->klingData[i][0] = 0;
	  	gameVars->klingData[i][1] = 0;
	  	gameVars->klingData[i][2] = 0;
	}

	for (i = 0; i <= 192; i++)
	{
		gameVars->quadDisp[i] = ' ';
	}
	gameVars->quadDisp[193] = '\0';

	//Position Enterprise
	strcpy(gameVars->objInSector, "<*>");
	gameVars->tempSectCoord[0] = (int)gameVars->entSect[0];
	gameVars->tempSectCoord[1] = (int)gameVars->entSect[1];
	insertInQuadrant(gameVars);

	//Position Klingons
	if (gameVars->klingQuad > 0)
	{
	  for (i = 1; i <= gameVars->klingQuad; i++)
	    {
	      	findEmptyPlace(gameVars);

	      	strcpy(gameVars->objInSector, "+K+");
      		gameVars->tempSectCoord[0] = gameVars->tempPos[0];
	      	gameVars->tempSectCoord[1] = gameVars->tempPos[1];
	      	insertInQuadrant(gameVars);

	      	gameVars->klingData[i][1] = gameVars->tempPos[0];
	      	gameVars->klingData[i][2] = gameVars->tempPos[1];
	      	gameVars->klingData[i][3] = 100 + getRand(200);
	    }
	}

	//Position Starbases
	if (gameVars->starbaseQuadrant > 0)
	{
	  findEmptyPlace(gameVars);

	  strcpy(gameVars->objInSector, ">!<");
  		gameVars->tempSectCoord[0] = gameVars->tempPos[0];
	  	gameVars->tempSectCoord[1] = gameVars->tempPos[1];
	  insertInQuadrant(gameVars);

	  gameVars->starbaseLocation[0] = gameVars->tempPos[0];
	  gameVars->starbaseLocation[1] = gameVars->tempPos[1];
	}

	for (i = 1; i <= gameVars->stars; i++)
	{
	  findEmptyPlace(gameVars);

	  strcpy(gameVars->objInSector, " * ");
  		gameVars->tempSectCoord[0] = gameVars->tempPos[0];
	  	gameVars->tempSectCoord[1] = gameVars->tempPos[1];
	  insertInQuadrant(gameVars);
	}
}





void courseControl(GameVariables *gameVars) //2290 REM COURSE CONTROL BEGINS HERE
{
	int i;
	/* @@@ int c2, c3, q4, q5; */
	int q4, q5; 			// No idea what these are used for...
	char temp[6];
	double course;
	strcpy(gameVars->tempStr[0], "8");

	printf("COURSE (0-9): ");

	gets(temp);

	printf("\n");

	course = atof(temp);

	if (course == 9.0)
	course = 1.0;

	if (course < 0 || course > 9.0)
	{
	  printf("LT. SULU REPORTS, 'INCORRECT COURSE DATA, SIR!'\n");
	  return;
	}

	if (gameVars->damage[1] < 0.0)
	strcpy(gameVars->tempStr[0], "0.2");

	printf("WARP FACTOR (0-%s): ", gameVars->tempStr[0]);

	gets(temp);

	printf("\n");

	gameVars->warpFactor = atof(temp);

	if (gameVars->damage[1] < 0.0 && gameVars->warpFactor > 0.21)
	{
	  printf("WARP ENGINES ARE DAMAGED.  MAXIUM SPEED = WARP 0.2");
	  return;
	}

	if (gameVars->warpFactor <= 0.0)
	return;

	if (gameVars->warpFactor > 8.1)
	{
	  printf("CHIEF ENGINEER SCOTT REPORTS 'THE ENGINES WON'T TAKE WARP %4.1f!'\n", gameVars->warpFactor);
	  return;
	}

	gameVars->n = cint(gameVars->warpFactor * 8.0); //N=INT(W1*8+.5)

	if (gameVars->currEnergy - gameVars->n < 0)
	{
	  printf("ENGINEERING REPORTS   'INSUFFICIENT ENERGY AVAILABLE for maneuvering");
	  printf("                       FOR MANEUVERING AT WARP %4.1f!'\n", gameVars->warpFactor);

	  if (gameVars->shields >= gameVars->n && gameVars->damage[7] >= 0.0)
	    {
	      printf("DEFLECTOR CONTROL ROOM ACKNOWLEDGES\n");
	      printf("  %d UNITS OF ENERGY PRESENTLY DEPLOYED TO SHIELDS.\n", gameVars->shields);
	    }

	  return;
	}
	//2580 REM KLINGONS MOVE/FIRE ON MOVING STARSHIP
	klingons_move(gameVars);

	repairDamage(gameVars);

	strcpy(gameVars->objInSector, "   ");
	gameVars->tempSectCoord[0] = (int)gameVars->entSect[0];
	gameVars->tempSectCoord[1] = (int)gameVars->entSect[1];
	insertInQuadrant(gameVars);

	gameVars->navX1 = gameVars->locationMove[1][(int)course] + 
		(gameVars->locationMove[1][(int)course + 1] - 
		gameVars->locationMove[1][(int)course]) * (course - (int)course);
	
	gameVars->navX2 = gameVars->locationMove[2][(int)course] + 
		(gameVars->locationMove[2][(int)course + 1] - 
		gameVars->locationMove[2][(int)course]) * (course - (int)course);

	gameVars->navX = gameVars->entSect[0];
	gameVars->navY = gameVars->entSect[1];
	q4 = gameVars->entQuad[0];
	q5 = gameVars->entQuad[0];

	for (i = 1; i <= n; i++)
	{
		gameVars->entSect[0] = gameVars->entSect[0] + gameVars->navX1;
	  	gameVars->entSect[1] = gameVars->entSect[1] + gameVars->navX2;

	  	/* @@@ z1 = cint(s1); */
		gameVars->tempSectCoord[0] = (int)gameVars->entSect[0];
		/* @@@ z2 = cint(s2); */
		gameVars->tempSectCoord[1] = (int)gameVars->entSect[1];

	  if (z1 < 1 || z1 >= 9 || z2 < 1 || z2 >= 9)
	    {
	      	outOfBounds(gameVars);
	      	complete_maneuver(gameVars);
	      	return;
	    }

	  stringCompare(gameVars);

	  //3060 REM BEGIN MOVING STARSHIP
	  if (z3 != 1) /* Sector not empty */
	    {
	      	gameVars->entSect[0] = gameVars->entSect[0] + gameVars->navX1;
	  		gameVars->entSect[1] = gameVars->entSect[1] + gameVars->navX2;
	      	printf("WARP ENGINES SHUT DOWN AT SECTOR ");
	      	printf("%d, %d DUE TO BAD NAVAGATION\n\n", 
	      			gameVars->tempSectCoord[0], gameVars->tempSectCoord[1]);
	      	i = gameVars->n + 1;
	    }
	}

	complete_maneuver();
}

//3490 REM EXCEEDED QUADRANT LIMITS
void outOfBounds (GameVariables *gameVars)
{
	int outOfBoundsFlag = 0;
	gameVars->n = (int)(gameVars->warpFactor * 8.0);
	
	gameVars->navX = (8 * gameVars->entQuad[0]) + 
					  gameVars->navX + (gameVars->n * gameVars->navX1); // not sure where the "n" is being pulled from
	gameVars->navY = (8 * gameVars->entQuad[1]) + 
					  gameVars->navY + (gameVars->n * gameVars->navY); // again not sure where the n is pulled
	
	gameVars->entQuad[0] = gameVars->navX/8;
	gameVars->entQuad[1] = gameVars->navY/8;
	gameVars->entSect[0] = gameVars->navX - gameVars->entQuad[0]/8;
	gameVars->entSect[1] = gameVars->navY - gameVars->entQuad[1]/8;
	
	if (gameVars->entSect[0] == 0)
	{
		gameVars->entQuad[0] = gameVars->entQuad[0] - 1;
		gameVars->entSect[0] = 8.0;
	}
	
	if (gameVars->entSect[1] == 0)
	{
		gameVars->entQuad[1] = gameVars->entQuad[1] - 1;
		gameVars->entSect[1] = 8.0;
	}
	
	if (gameVars->entQuad[0] < 1)
	{
		outOfBoundsFlag = 1;
		gameVars->entQuad[0] = 1;
		gameVars->entSect[0] = 1.0;
	}
	
	if (gameVars->entQuad[1] < 1)
	{
		outOfBoundsFlag = 1;
		gameVars->entQuad[1] = 1;
		gameVars->entSect[1] = 1.0;
	}
	
	if (gameVars->entQuad[0] > 8)
	{
		outOfBoundsFlag = 1;
		gameVars->entQuad[0] = 8;
		gameVars->entSect[0] = 8.0;
	}
	
	if (gameVars->entQuad[1] > 8)
	{
		outOfBoundsFlag = 1;
		gameVars->entQuad[1] = 8;
		gameVars->entSect[1] = 8.0;
	}
	
    if (outOfBoundsFlag != 0)
	{
		printf("LT. UHURA REPORTS MESSAGE FROM STARFLEET COMMAND : \n");
		printf("  'PERMISSION TO ATTEMPT CROSSING OF GALACTIC PERIMETER\n");
		printf("   IS HEREBY *DENIED*.  SHUT DOWN YOUR ENGINES.'\n");
		printf("   CHIEF ENGINEER SCOTT REPORTS:  'WARP ENGINES SHUT DOWN\n");
		printf("   AT SECTOR %.1lf,%.1lf OF QUADRANT %d, %d.'", 
			gameVars->entSect[0], gameVars->entSect[1], 
			gameVars->entQuad[0], gameVars->entQuad[1]);
	}

	maneuverEnergy(GameVariables *gameVars);
	if (gameVars->stardateCurr > gameVars->stardateStart + gameVars->stardateEnd)
    	endOfTime(gameVars);
		gameVars->stardateCurr = gameVars->stardateCurr + 1;
		newQuadrant(gameVars);
}

//3900 REM MANEUVER ENERGY S/R **
void maneuverEnergy(GameVariables *gameVars)
{
  	gameVars->currEnergy = gameVars->currEnergy - gameVars->n - 10;

  	if (gameVars->currEnergy >= 0)
    	return;

  	printf("SHIELD CONTROL SUPPLIES ENERGY TO COMPLETE THE MANEUVER.\n\n");
  	gameVars->shields = gameVars->shields + gameVars->currEnergy;
  	gameVars->currEnergy = 0;

  	if (gameVars->shields <= 0)
  	{
    	gameVars->shields = 0;
    }
}	

//6420 REM SHORT RANGE SENSOR SCAN & STARTUP SUBROUTINE
void shortRangeScan(GameVariables *gameVars)
{
	int i, j;
	strcpy(gameVars->condition, "GREEN");

 	if (gameVars->currEnergy < gameVars->startEnergy * .1)
 	{
    	strcpy(gameVars->condition, "YELLOW");
 	}

	if (gameVars->klingQuad > 0)
	{
	    strcpy(gameVars->condition, "*RED*");
	}

	//Clear dockFlag
	gameVars->dockFlag = 0;

  /* @@@ for (i = s1 - 1; i <= s1 + 1; i++) */
  	for (i = (int)(gameVars->entSect[0]); i <= (int)(gameVars->entSect[0]); i++)
  	{
    /* @@@ for (j = s2 - 1; j <= s2 + 1; j++) */
    	for (j = (int)(gameVars->entSect[1]); j <= (int)(gameVars->entSect[1]); j++)
      	{	
	      	if (i >= 1 && i <= 8 && j >= 1 && j <= 8)
	        {
	          strcpy(gameVars->objInSector, ">!<");
	          gameVars->tempSectCoord[0] = i;
	          gameVars->tempSectCoord[1] = j;
	          stringCompare(gameVars);
	          if (gameVars->compare == 1)
	            {
	              gameVars->dockFlag = 1;
	              strcpy(gameVars->condition, "DOCKED");
	              gameVars->currEnergy = gameVars->startEnergy;
	              gameVars->torpLeft = gameVars->torpCap;
	              printf("Shields dropped for docking purposes.\n");
	              gameVars->shields = 0;
	            }
	        }
	    }
  	}
  if (gameVars->damage[2] < 0.0)
    {
      printf("\n*** Short Range Sensors are out ***\n");
      return;
    }

  printf("------------------------\n");
  for (i = 0; i < 8; i++)
    {
      for (j = 0; j < 24; j++)
        putchar(gameVars->quadDisp[i * 24 + j]); 

      if (i == 0)
    printf("    Stardate            %d\n", (int) gameVars->stardateCurr);
      if (i == 1)
    printf("    Condition           %s\n", gameVars->condition);
      if (i == 2)
    printf("    Quadrant            %d, %d\n",  gameVars->entQuad[0], gameVars->entQuad[1]);
      if (i == 3)
    /* @@@ printf("    Sector              %d, %d\n", cint(s1), cint(s2)); */
    printf("    Sector              %d, %d\n", (int)gameVars->entSect[0], (int)gameVars->entSect[1]);
      if (i == 4)
    printf("    Photon Torpedoes    %d\n", gameVars->torpLeft);
      if (i == 5)
    printf("    Total Energy        %d\n", gameVars->currEnergy + gameVars->startEnergy);
      if (i == 6)
    printf("    Shields             %d\n", gameVars->shields);
      if (i == 7)
    printf("    Klingons Remaining  %d\n", gameVars->klingLeft);
    }
  printf("------------------------\n\n");

  return;
}

//3990 REM LONG RANGE SENSOR SCAN CODE
void longRangeScan (GameVariables *gameVars)
{
if (gameVars->damage[3] < 0)
	{
	printf("Long Range Sensors are inopperable");
	}
	
printf("Long Range Scan for Quadrant %d, %d", gameVars->entQuad[0], gameVars->entQuad[1]);

printf("    -------------------");

for (int i = gameVars->entQuad[0] -1; i <= gameVars->entQuad[0] + 1; i++)
	{
	for (int j = gameVars->entQuad[1] - 1; j <= gameVars->entQuad[1] + 1; j++)
		{
		if (((i > 0) && (i < 9)) && ((j > 0) && (j < 9)))
			{
			gameVars->galaxyRecord[i][j] = gameVars->galaxy[i][j];
			printf("%d :",gameVars->galaxyRecord[i][j]);
			}
		
		else 
			{
			printf(" *** : ");
			}
		}
		printf("\n");
	}
printf("    -------------------");	

}


void klingonsMove(GameVariables *gameVars)
{
  int i;

  for (i = 0; i < 3; i++)
    {
      if (gameVars->klingData[i][2] > 0)
        {
          strcpy(gameVars->objInSector, "   ");
          z1 = gameVars->klingData[i][0];
          z2 = gameVars->klingData[i][1];
          insertInQuadrant(gameVars);

          findEmptyPlace(gameVars);

          gameVars->klingData[i][0] = z1;
          gameVars->klingData[i][1] = z2;
          strcpy(gameVars->objInSector, "+K+");
          insertInQuadrant(gameVars);
        }
    }

  klingons_shoot(gameVars);
}

void klingonsShoot(GameVariables *gameVars)
{
	int hit, i;

	if (gameVars->klingQuad <= 0)
		return;

	if (gameVars->dockFlag != 0)
	{
	  	printf("Starbase shields protect the Enterprise\n\n");
	  	return;
	}

	for (i = 0; i < 3; i++)
	{
	  	if (gameVars->klingData[i][2] > 0)
    	{
	      	hit = (int) ((gameVars->klingData[i][2] / findDistance(i)) * (2 + rnd()));
	      	gameVars->shields = gameVars->shields - hit;
	      	/* @@@ gameVars->klingData[i][3] = gameVars->klingData[i][3] / (3 + rnd()); */
	      	gameVars->klingData[i][2] = (int)(gameVars->klingData[i][2] / (3 + rnd()));

	      	printf("%d unit hit on Enterprise from sector ", hit);
	      	printf("%d, %d\n", gameVars->klingData[i][1], gameVars->klingData[i][2]);

	          	if (gameVars->shields <= 0)
	            {
	              	printf("\n");
	              	shipDestroyed();
	            }

          printf("    <Shields down to %d units>\n\n", gameVars->shields);

	      	if (hit >= 20)
	        {
	          	if (rnd() <= 0.6 || (hit / gameVars->shields) > 0.2)
	            {
	              	gameVars->tempPos[0] = findRandom();
	        	  	gameVars->damage[gameVars->tempPos[0]] = gameVars->damage[gameVars->tempPos[0]] - (hit / gameVars->shields) - (0.5 * rnd());

	              	getDeviceName(gameVars);

	              	printf("Damage Control reports\n");
	              	printf("   '%s' damaged by hit\n\n", gameVars->strResults);
	            }
	        }
   	 	}
	}
} 

void repairDamage(GameVariables *gameVars)
{
	int i;
	double repairFactor; 

	repairFactor = gameVars->warpFactor;

	if (gameVars->warpFactor >= 1.0)
	{
		repairFactor = gameVars->warpFactor / 10;
	}

	for (i = 1; i <= 8; i++)
	{
	  	if (gameVars->damage[i] < 0.0)
    	{
	      	gameVars->damage[i] = gameVars->damage[i] + repairFactor;
	      	if (gameVars->damage[i] > -0.1 && d[i] < 0)
	        {
	        	gameVars->damage[i] = -0.1;
	        }
	      	else if (gameVars->damage[i] >= 0.0)
	        {
	        	if (gameVars->damageRepFlag != 1)
	     	   	{
	            	gameVars->damageRepFlag = 1;
	        	}
	          	printf("Damage Control report:\n");
	          	gameVars->tempPos[0] = i;
	          	getDeviceName(gameVars);
	          	printf("    %s repair completed\n\n", gameVars->strResults);
	        }
	    }
	}

	if (rnd() <= 0.2)
	{
	  	gameVars->tempPos[0] = findRandom();

	  	if (rnd() < .6)
	    {
	      	gameVars->damage[gameVars->tempPos[0]] = gameVars->damage[gameVars->tempPos[0]] - (rnd() * 5.0 + 1.0);
	      	printf("Damage Control report:\n");
	      	getDeviceName(gameVars);
	      	printf("    %s damaged\n\n", gameVars->strResults);
	    }
	  	else
	    {
	      gameVars->damage[gameVars->tempPos[0]] = gameVars->damage[gameVars->tempPos[0]] + (rnd() * 3.0 + 1.0);
	      printf("Damage Control report:\n");
	      getDeviceName(gameVars);
	      printf("    %s state of repair improved\n\n", gameVars->strResults);
	    }
	}
}


void findEmptyPlace(GameVariables *gameVars)
{
  /* @@@ while (z3 == 0) this is a nasty one.*/
  do
    {
      gameVars->tempPos[0] = findRandom();
      gameVars->tempPos[1] = findRandom();

      strcpy(gameVars->objInSector, "   ");

    	gameVars->tempSectCoord[0] = gameVars->tempPos[0];
		gameVars->tempSectCoord[1] = gameVars->tempPos[1];

      stringCompare(gameVars);
    } while (gameVars->compare == 0);

  gameVars->compare = 0;
}


void insertInQuadrant(GameVariables *gameVars)
{
	int i, j = 0;

  /* @@@ s8 = ((z2 - 1) * 3) + ((z1 - 1) * 24) + 1; */
	gameVars->quadIndex = ((int)(gameVars->tempSectCoord[1] - 0.5) * 3) + ((int)(gameVars->tempSectCoord[0] - 0.5) * 24) + 1;

	for (i = gameVars->quadIndex - 1; i <= gameVars->quadIndex + 1; i++)
	{
    	gameVars->quadDisp[i] = gameVars->objInSector[j++];
    }
}

void getDeviceName(GameVariables *gameVars)
{
	static char *deviceName[] = {
	    "", "Warp Engines","Short Range Sensors","Long Range Sensors",
	    "Phaser Control","Photon Tubes","Damage Control","Sheild Control",
	    "Library-Computer"};

  	if (gameVars->tempPos[0] < 0 || gameVars->tempPos[0] > 8)
	{
    	gameVars->tempPos[0] = 0;
	}

  	strcpy(gameVars->strResults, deviceName[r1]);
	return;
}

void stringCompare(GameVariables *gameVars)
{
	int i;
	char temp[4];

	gameVars->tempSectCoord[0] = (int)(gameVars->tempSectCoord[0] + 0.5);
	gameVars->tempSectCoord[1] = (int)(gameVars->tempSectCoord[1] + 0.5);

	gameVars->quadIndex = ((gameVars->tempSectCoord[1] - 1) * 3) + ((gameVars->tempSectCoord[0] - 1) * 24) + 1;

	midStr(temp, gameVars->quadDisp, gameVars->quadIndex, 3);

	i = strncmp(temp, gameVars->quadDisp, 3);

	if (i == 0)
	{
		gameVars->compare = 1;
	}
	else
	{
		gameVars->compare = 0;
	}

	return;
}


void quadrantName(GameVariables *gameVars)
{
    static char * quadName[] = {"","Antares","Rigel","Procyon","Vega",
    "Canopus","Altair","Sagittarius","Pollux","Sirius","Deneb","Capella",
    "Betelgeuse","Aldebaran","Regulus","Arcturus","Spica"};

  	static char * sectName[] = {""," I"," II"," III"," IV"};

  	if (gameVars->tempQuadCoord[0] < 1 || gameVars->tempQuadCoord[0] > 8 || gameVars->tempQuadCoord[1] < 1 || gameVars->tempQuadCoord[1] > 8)
    {	
    	strcpy(gameVars->strResults, "Unknown");
    }
  	if (gameVars->tempQuadCoord[1] <= 4)
    {
    	strcpy(gameVars->strResults, quadName[gameVars->tempQuadCoord[0]]);
    }
  	else
    {	
    	strcpy(gameVars->strResults, quadName[gameVars->tempQuadCoord[0]+8]);
    }
  	if (gameVars->quadName != 1)
    {
     	if (gameVars->tempQuadCoord[1] > 4)
      	{
	      	gameVars->tempQuadCoord[1] = gameVars->tempQuadCoord[1] - 4;
	      	strcat(gameVars->strResults, sectName[gameVars->tempQuadCoord[1]]);
      	}
    }
}

void midStr(char *a, char *b, int x, int y)
{
	/* 
		MID$( sexpr, aexpr [, aexpr] )
		Substring of (string, start character, length)
		https://www.calormen.com/jsbasic/reference.html

		Due to its effectiveness, this function is a direct copy from:

		* startrek.c
		*
 		* Super Star Trek Classic (v1.1)
 		* Retro Star Trek Game 
 		* C Port Copyright (C) 1996  <Chris Nystrom>
	*/

  --x;
  y += x;

  /* @@@ while (x < y && x <= strlen(b)) */
  while (x < y && x <= (int)strlen(b))
    *a++ = *(b + x++);

  *a = '\0';
}



double findDistance(GameVariables *gameVars, int index)
{
	double dist = 0.0;
	dist = sqrt(pow((gameVars->klingData[index][0]-gameVars->entSect[0]),2)+
			pow((gameVars->klingData[index][1]-gameVars->entSect[1]),2));

	return dist;
}

double rnd(void)
{
	/* 	Returns an integer from 1 to iSpread 
		
		Due to its effectiveness, this function is a direct copy from:

		* startrek.c
		*
 		* Super Star Trek Classic (v1.1)
 		* Retro Star Trek Game 
 		* C Port Copyright (C) 1996  <Chris Nystrom>
	*/
  double d;

  d = rand() / (double) RAND_MAX;
  
  return d;
}



int findRandom(void)
{
	return(getRand(8));
}


int getRand(int iSpread)
{
	/* 	Returns an integer from 1 to iSpread 
		
		Due to its effectiveness, this function is a direct copy from:

		* startrek.c
		*
 		* Super Star Trek Classic (v1.1)
 		* Retro Star Trek Game 
 		* C Port Copyright (C) 1996  <Chris Nystrom>
	*/
  	return((rand() % iSpread) + 1);
}

int cint (double d)
{
	/* 	Round off floating point numbers instead of truncating 
		
		Due to its effectiveness, this function is a direct copy from:

		* startrek.c
		*
 		* Super Star Trek Classic (v1.1)
 		* Retro Star Trek Game 
 		* C Port Copyright (C) 1996  <Chris Nystrom>
	*/
  	int i;

  	i = (int) (d + 0.5);

  	return(i);
}

