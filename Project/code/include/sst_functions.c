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
		    gameVars->tempPos[0] = get_rand(100);
		    if (gameVars->tempPos[0]  > 98)
		      gameVars->klingQuad = 3;
		    else if (gameVars->tempPos[0]  > 95)
		      gameVars->klingQuad = 2;
		    else if (gameVars->tempPos[0]  > 80)
		      gameVars->klingQuad = 1;

		    gameVars->klingLeft = gameVars->klingLeft + gameVars->klingQuad;
		    gameVars->starbaseQuadrant = 0;

		    if (get_rand(100) > 96)
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

	printf("Your orders are as follows:\n\n");
	printf("   Destroy the %d Klingon warships which have invaded\n", gameVars->klingLeft);
	printf(" the galaxy before they can attack Federation Headquarters\n");
	printf(" on stardate %d. This gives you %d days. There %s\n",
	gameVars->stardateStart + gameVars->stardateEnd, gameVars->stardateEnd, gameVars->tempStr[1]);
	printf(" %d starbase%s in the galaxy for resupplying your ship.\n\n",
	gameVars->starbaseTotal, gameVars->tempStr[0]);

	printf("Hit any key to accept command. ");
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
	gameVars->repairTime = (double) get_rand(100) / 100 / 50;
	gameVars->galaxyRecord[gameVars->tempQuadCoord[0]][gameVars->tempQuadCoord[1]] = 
			gameVars->galaxy[gameVars->entQuad[0]][gameVars->entQuad[1]];

	if (gameVars->entQuad[0] >= 1 && gameVars->entQuad[0] <= 8 && 
		gameVars->entQuad[1] >= 1 && gameVars->entQuad[1] <= 8)
	{
	  quadrantName(gameVars);

	  if (gameVars->stardateStart != gameVars->stardateCurr)
	    printf("Now entering %s quadrant...\n\n", gameVars->strResults);
	  else
	    {
	      printf("\nYour mission begins with your starship located\n");
	      printf("in the galactic quadrant %s.\n\n", gameVars->strResults);
	    }
	}

	gameVars->klingQuad = (int)(gameVars->galaxy[gameVars->entQuad[0]][gameVars->entQuad[1]] * .01);
	gameVars->starbaseQuadrant = (int)(gameVars->galaxy[gameVars->entQuad[0]][gameVars->entQuad[1]] * .1 - 10 * gameVars->klingQuad);
	gameVars->stars = gameVars->galaxy[gameVars->entQuad[0]][gameVars->entQuad[1]] - 100 * gameVars->klingQuad - 10 * gameVars->starbaseQuadrant;

	if (gameVars->klingQuad > 0)
	{
	  	printf("Combat Area  Condition Red\n");
	  	if (gameVars->shields < 200)
	  	{
	    	printf("Shields Dangerously Low\n");
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
	      	gameVars->klingData[i][3] = 100 + get_rand(200);
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



void eventHandler(GameVariables *gameVars)
{
	/*
	Initializes the game variables
	*/

	//Initialize Time
	if(strcmp(gameVars->command,"nav")==0)
	{
		printf("nav function\n");
	}
	else if (strcmp(gameVars->command,"srs")==0)
	{
		printf("srs function\n");		
	}
	else if (strcmp(gameVars->command,"lrs")==0)
	{
		printf("lrs function\n");		
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
      printf("  nav - To Set Course\n");
      printf("  srs - Short Range Sensors\n");
      printf("  lrs - Long Range Sensors\n");
      printf("  pha - Phasers\n");
      printf("  tor - Photon Torpedoes\n");
      printf("  she - Sheild Control\n");
      printf("  dam - Damage Control\n");
      printf("  com - Library Computer\n");
      printf("  xxx - Resign Command\n");
      printf("\n");
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
		printf("   CHIEF ENGINEER SCOTT REPORTS  'WARP ENGINES SHUT DOWN\n");
		printf("   AT SECTOR %.1lf,%.1lf OF QUADRANT %d, %d.'", 
			gameVars->entSect[0], gameVars->entSect[1], 
			gameVars->entQuad[0], gameVars->entQuad[1]);
	}
}


void short_range_scan(GameVariables *gameVars)
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

void courseNavigation(GameVariables *gameVars)
{
	int q4, q5;
  	char sTemp[MAXLEN];
  	double c1;
  	char sX[4] = "8";

  	printf("Course (0-9): ");
  	gets(sTemp);
  	printf("\n");
  	c1 = atof(sTemp);

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


void stringCompare(GameVariables *gameVars)
{
  int i;
  char temp[4];

  gameVars->tempSectCoord[0] = (int)(gameVars->tempSectCoord[0] + 0.5);
  gameVars->tempSectCoord[1] = (int)(gameVars->tempSectCoord[1] + 0.5);

  gameVars->quadIndex = ((gameVars->tempSectCoord[1] - 1) * 3) + ((gameVars->tempSectCoord[0] - 1) * 24) + 1;

  mid_str(temp, gameVars->quadDisp, gameVars->quadIndex, 3);

  i = strncmp(temp, gameVars->quadDisp, 3);

  if (i == 0)
    gameVars->compare = 1;
  else
    gameVars->compare = 0;

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

void mid_str(char *a, char *b, int x, int y)
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

int findRandom(void)
{
	return(get_rand(8));
}


int get_rand(int iSpread)
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


