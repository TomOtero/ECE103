/*
	ECE 103 Engineering Programming
	Team 9: Tom Otero, Ed Rees, Kevin Deleon
	Last update: 07/25/20

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
	printf("   Destroy the %d Klingon warships which have invaded\n", k9);
	printf(" the galaxy before they can attack Federation Headquarters\n");
	printf(" on stardate %d. This gives you %d days. There %s\n",
	gameVars->stardateStart + gameVars->stardateEnd, gameVars->stardateEnd, gameVars->tempStr[1]);
	printf(" %d starbase%s in the galaxy for resupplying your ship.\n\n",
	gameVars->starbaseTotal, gameVars->tempStr[0]);

	printf("Hit any key to accept command. ");
	getchar();
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

/* Returns an integer from 1 to iSpread */
int get_rand(int iSpread)
{
  return((rand() % iSpread) + 1);
}


