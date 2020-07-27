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
	gameVars->startEnergy 		 = 3000;						// E
	gameVars->currEnergy 		 = gameVars->startEnergy;	// E0
	gameVars->torpCap 			 = 10;						// P
	gameVars->torpLeft 			 = gameVars->torpCap;		// P0
	gameVars->shields 			 = 0;						// S
	gameVars->klingPow 			 = 200;						// S9
	gameVars->klingLeft 		 = 0;						// K9
	gameVars->starbaseTotal 	 = 2;						// B9

	//Initialize strings
	strcpy(gameVars->tempStr[0], "");
	strcpy(gameVars->tempStr[1], "IS");
	const char tempCommandList[9][6] = {{"NAV"},{"SRS"},{"LRS"},
										{"PHA"},{"TOR"},{"SHE"},
										{"DAM"},{"COM"},{"XXX"}};
	memcpy(gameVars->commandList, tempCommandList, sizeof tempCommandList); // 710

	// Initializing arrays 
	/*
		Wasn't sure if arrays needed to be fully initialized, and they do not
	  	accordding to IBM:
	  	https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.2.0/com.ibm.zos.v2r2.cbclx01/aryin.htm
	  	 
	*/
	gameVars->galaxy[0][0]		 = 0;
	gameVars->galaxyRecord[0][0] = 0;
	gameVars->klingData[0][0]	 = 0;
	


}


void initialize(GameVariables *gameVars)
{
	// Clear game vars to default
	clear(gameVars);

	// Initialize Enterprise
	gameVars->entQuad[0] = findRandom();
	gameVars->entQuad[1] = findRandom();
	gameVars->entSect[0] = findRandom();
	gameVars->entSect[1] = findRandom();
	gameVars->damage[0]  = 0;
	static const long tempArray[9][2] = {{0,1}, {-1,1}, {-1,0},		// 530 - 600
	   								     {-1,-1}, {0-1}, {1,-1},
								         {1,0}, {1,1}, {0,1}};

	memcpy(gameVars->locationMove, tempArray, sizeof tempArray);
	//////////////////////////////////
	//        Debug
	// for(int i=0; i<9; i++)
	// {
	// 	for(int j=0; j<2; j++)
	// 	{
	// 		printf("%d", gameVars->locationMove[i][j]); 
	// 	}
	// 	printf("\n");
	// }
	//////////////////////////////////


	
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
void OutOfBounds (GameVariables *gameVars)
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


void LongRangeScan (GameVariables *gameVars)
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



double findDistance(GameVariables *gameVars, int index)
{
	double dist = 0.0;
	dist = sqrt(pow((gameVars->klingData[index][0]-gameVars->entSect[0]),2)+
			pow((gameVars->klingData[index][1]-gameVars->entSect[1]),2));

	return dist;
}

int findRandom(void)
{
	int randReturn = 0;
	randReturn = rand()*7.98+1.01;
	return randReturn;
}
