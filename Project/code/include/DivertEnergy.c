  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <stdbool.h>

#include "sst_functions.h"

void divertEnergy (GameVariables *game_vars)
{
	game_vars->currEnergy = game_vars->currEnergy - game_vars->n - 10; // Need 'C' code variable name for N
	
	if (currEnergy >= 0)
		return;
	else 
	{
		printf("SHIELD CONTROL SUPPLIES ENERGY TO COMPLETE THE MANEUVER.");
		game_vars->shields = game_vars->shields + game_vars->energy;
		game_vars->energy = 0;
		if (game_vars->shields <= 0)
			game_vars->shields = 0;
	}
	return;
}