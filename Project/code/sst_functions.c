/*
	ECE 103 Engineering Programming
	Team 9: Tom Otero, Ed Rees, Kevin Deleon
	Last update: 07/25/20

*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
		file = fopen("test.txt","r");
		while((fileC=fgetc(file))!=EOF)
		{
			printf("%c",fileC);
		}
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
	gameVars->stardateCurr=(int)(rand()*20+20)*100;  		// T
	gameVars->stardateStart=stardateCurr;			 		// T0
	gameVars->stardateEnd = 25+(int)(rand()*10); 	 		// T9

	//Initialize Enterprise
	gameVars->dockFlag 			 = 0;						// D0
	gameVars->startEnergy 		 = 3000;						// E
	gameVars->currEnergy 		 = gameVars->startEnergy;	// E0
	gameVars->torpCap 			 = 10;						// P
	gameVars->torpLeft 			 = gameVars->torpCap;		// P0
	gameVars->shields 			 = 0;						// S
	gameVars->klingPow 			 = 200;						// S9
	gameVars->klingLeft 		 = 0;						// K9
	gameVars->starbaseTotal 	 = 2;						// B9
	gameVars->galaxy[0][0]		 = { 0 };
	gameVars->galaxyRecord[0][0] = { 0 };
	gameVars->klingData[0][0]	 = { 0 };

}


void initialize(GameVariables *gameVars)
{
	// Clear game vars to default
	clear(gameVars);

	// Initialize Enterprise

	


}

void event_handler(GameVariables *gameVars)
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
		command_help();
	}

}

void command_help(void)
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

double find_distance(GameVariables *gameVars, int index)
{
	double dist = 0.0;
	dist = sqrt(pow((gameVars->klingData[index][0]-gameVars->entSect[0]),2)+
			pow((gameVars->klingData[index][1]-gameVars->entSect[1]),2));

	return dist;
}

int find_random(GameVariables *gameVars)
{
	int randReturn = 0;
	randReturn = rand()*7.98+1.01;
	return randReturn;
}
