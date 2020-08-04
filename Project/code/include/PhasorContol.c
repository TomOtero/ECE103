  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <stdbool.h>

#include "sst_functions.h"

void phaserControl (GameVariables *game_vars)
{
	int firePhasers = 3000;
	int maxDamage;
	int damageDone;
	
	if (game_vars->damage[4] < 0)
	{
		printf("PHASERS INOPERATIVE\n");
		return;
	}
	
	if (game_vars->klingStart <= 0)
	{
		printf("SCIENCE OFFICER SPOCK REPORTS  'SENSORS SHOW NO ENEMY SHIPS\n");
		printf("                                IN THIS QUADRANT'\n");
		return;
	}
	
	if (game_vars->damage[8] < 0)
	{
		printf("COMPUTER FAILURE HAMPERS ACCURACY\n");
	}
	
	printf("PHASERS LOCKED ON TARGET;  \n");
	while ((game_vars->currEnergy - firePhasers) <= 0)
	{
		printf("ENERGY AVAILABLE = %d UNITS\n", game_vars->currEnergy);
		printf("NUMBER OF UNITS TO FIRE? \n");
		scanf("%d", &firePhasers);
		
		if ((firePhasers <= 0))
		{
			return;
		}
	}
	
	if (game_vars->damage[7] < 0)
	{
		firePhasers = int (firePhasers*rand());
	}
	
	game_vars->currEnergy = game_vars->currEnergy - firePhasers;
	
	maxDamage = firePhasers/game_vars->klingStart;
	
	
	for (int i = 0; i < 4; i++)
	{
		if (game_vars->klingData [i][3] <= 0)
		{
			return;
		}
		
		damageDone = (maxDamage/findDistance())*(rand()); //Confirm Distance Function Name
		
		if (damageDone < (.15 * game_vars->klingData[i][3]))
		{
			printf("SENSORS SHOW NO DAMAGE TO ENEMY AT %d, %d\n", 
					game_vars->klingData[i][1],game_vars->klingData[i][2]);
			return;
		}
		
		game_vars->klingData[i][3] = game_vars->klingData[i][3] - damageDone; 
		
		printf("%d UNIT HIT ON KLINGON AT SECTOR %d, %d\n", 
				damageDone, game_vars->klingData [i][1], game_vars->klingData[i][2]);
		
		if (game_vars->kling_data[i][3] <= 0)
		{
			printf("*** KLINGON DESTROYED ***");
			game_vars->klingStart = klingStart-1;
			game_vars->klingLeft = klingLeft -1;
			game_vars->galaxyRecord = klingData[i][1];
			game_vars->galaxyRecord = klingData[i][2];
			InsertStringArray(); //Confirm Function Name 
			game_vars->klingData[i][3] = 0;
			game_vars->galaxy[game_vars->entQuad1][game_vars->entQuad2] = 
				game_vars->galaxy [game_vars->entQuad1][game_vars->entQuad2] - 100;
			game_vars->galaxyRecord[game_vars->entQuad1][game_vars->entQuad2] = 
				game_vars->galaxy [game_vars->entQuad1][game_vars->entQuad2];
			if (game_vars->klingLeft <= 0)
			{
				endOfGame();
			}
		}
		else
		{
			printf("   (SENSORS SHOW %d UNITS REMAINING)", game_vars->klingData[i][3]);
		}
		
		
	}
	
	
	
	return;
}