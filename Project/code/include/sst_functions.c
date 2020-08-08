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
		phaserControl(gameVars);	
	}
	else if (strcmp(gameVars->command,"tor")==0)
	{
		photonTorpedoes(gameVars);		
	}
	else if (strcmp(gameVars->command,"she")==0)
	{
		shieldControl(gameVars);		
	}
	else if (strcmp(gameVars->command, "dam")==0)
    {
        damageControl(gameVars);
    }
	else if (strcmp(gameVars->command,"com")==0)
	{
		libraryComputer(gameVars);		
	}
	else if (strcmp(gameVars->command,"xxx")==0)
	{
		resignCommision(gameVars);		
	}
	else if(strcmp(gameVars->command,"help")==0)
	{
		commandHelp();
	}
	else
	{
		commandHelp();
	}

}

void commandHelp(void)
{
/*
2160 NEXT I : PRINT "ENTER ONE OF THE FOLLOWING : "
2180 PRINT "  NAV  (TO SET COURSE)"
2190 PRINT "  SRS  (FOR SHORT RANGE SENSOR SCAN)"
2200 PRINT "  LRS  (FOR LONG RANGE SENSOR SCAN)"
2210 PRINT "  PHA  (TO FIRE PHASERS)"
2220 PRINT "  TOR  (TO FIRE PHOTON TORPEDOES)"
2230 PRINT "  SHE  (TO RAISE OR LOWER SHIELDS)"
2240 PRINT "  DAM  (FOR DAMAGE CONTROL REPORTS)"
2250 PRINT "  COM  (TO CALL ON LIBRARY-COMPUTER)"
2260 PRINT "  XXX  (TO RESIGN YOUR COMMAND)" : PRINT : GOTO  1990
*/
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

// Original Functions 
void intro(void)
{
	/*
	This function displays the intro mesgameVars->objInSectorge and asks if user
	wants to display the instructions.

	*/

	/*
220 PRINT : PRINT : PRINT : PRINT : PRINT : PRINT : PRINT : PRINT : PRINT : PRINT : PRINT
221 PRINT "                                    ,------*------,"
222 PRINT "                    ,-------------   '---  ------'"
223 PRINT "                     '-------- --'      / /"
224 PRINT "                         ,---' '-------/ /--,"
225 PRINT "                          '----------------'" : PRINT
226 PRINT "                    THE USS ENTERPRISE --- NCC-1701"
227 PRINT : PRINT : PRINT : PRINT : PRINT
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
/*
260 REM CLEAR 600
270 Z$="                         "
330 DIM G(8,8),C(9,2),K(3,3),N(3),Z(8,8),D(8)
370 T=INT(RND(1)*20+20)*100 : T0=T : T9=25+INT(RND(1)*10) : D0=0 : E=3000 : E0=E //done
440 P=10 : P0=P : S9=200 : S=0 : B9=2 : K9=0 : X$="" : X0$=" IS "
470 DEF FND(D)=SQR((K(I,1)-S1)^2+(K(I,2)-S2)^2)
475 DEF FNR(R)=INT(RND(R)*7.98+1.01)
*/

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
	strcpy(gameVars->tempStr[1], "IS");
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
/*
480 REM INITIALIZE ENTERPRISE'S POSITION
490 Q1=FNR(1) : Q2=FNR(1) : S1=FNR(1) : S2=FNR(1)
530 FOR I=1 TO 9 : C(I,1)=0 : C(I,2)=0 : NEXT I
540 C(3,1)=-1 : C(2,1)=-1 : C(4,1)=-1 : C(4,2)=-1 : C(5,2)=-1 : C(6,2)=-1
600 C(1,2)=1 : C(2,2)=1 : C(6,1)=1 : C(7,1)=1 : C(8,1)=1 : C(8,2)=1 : C(9,2)=1
670 FOR I=1 TO 8 : D(I)=0 : NEXT I
710 A1$="NAVSRSLRSPHATORSHEDAMCOMXXX"
*/

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
	
/*
810 REM SETUP WHAT EXISTS IN GALAXY . . .
815 REM K3= # KLINGONS  B3= # STARBASES  S3 = # STARS
820 FOR I=1 TO 8 : FOR J=1 TO 8 : K3=0 : Z(I,J)=0 : R1=RND(1)
850 IF R1>.98 THEN K3=3 : K9=K9+3 : GOTO 980
860 IF R1>.95 THEN K3=2 : K9=K9+2 : GOTO 980
870 IF R1>.80 THEN K3=1 : K9=K9+1
980 B3=0 : IF RND(1)>.96 THEN B3=1 : B9=B9+1
1040 G(I,J)=K3*100+B3*10+FNR(1) : NEXT J : NEXT I : IF K9>T9 THEN T9=K9+1
1100 IF B9<>0 THEN 1200
1150 IF G(Q1,Q2)<200 THEN G(Q1,Q2)=G(Q1,Q2)+120 : K9=K9+1
1160 B9=1 : G(Q1,Q2)=G(Q1,Q2)+10 : Q1=FNR(1) : Q2=FNR(1)
1200 K7=K9 : IF B9<>1 THEN X$="S" : X0$=" ARE "
1230 PRINT "YOUR ORDERS ARE AS FOLLOWS : "
1240 PRINT "   DESTROY THE ";K9;" KLINGON WARSHIPS WHICH HAVE INVADED"
1252 PRINT "   THE GALAXY BEFORE THEY CAN ATTACK FEDERATION HEADQUARTERS"
1260 PRINT "   ON STARDATE ";T0+T9;". THIS GIVES YOU ";T9;" DAYS. THERE";X0$
1272 PRINT "   ";B9;" STARBASE";X$;" IN THE GALAXY FOR RESUPPLYING YOUR SHIP."
1280 PRINT : REM PRINT "HIT ANY KEY EXCEPT RETURN WHEN READY TO ACCEPT COMMAND"
1300 I=RND(1) : REM IF INP(1)=13 THEN 1300
*/

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		  {
		  	gameVars->klingQuad = 0;
            gameVars->galaxyRecord[i][j] = 0;
		    gameVars->tempPos[0] = getRandRange(100);
		    if (gameVars->tempPos[0]  > 98)
		      gameVars->klingQuad = 3;
		    else if (gameVars->tempPos[0]  > 95)
		      gameVars->klingQuad = 2;
		    else if (gameVars->tempPos[0]  > 80)
		      gameVars->klingQuad = 1;

		    gameVars->klingLeft = gameVars->klingLeft + gameVars->klingQuad;
		    gameVars->starbaseQuadrant = 0;

		    if (getRandRange(100) > 96)
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
          	gameVars->klingLeft++;
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
      	strcpy(gameVars->tempStr[0], "S");
      	strcpy(gameVars->tempStr[1], "ARE");
    }

	printf("YOUR ORDERS ARE AS FOLLOWS :\n\n");
	printf("   DESTROY THE %d KLINGON WARSHIPS WHICH HAVE INVADED\n", gameVars->klingLeft);
	printf("   THE GALAXY BEFORE THEY CAN ATTACK FEDERATION HEADQUARTERS\n");
	printf("   ON STARDATE %d. THIS GIVES YOU %d DAYS. THERE %s\n",
	gameVars->stardateStart + gameVars->stardateEnd, gameVars->stardateEnd, gameVars->tempStr[1]);
	printf("   %d STARBASE%s IN THE GALAXY FOR RESUPPLYING YOUR SHIP.\n\n",
	gameVars->starbaseTotal, gameVars->tempStr[0]);

	printf("HIT ANY KEY WHEN READY TO ACCEPT COMMAND ");
	getchar();
}


void newQuadrant(GameVariables *gameVars)
{
/*
1310 REM HERE ANY TIME NEW QUADRANT ENTERED
1320 Z4=Q1 : Z5=Q2 : K3=0 : B3=0 : S3=0 : G5=0 : D4=.5*RND(1) : Z(Q1,Q2)=G(Q1,Q2)
1390 IF Q1<1 OR Q1>8 OR Q2<1 OR Q2>8 THEN 1600
1430 GOSUB 9030 : PRINT : IF T0<>T THEN 1490
1460 PRINT "YOUR MISSION BEGINS WITH YOUR STARSHIP LOCATED"
1470 PRINT "IN THE GALACTIC QUADRANT, '";G2$;"'." : GOTO 1500
1490 PRINT "NOW ENTERING ";G2$;" QUADRANT . . ."
1500 PRINT : K3=INT(G(Q1,Q2)*.01) : B3=INT(G(Q1,Q2)*.1)-10*K3
1540 S3=G(Q1,Q2)-100*K3-10*B3 : IF K3=0 THEN 1590
1560 PRINT "COMBAT AREA      CONDITION RED" : IF S>200 THEN 1590
1580 PRINT "   SHIELDS DANGEROUSLY LOW"
1590 FOR I=1 TO 3 : K(I,1)=0 : K(I,2)=0 : NEXT I
1600 FOR I=1 TO 3 : K(I,3)=0 : NEXT I : Q$=Z$+Z$+Z$+Z$+Z$+Z$+Z$+LEFT$(Z$,17)
*/
	int i;
	gameVars->tempQuadCoord[0] = gameVars->entQuad[0];
	gameVars->tempQuadCoord[1] = gameVars->entQuad[1];
	gameVars->klingQuad = 0;
	gameVars->starbaseQuadrant = 0;
	gameVars->stars = 0;
	gameVars->quadName = 0; 
	gameVars->repairTime = (double) (getRandRange(100)/100)/2; // D4=.5*RND(1) //sets to a value 0 - 1 then takes half
	gameVars->galaxyRecord[gameVars->tempQuadCoord[0]][gameVars->tempQuadCoord[1]] = 
			gameVars->galaxy[gameVars->entQuad[0]][gameVars->entQuad[1]];

	if (gameVars->entQuad[0] >= 1 || gameVars->entQuad[0] <= 8 || 
		gameVars->entQuad[1] >= 1 || gameVars->entQuad[1] <= 8)
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
	      	gameVars->klingData[i][3] = 100 + getRandRange(200);
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
	// int q4, q5; 			// No idea what these are used for...
	char temp[6];
	// double course;
	strcpy(gameVars->tempStr[0], "8");

	printf("COURSE (0-9): ");

	gets(temp);

	printf("\n");

	gameVars->course = atof(temp);

	if (gameVars->course == 9.0)
	gameVars->course = 1.0;

	if (gameVars->course < 0 || gameVars->course > 9.0)
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

	gameVars->n = doubleToInt(gameVars->warpFactor * 8.0); //N=INT(W1*8+.5)

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
	klingonsMove(gameVars);

	repairDamage(gameVars);

	strcpy(gameVars->objInSector, "   ");
	gameVars->tempSectCoord[0] = (int)gameVars->entSect[0];
	gameVars->tempSectCoord[1] = (int)gameVars->entSect[1];
	insertInQuadrant(gameVars);

	gameVars->navX1 = gameVars->locationMove[(int)gameVars->course][0] + 
		(gameVars->locationMove[(int)gameVars->course + 1][0] - 
		gameVars->locationMove[(int)gameVars->course][0]) * 
		(gameVars->course - (int)gameVars->course);
	
	gameVars->navX2 = gameVars->locationMove[(int)gameVars->course][1] + 
		(gameVars->locationMove[(int)gameVars->course + 1][1] - 
		gameVars->locationMove[(int)gameVars->course][1]) * 
		(gameVars->course - (int)gameVars->course);

	gameVars->navX = gameVars->entSect[0];
	gameVars->navY = gameVars->entSect[1];
	// q4 = gameVars->entQuad[0];
	// q5 = gameVars->entQuad[0];

	for (i = 1; i <= gameVars->n; i++)
	{
		gameVars->entSect[0] = gameVars->entSect[0] + gameVars->navX1;
	  	gameVars->entSect[1] = gameVars->entSect[1] + gameVars->navX2;

	  	/* @@@ gameVars->tempSectCoord[0] = doubleToInt(s1); */
		gameVars->tempSectCoord[0] = (int)gameVars->entSect[0];
		/* @@@ gameVars->tempSectCoord[1] = doubleToInt(s2); */
		gameVars->tempSectCoord[1] = (int)gameVars->entSect[1];

	  if (gameVars->tempSectCoord[0] < 1 || gameVars->tempSectCoord[0] >= 9 || gameVars->tempSectCoord[1] < 1 || gameVars->tempSectCoord[1] >= 9)
	    {
	      	outOfBounds(gameVars);
	      	completeManeuver(gameVars);
	      	return;
	    }

	  stringCompare(gameVars);

	  //3060 REM BEGIN MOVING STARSHIP
	  if (gameVars->compare != 1) /* Sector not empty */
	    {
	      	gameVars->entSect[0] = gameVars->entSect[0] + gameVars->navX1;
	  		gameVars->entSect[1] = gameVars->entSect[1] + gameVars->navX2;
	      	printf("WARP ENGINES SHUT DOWN AT SECTOR ");
	      	printf("%d, %d DUE TO BAD NAVAGATION\n\n", 
	      			gameVars->tempSectCoord[0], gameVars->tempSectCoord[1]);
	      	i = gameVars->n + 1;
	    }
	}

	completeManeuver(gameVars);
}


void completeManeuver(GameVariables *gameVars)
{
	double t8;

	strcpy(gameVars->objInSector, "<*>");
  	/* @@@ gameVars->tempSectCoord[0] = doubleToInt(s1); */
	gameVars->tempSectCoord[0] = (int)gameVars->entSect[0];
	/* @@@ gameVars->tempSectCoord[1] = doubleToInt(s2); */
	gameVars->tempSectCoord[1] = (int)gameVars->entSect[1];
	insertInQuadrant(gameVars);

	maneuverEnergy(gameVars);

	t8 = 1.0;

	if (gameVars->warpFactor < 1.0)
	t8 = gameVars->warpFactor;

	gameVars->stardateCurr = gameVars->stardateCurr + t8;

	if (gameVars->stardateCurr > gameVars->stardateStart + gameVars->stardateEnd)
	{	
		endOfTime(gameVars);
	}

	shortRangeScan(gameVars);
}


void outOfBounds (GameVariables *gameVars)
{
/*
3490 REM EXCEEDED QUADRANT LIMITS
3500 X=8*Q1+X+N*X1 : Y=8*Q2+Y+N*X2 : Q1=INT(X/8) : Q2=INT(Y/8) : S1=INT(X-Q1*8)
3550 S2=INT(Y-Q2*8) : IF S1=0 THEN Q1=Q1-1 : S1=8
3590 IF S2=0 THEN Q2=Q2-1 : S2=8
3620 X5=0 : IF Q1<1 THEN X5=1 : Q1=1 : S1=1
3670 IF Q1>8 THEN X5=1 : Q1=8 : S1=8
3710 IF Q2<1 THEN X5=1 : Q2=1 : S2=1
3750 IF Q2>8 THEN X5=1 : Q2=8 : S2=8
3790 IF X5=0 THEN 3860
3800 PRINT "LT. UHURA REPORTS MESSAGE FROM STARFLEET COMMAND : "
3810 PRINT "  'PERMISSION TO ATTEMPT CROSSING OF GALACTIC PERIMETER"
3820 PRINT "  IS HEREBY *DENIED*.  SHUT DOWN YOUR ENGINES.'"
3830 PRINT "CHIEF ENGINEER SCOTT REPORTS  'WARP ENGINES SHUT DOWN"
3840 PRINT "  AT SECTOR";S1;",";S2;"OF QUADRANT";Q1;",";Q2;".'"
3850 IF T>T0+T9 THEN 6220
3860 IF 8*Q1+Q2=8*Q4+Q5 THEN 3370
3870 T=T+1 : GOSUB 3910 : GOTO 1320
*/
	int outOfBoundsFlag = 0;
	gameVars->n = (int)(gameVars->warpFactor * 8.0);
	
	gameVars->navX = (8 * gameVars->entQuad[0]) + 
					  gameVars->navX + (gameVars->n * gameVars->navX1);
	gameVars->navY = (8 * gameVars->entQuad[1]) + 
					  gameVars->navY + (gameVars->n * gameVars->navY);

	gameVars->entQuad[0] = (int)(gameVars->navX/8);
	gameVars->entQuad[1] = (int)(gameVars->navY/8);
	gameVars->entSect[0] = (gameVars->navX - gameVars->entQuad[0]/8);
	gameVars->entSect[1] = (gameVars->navY - gameVars->entQuad[1]/8);
	printf("[DEBUG] gameVars->entSect[0]: %f\n", gameVars->entSect[0]);
	printf("[DEBUG] gameVars->entSect[1]:%f\n", gameVars->entSect[1]);
	if ((int)gameVars->entSect[0] == 0) //3550 ...  IF S1=0 THEN Q1=Q1-1 : S1=8
	{
		gameVars->entQuad[0] = gameVars->entQuad[0] - 1;
		gameVars->entSect[0] = 8.0;
	}
	
	if ((int)gameVars->entSect[1] == 0) //3590 IF S2=0 THEN Q2=Q2-1 : S2=8
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
	
    if (outOfBoundsFlag == 1)
	{
		printf("   LT. UHURA REPORTS MESSAGE FROM STARFLEET COMMAND : \n");
		printf("   'PERMISSION TO ATTEMPT CROSSING OF GALACTIC PERIMETER\n");
		printf("   IS HEREBY *DENIED*.  SHUT DOWN YOUR ENGINES.'\n");
		printf("   CHIEF ENGINEER SCOTT REPORTS:  'WARP ENGINES SHUT DOWN\n");
		printf("   AT SECTOR %d, %d OF QUADRANT %d, %d.'\n", 
			(int)gameVars->entSect[0], (int)gameVars->entSect[1], 
			gameVars->entQuad[0], gameVars->entQuad[1]);
	}

	maneuverEnergy(gameVars);
	printf("[DEBUG] here2\n");
	if (gameVars->stardateCurr > gameVars->stardateStart + gameVars->stardateEnd)
    	endOfTime(gameVars);
		gameVars->stardateCurr = gameVars->stardateCurr + 1;
		newQuadrant(gameVars);
}


void maneuverEnergy(GameVariables *gameVars)
{
/*
3900 REM MANEUVER ENERGY S/R **
3910 E=E-N-10 : IF E>=0 THEN RETURN
3930 PRINT "SHIELD CONTROL SUPPLIES ENERGY TO COMPLETE THE MANEUVER."
3940 S=S+E : E=0 : IF S<=0 THEN S=0
*/
	printf("[DEBUG] maneuverEnergy()\n");
  	gameVars->currEnergy = gameVars->currEnergy - gameVars->n - 10;

  	if (gameVars->currEnergy >= 0)
  	{
  		printf("[DEBUG]  if (gameVars->currEnergy >= 0)\n");
    	return;
  	}

  	printf("SHIELD CONTROL SUPPLIES ENERGY TO COMPLETE THE MANEUVER.\n\n");
  	gameVars->shields = gameVars->shields + gameVars->currEnergy;
  	gameVars->currEnergy = 0;

  	if (gameVars->shields <= 0)
  	{
  		printf("[DEBUG] if (gameVars->shields <= 0)\n");
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
	              printf("SHIELDS DROPPED FOR DOCKING PURPOSES\n");
	              gameVars->shields = 0;
	            }
	        }
	    }
  	}
  if (gameVars->damage[2] < 0.0)
    {
      printf("\n*** SHORT RANGE SENSORS ARE OUT ***\n");
      return;
    }

  printf("------------------------\n");
  for (i = 0; i < 8; i++)
    {
      for (j = 0; j < 24; j++)
        putchar(gameVars->quadDisp[i * 24 + j]); 

      if (i == 0)
    printf("    STARDATE            %d\n", (int) gameVars->stardateCurr);
      if (i == 1)
    printf("    CONDITION           %s\n", gameVars->condition);
      if (i == 2)
    printf("    QUADRANT            %d, %d\n",  gameVars->entQuad[0], gameVars->entQuad[1]);
      if (i == 3)
    /* @@@ printf("    Sector              %d, %d\n", doubleToInt(s1), doubleToInt(s2)); */
    printf("    SECTOR              %d, %d\n", (int)gameVars->entSect[0], (int)gameVars->entSect[1]);
      if (i == 4)
    printf("    PHOTON TORPEDOES    %d\n", gameVars->torpLeft);
      if (i == 5)
    printf("    TOTAL ENERGY        %d\n", gameVars->currEnergy + gameVars->startEnergy);
      if (i == 6)
    printf("    SHIELDS             %d\n", gameVars->shields);
      if (i == 7)
    printf("    KLINGONS REMAINING  %d\n", gameVars->klingLeft);
    }
  printf("------------------------\n\n");

  return;
}


void longRangeScan (GameVariables *gameVars)
{
/*
4000 IF D(3)<0 THEN PRINT "LONG RANGE SENSORS ARE INOPERABLE" : GOTO 1990
4030 PRINT "LONG RANGE SCAN FOR QUADRANT ";Q1;",";Q2
4040 O1$="    -------------------" : PRINT O1$
4060 FOR I=Q1-1 TO Q1+1 : N(1)=-1 : N(2)=-2 : N(3)=-3 : FOR J=Q2-1 TO Q2+1
4120 IF I>0 AND I<9 AND J>0 AND J<9 THEN N(J-Q2+2)=G(I,J) : Z(I,J)=G(I,J)
4180 NEXT J : FOR L=1 TO 3 : PRINT " :  "; : IF N(L)<0 THEN PRINT "*** "; : GOTO 4230
4210 PRINT RIGHT$(STR$(N(L)+1000),3);" ";
4230 NEXT L : PRINT " : " : PRINT O1$ : NEXT I : GOTO 1990
*/
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


void phaserControl(GameVariables *gameVars)
{
/*
4250 REM PHASER CONTROL CODE BEGINS HERE
4260 IF D(4)<0 THEN PRINT "PHASERS INOPERATIVE" : GOTO 1990
4265 IF K3>0 THEN 4330
4270 PRINT "SCIENCE OFFICER SPOCK REPORTS  'SENSORS SHOW NO ENEMY SHIPS"
4280 PRINT "                                IN THIS QUADRANT'" : GOTO 1990
4330 IF D(8)<0 THEN PRINT "COMPUTER FAILURE HAMPERS ACCURACY"
4350 PRINT "PHASERS LOCKED ON TARGET;  ";
4360 PRINT "ENERGY AVAILABLE =";E;" UNITS"
4370 INPUT "NUMBER OF UNITS TO FIRE? ";X : IF X<=0 THEN 1990
4400 IF E-X<0 THEN 4360
4410 E=E-X : IF D(7)<0 THEN X=X*RND(1)
4450 H1=INT(X/K3) : FOR I=1 TO 3 : IF K(I,3)<=0 THEN 4670
4480 H=INT((H1/FND(0))*(RND(1)+2)) : IF H>.15*K(I,3) THEN 4530
4500 PRINT "SENSORS SHOW NO DAMAGE TO ENEMY AT ";K(I,1);",";K(I,2) : GOTO 4670
4530 K(I,3)=K(I,3)-H : PRINT H;" UNIT HIT ON KLINGON AT SECTOR";K(I,1);",";
4550 PRINT K(I,2) : IF K(I,3)<=0 THEN PRINT "*** KLINGON DESTROYED ***" : GOTO 4580
4560 PRINT "   (SENSORS SHOW";K(I,3);" UNITS REMAINING)" : GOTO 4670
4580 K3=K3-1 : K9=K9-1 : Z1=K(I,1) : Z2=K(I,2) : A$="   " : GOSUB 8670
4650 K(I,3)=0 : G(Q1,Q2)=G(Q1,Q2)-100 : Z(Q1,Q2)=G(Q1,Q2) : IF K9<=0 THEN 6370
4670 NEXTI : GOSUB 6000 : GOTO 1990
*/
	int firePhasers = 3000;
	int maxDamage;
	int damageDone;
	
	if (gameVars->damage[4] < 0)
	{
		printf("PHASERS INOPERATIVE\n");
		return;
	}
	
	if (gameVars->klingStart <= 0)
	{
		printf("SCIENCE OFFICER SPOCK REPORTS  'SENSORS SHOW NO ENEMY SHIPS\n");
		printf("                                IN THIS QUADRANT'\n");
		return;
	}
	
	if (gameVars->damage[8] < 0)
	{
		printf("COMPUTER FAILURE HAMPERS ACCURACY\n");
	}
	
	printf("PHASERS LOCKED ON TARGET;  \n");
	while ((gameVars->currEnergy - firePhasers) <= 0)
	{
		printf("ENERGY AVAILABLE = %d UNITS\n", gameVars->currEnergy);
		printf("NUMBER OF UNITS TO FIRE? \n");
		scanf("%d", &firePhasers);
		
		if ((firePhasers <= 0))
		{
			return;
		}
	}
	
	if (gameVars->damage[7] < 0)
	{
		firePhasers = (int)(firePhasers*rand());
	}
	
	gameVars->currEnergy = gameVars->currEnergy - firePhasers;
	
	maxDamage = firePhasers/gameVars->klingStart;
	
	
	for (int i = 0; i < 3; i++)
	{
		if (gameVars->klingData [i][2] <= 0)
		{
			return;
		}
		
		damageDone = (maxDamage/findDistance(gameVars,i))*(rand()); //Confirm Distance Function Name
		
		if (damageDone < (.15 * gameVars->klingData[i][2]))
		{
			printf("SENSORS SHOW NO DAMAGE TO ENEMY AT %d, %d\n", 
				gameVars->klingData[i][0],gameVars->klingData[i][1]);
			return;
		}
		
		gameVars->klingData[i][2] = gameVars->klingData[i][2] - damageDone; 
		
		printf("%d UNIT HIT ON KLINGON AT SECTOR %d, %d\n", 
			damageDone, gameVars->klingData [i][0], gameVars->klingData[i][1]);
		
		if (gameVars->klingData[i][2] <= 0)
		{
			printf("*** KLINGON DESTROYED ***");
			gameVars->klingQuad--;
			gameVars->klingLeft--;
			gameVars->tempSectCoord[0] = gameVars->klingData[i][0];
			gameVars->tempSectCoord[1] = gameVars->klingData[i][1];
			insertInQuadrant(gameVars); //Confirm Function Name 
			gameVars->klingData[i][2] = 0;
			gameVars->galaxy[gameVars->entQuad[0]][gameVars->entQuad[1]] = 
				gameVars->galaxy [gameVars->entQuad[0]][gameVars->entQuad[1]] - 100;
			gameVars->galaxyRecord[gameVars->entQuad[0]][gameVars->entQuad[1]] = 
				gameVars->galaxy [gameVars->entQuad[0]][gameVars->entQuad[1]];
			if (gameVars->klingLeft <= 0)
			{
				endOfGame(gameVars);
			}
		}
		else
		{
			printf("   (SENSORS SHOW %d UNITS REMAINING)", gameVars->klingData[i][2]);
		}	
	}
	return;
}


void photonTorpedoes(GameVariables *gameVars)
{
/*
4690 REM PHOTON TORPEDO CODE BEGINS HERE
4700 IF P<=0 THEN PRINT "ALL PHOTON TORPEDOES EXPENDED" : GOTO  1990
4730 IF D(5)<0 THEN PRINT "PHOTON TUBES ARE NOT OPERATIONAL" : GOTO 1990
4760 INPUT "PHOTON TORPEDO COURSE (1-9) ";C1 : IF C1=9 THEN C1=1
4780 IF C1>=1 AND C1<9 THEN 4850
4790 PRINT "ENSIGN CHEKOV REPORTS,  'INCORRECT COURSE DATA, SIR!'"
4800 GOTO 1990
4850 X1=C(C1,1)+(C(C1+1,1)-C(C1,1))*(C1-INT(C1)) : E=E-2 : P=P-1
4860 X2=C(C1,2)+(C(C1+1,2)-C(C1,2))*(C1-INT(C1)) : X=S1 : Y=S2
4910 PRINT "TORPEDO TRACK : "
4920 X=X+X1 : Y=Y+X2 : X3=INT(X+.5) : Y3=INT(Y+.5)
4960 IF X3<1 OR X3>8 OR Y3<1 OR Y3>8 THEN 5490
5000 PRINT "               ";X3;",";Y3 : A$="   " : Z1=X : Z2=Y : GOSUB 8830
5050 IF Z3<>0 THEN 4920
5060 A$="+K+" : Z1=X : Z2=Y : GOSUB 8830 : IF Z3=0 THEN 5210
5110 PRINT "*** KLINGON DESTROYED ***" : K3=K3-1 : K9=K9-1 : IF K9<=0 THEN 6370
5150 FOR I=1 TO 3 : IF X3=K(I,1) AND Y3=K(I,2) THEN 5190
5180 NEXT I : I=3
5190 K(I,3)=0 : GOTO 5430
5210 A$=" * " : Z1=X : Z2=Y : GOSUB 8830 : IF Z3=0 THEN 5280
5260 PRINT "STAR AT ";X3;",";Y3;" ABSORBED TORPEDO ENERGY." : GOSUB 6000 : GOTO 1990
5280 A$=">B<" : Z1=X : Z2=Y : GOSUB 8830 : IF Z3=0 THEN 4760
5330 PRINT "*** STARBASE DESTROYED ***" : B3=B3-1 : B9=B9-1
5360 IF B9>0 OR K9>T-T0-T9 THEN 5400
5370 PRINT "THAT DOES IT, CAPTAIN!!  YOU ARE HEREBY RELIEVED OF COMMAND"
5380 PRINT "AND SENTENCED TO 99 STARDATES AT HARD LABOR ON CYGNUS 12!!"
5390 GOTO  6270
5400 PRINT "STARFLEET COMMAND REVIEWING YOUR RECORD TO CONSIDER"
5410 PRINT "COURT MARTIAL!" : D0=0
5430 Z1=X : Z2=Y : A$="   " : GOSUB 8670
5470 G(Q1,Q2)=K3*100+B3*10+S3 : Z(Q1,Q2)=G(Q1,Q2) : GOSUB 6000 : GOTO 1990
5490 PRINT "TORPEDO MISSED" : GOSUB 6000 : GOTO 1990
*/
	char temp[6];
	int torpX, torpY; 

	if (gameVars->torpLeft <= 0)
	{
	  printf("All photon torpedoes expended\n");
	  return;
	}

	if (gameVars->damage[5] < 0.0)
	{
	  printf("Photon Tubes not operational\n");
	  return;
	}

	printf("Course (0-9): ");

	gets(temp);

	printf("\n");

	gameVars->course = atof(temp);

	if (gameVars->course == 9.0)
	gameVars->course = 1.0;

	/* @@@ if (gameVars->course < 0 || gameVars->course > 9.0) */
	if (gameVars->course < 1.0 || gameVars->course > 9.0)
	{
	  printf("Ensign Chekov roports:\n");
	  printf("  Incorrect course data, sir!\n\n");
	  return;
	}

	gameVars->currEnergy = gameVars->currEnergy - 2;
	gameVars->torpLeft--;

	gameVars->navX1 = gameVars->locationMove[(int)gameVars->course][0] + 
			(gameVars->locationMove[(int)gameVars->course + 1][0] - 
			gameVars->locationMove[(int)gameVars->course][0]) * 
			(gameVars->course - (int)gameVars->course);
	gameVars->navX2 = gameVars->locationMove[(int)gameVars->course][1] + 
			(gameVars->locationMove[(int)gameVars->course + 1][1] - 
			gameVars->locationMove[(int)gameVars->course][1]) * 
			(gameVars->course - (int)gameVars->course);

	gameVars->navX = gameVars->entSect[0] + gameVars->navX1;
	gameVars->navY = gameVars->entSect[1] + gameVars->navX2;

	torpX = doubleToInt(gameVars->navX); /* @@@ note: this is a true integer round in the MS BASIC version */
	torpY = doubleToInt(gameVars->navY); /* @@@ note: this is a true integer round in the MS BASIC version */

	gameVars->outOfBoundsFlag = 0;

	printf("Torpedo Track:\n");

	while (torpX >= 1 && torpX <= 8 && torpY >= 1 && torpY <= 8)
	{
	  printf("    %d, %d\n", torpX, torpY);

	  strcpy(gameVars->objInSector, "   ");
	  gameVars->tempSectCoord[0] = torpX;
	  gameVars->tempSectCoord[1] = torpY;

	  stringCompare(gameVars);

	  if (gameVars->compare == 0)
	    {
	      torpedoHit(gameVars);
	      klingonsShoot(gameVars);
	      return;
	    }

	  gameVars->navX = gameVars->navX + gameVars->navX1;
	  gameVars->navY = gameVars->navY + gameVars->navX2;

	  torpX = doubleToInt(gameVars->navX); /* @@@ note: this is a true integer round in the MS BASIC version */
	  torpY = doubleToInt(gameVars->navY); /* @@@ note: this is a true integer round in the MS BASIC version */
	}

	printf("Torpedo Missed\n\n");

	klingonsShoot(gameVars);
}

void torpedoHit(GameVariables *gameVars)
{
	int i, torpX, torpY;

	torpX = doubleToInt(gameVars->navX); /* @@@ note: this is a true integer round in the MS BASIC version */
	torpY = doubleToInt(gameVars->navY); /* @@@ note: this is a true integer round in the MS BASIC version */

	gameVars->compare = 0;

	strcpy(gameVars->objInSector, " * ");
	stringCompare(gameVars);

	if (gameVars->compare == 1)
	{
	  	printf("Star at %d, %d absorbed torpedo energy.\n\n", torpX, torpY);
	  	return;
	}

	strcpy(gameVars->objInSector, "+K+");
	stringCompare(gameVars);

	if (gameVars->compare == 1)
	{
	  	printf("*** Klingon Destroyed ***\n\n");
	  	gameVars->klingQuad--;
	  	gameVars->klingLeft--;

	  	if (gameVars->klingLeft <= 0)
	    	wonGame(gameVars);

	  	for (i=0; i<=3; i++)
	    	if (torpX == gameVars->klingData[i][0] && torpY == gameVars->klingData[i][1])
	      		gameVars->klingData[i][2] = 0;
	}

	strcpy(gameVars->objInSector, ">!<");
	stringCompare(gameVars);

	if (gameVars->compare == 1)
	{
	  	printf("*** Starbase Destroyed ***\n");
	  	gameVars->starbaseQuadrant--;
	  	gameVars->starbaseTotal--;

	  if (gameVars->starbaseTotal <= 0 && 
	  		gameVars->klingLeft <= gameVars->stardateCurr - 
	  								gameVars->stardateStart - 
	  								gameVars->stardateEnd)
	    {
	    	// THIS IS NOT HOW THE APPLESOFT II HANDLES THIS CONDITION
	      	printf("That does it, Captain!!");
	      	printf("You are hereby relieved of command\n");
	      	printf("and sentanced to 99 stardates of hard");
	      	printf("labor on Cygnus 12!!\n");
	      	resignCommision(gameVars);
	    }

	  	printf("Starfleet Command reviewing your record to consider\n");
	  	printf("court martial!\n\n");

	  	gameVars->dockFlag = 0;    /* Undock */
	}

	gameVars->tempSectCoord[0] = torpX;
	gameVars->tempSectCoord[1] = torpY;
	strcpy(gameVars->objInSector,"   ");
	insertInQuadrant(gameVars);

	gameVars->galaxy[gameVars->entQuad[0]][gameVars->entQuad[1]] = 
			(gameVars->klingQuad * 100) + (gameVars->starbaseQuadrant * 10) + gameVars->stars;
	gameVars->galaxyRecord[gameVars->entQuad[0]][gameVars->entQuad[1]] = 
			gameVars->galaxy[gameVars->entQuad[0]][gameVars->entQuad[1]];
}


void damageControl(GameVariables *gameVars)
{ 
	int authorizeRepair; // a1
	double d3 = 0.0;	 // not sure..
	int i;

	if (gameVars->damage[6] < 0.0)
	{
	  printf("Damage Control report not available.\n");

	  if (gameVars->dockFlag == 0)
	    return;

	  d3 = 0.0;
	  for (i = 0; i < 8; i++)
	    if (gameVars->damage[i] < 0.0)
	      d3 = d3 + .1;

	  if (d3 == 0.0)
	    return;

	  d3 = d3 + gameVars->repairTime;
	  if (d3 >= 1.0)
	    d3 = 0.9;

	  printf("\nTechnicians standing by to effect repairs to your");
	  /* @@@ printf("ship; Will you authorize the repair order (Y/N)? "); */
	  printf("ship;\nEstimated time to repair: %4.2f stardates.\n", d3);
	  printf("Will you authorize the repair order (Y/N)? ");

	  authorizeRepair = getchar();

	  if (authorizeRepair == 'Y' || authorizeRepair == 'y')
	    {
	      for (i = 1; i <= 8; i++)
	        if (gameVars->damage[i] < 0.0)
	          gameVars->damage[i] = 0.0;

	      gameVars->stardateCurr = gameVars->stardateCurr + d3 + 0.1;
	    }
	}

	printf("Device            State of Repair\n");

	for (gameVars->tempPos[0] = 0; gameVars->tempPos[0] < 8; gameVars->tempPos[0]++)
	{
	  getDeviceName(gameVars);
	  printf(gameVars->strResults);
	  /* @@@ for (i = 1; i < 25 - strlen(strResults); i++) */
	  for (i = 1; i < 25 - (int)strlen(gameVars->strResults); i++)
	  printf(" ");
	  /* @@@ printf("%4.1f\n", d[r1]); */
	  printf("%4.2f\n", gameVars->damage[gameVars->tempPos[0]]);
	}

printf("\n");
} 


void shieldControl(GameVariables *gameVars)
{
/*
5520 REM SHIELD CONTROL
5530 IF D(7)<0 THEN PRINT "SHIELD CONTROL INOPERABLE" : GOTO 1990
5560 PRINT "ENERGY AVAILABLE =";E+S; : INPUT " NUMBER OF UNITS TO SHIELDS? ";X
5580 IF X<0ORS=X THEN PRINT "<SHIELDS UNCHANGED>" : GOTO 1990
5590 IF X<=E+S THEN 5630
5600 PRINT "SHIELD CONTROL REPORTS  'THIS IS NOT THE FEDERATION TREASURY.'"
5610 PRINT "<SHIELDS UNCHANGED>" : GOTO 1990
5630 E=E+S-X : S=X : PRINT "DEFLECTOR CONTROL ROOM REPORT : "
5660 PRINT "  'SHIELDS NOW AT ";INT(S);" UNITS PER YOUR COMMAND.'" : GOTO 1990
*/
  int i;
  char temp[6];

  if (gameVars->damage[7] < 0.0)
    {
      printf("shield Control inoperable\n");
      return;
    }

  printf("Energy available = %d\n\n", gameVars->currEnergy + gameVars->shields);

  printf("Input number of units to shields: ");

  gets(temp);

  printf("\n");

  i = atoi(temp);

  if (i < 0 || gameVars->shields == i)
    {
      printf("<shields Unchanged>\n\n");
      return;
    }

  if (i >= gameVars->currEnergy + gameVars->shields)
    {
      printf("shield Control Reports:\n");
      printf("  'This is not the Federation Treasury.'\n");
      printf("<shields Unchanged>\n\n");
      return;
    }

  gameVars->currEnergy = gameVars->currEnergy + gameVars->shields - i;
  gameVars->shields = i;

  printf("Deflector Control Room report:\n");
  printf("  'Shields now at %d units per your command.'\n\n", gameVars->shields);
}


void libraryComputer(GameVariables *gameVars)
{
	char temp[6];

	if (gameVars->damage[8] < 0.0)
	{
		printf("Library Computer inoperable\n");
  		return;
	}

	printf("Computer active and awating command: ");

	gets(temp);
	printf("\n");

	if (! strncmp(temp, "0", 1))
	{
		galacticRecord(gameVars);
	}
	else if (! strncmp(temp, "1", 1))
	{
		statusReport(gameVars);
	}
	else if (! strncmp(temp, "2", 1))
	{
		torpedoData(gameVars);
	}
	else if (! strncmp(temp, "3", 1))
	{
		navData(gameVars);
	}
	else if (! strncmp(temp, "4", 1))
	{
		dirdistCalc(gameVars);
	}
	else if (! strncmp(temp, "5", 1))
	{
		galaxyMap(gameVars);
	}
	else
	{
		printf("Functions available from Library-Computer:\n\n");
		printf("   0 = Cumulative Galactic Record\n");
		printf("   1 = Status Report\n");
		printf("   2 = Photon Torpedo Data\n");
		printf("   3 = Starbase Nav Data\n");
		printf("   4 = Direction/Distance Calculator\n");
		printf("   5 = Galaxy 'Region Name' Map\n\n");
	}
}


void galacticRecord(GameVariables *gameVars)
{
	int i, j;

	printf("\n     Computer Record of Galaxy for Quadrant %d,%d\n\n", gameVars->entQuad[0], gameVars->entQuad[1]);
	printf("     1     2     3     4     5     6     7     8\n");

	for (i = 0; i < 8; i++)
	{ 
		printf("   ----- ----- ----- ----- ----- ----- ----- -----\n");
		printf("%d", i);
		for (j = 0; j < 8; j++)
		{
		  	printf("   ");

		  	if (gameVars->galaxyRecord[i][j] == 0)
	    	{
		    	printf("***");
	    	}
		  	else
	    	{
		    	printf("%3.3d", gameVars->galaxyRecord[i][j]);
	    	}
		}

		printf("\n");
	}

	printf("   ----- ----- ----- ----- ----- ----- ----- -----\n\n");
}


void statusReport(GameVariables *gameVars)
{
	strcpy(gameVars->tempStr[0], "");

	printf("   Status Report:\n\n");

	if (gameVars->klingLeft > 1)
	{
		strcpy(gameVars->tempStr[0], "s");
	}

	printf("Klingon%s Left: %d\n", gameVars->tempStr[0], gameVars->klingLeft);

	printf("Mission must be completed in %4.1f stardates\n", 
		.1 * (int)((gameVars->stardateStart + 
			gameVars->stardateEnd - gameVars->stardateCurr) * 10));

	if (gameVars->starbaseTotal < 1)
	{
		printf("Your stupidity has left you on your own in the galaxy\n");
		printf(" -- you have no starbases left!\n");
	}
	else
	{  
		strcpy(gameVars->tempStr[0], "s");
		if (gameVars->starbaseTotal < 2)
  		{
	  		strcpy(gameVars->tempStr[0], "");
  		}
		printf("The Federation is maintaining %d starbase%s in the galaxy\n",
	  	gameVars->starbaseTotal, gameVars->tempStr[0]);
  	}

  printf("\n");
}



//8060 REM TORPEDO, BASE NAV, D/D CALCULATOR
void torpedoData(GameVariables *gameVars)
{
  int i;
  strcpy(gameVars->tempStr[0], "");

  if (gameVars->klingQuad <= 0)
  {
    printf("Science Officer Spock reports:\n");
    printf("  'Sensors show no enemy ships in this quadrant.'\n\n");
    return;
  }

  if (gameVars->klingQuad > 1)
    strcpy(gameVars->tempStr[0], "s");
 
  printf("From Enterprise to Klingon battlecriuser%s:\n\n", gameVars->tempStr[0]);

  for (i = 0; i < 3; i++)
  {
    if (gameVars->klingData[i][2] > 0)
    {
      	gameVars->warpFactor = gameVars->klingData[i][0];
      	gameVars->navX  = gameVars->klingData[i][1];
    	gameVars->course = gameVars->entSect[0];
		gameVars->deltaCourseWarpFactor  = gameVars->entSect[1];

      	computeVector(gameVars);
    }
  }
}

void navData(GameVariables *gameVars)
{
	if (gameVars->starbaseQuadrant <= 0)
	{
		printf("Mr. Spock reports,\n");
		printf("  'Sensors show no starbases in this quadrant.'\n\n");
		return;
	}

	gameVars->warpFactor = gameVars->starbaseLocation[0];
	gameVars->navX  = gameVars->starbaseLocation[1];
	gameVars->course = gameVars->entSect[0];
	gameVars->deltaCourseWarpFactor  = gameVars->entSect[1];

	computeVector(gameVars);
}

void dirdistCalc(GameVariables *gameVars)
{
	char temp[6];

	printf("Direction/Distance Calculator\n\n");
	printf("You are at quadrant %d,%d sector %d,%d\n\n", gameVars->entQuad[0], gameVars->entQuad[1],
	/* @@@ doubleToInt(s1), doubleToInt(s2)); */
	(int)gameVars->entSect[0], (int)gameVars->entSect[1]);

	printf("Please enter initial X coordinate: ");
	gets(temp);
	gameVars->course = atoi(temp);

	printf("Please enter initial Y coordinate: ");
	gets(temp);
	gameVars->deltaCourseWarpFactor = atoi(temp);

	printf("Please enter final X coordinate: ");
	gets(temp);
	gameVars->warpFactor = atoi(temp);

	printf("Please enter final Y coordinate: ");
	gets(temp);
	gameVars->navX = atoi(temp);

	computeVector(gameVars);
}


//7390 REM SETUP TO CHANGE CUM GAL RECORD TO GALAXY MAP
void galaxyMap(GameVariables *gameVars)
{
	int i, j, j0;

	gameVars->quadName = 1;

	printf("\n                   The Galaxy\n\n");
	printf("    1     2     3     4     5     6     7     8\n");

	for (i = 1; i <= 8; i++)
	{
		printf("  ----- ----- ----- ----- ----- ----- ----- -----\n");

		printf("%d ", i);

		gameVars->tempQuadCoord[0] = i;
		gameVars->tempQuadCoord[1] = 1;
		quadrantName(gameVars);

		j0 = (int)(11 - (strlen(gameVars->strResults) / 2)); //J0=INT(15-.5*LEN(G2$))

		for (j = 0; j < j0; j++)
		{
			printf(" ");
		}

		printf(gameVars->strResults);

		for (j = 0; j < j0; j++)
	  	{
			printf(" ");
	  	}

		if (! (strlen(gameVars->strResults) % 2))
  		{
	  		printf(" ");
  		}

		gameVars->tempQuadCoord[1] = 5;
		quadrantName(gameVars);

		j0 = (int)(12 - (strlen(gameVars->strResults) / 2));

		for (j = 0; j < j0; j++)
		{	
			printf(" ");
		}
		printf(gameVars->strResults); 

		printf("\n");
	}

	printf("  ----- ----- ----- ----- ----- ----- ----- -----\n\n");

}


void computeVector(GameVariables *gameVars)
{
	gameVars->navX = gameVars->navX - gameVars->deltaCourseWarpFactor;
	gameVars->deltaCourseWarpFactor = gameVars->course - gameVars->warpFactor; // delta of course and warp factor

	if (gameVars->navX <= 0.0)
	{
		if (gameVars->deltaCourseWarpFactor > 0.0)
		{    
		  gameVars->course = 3.0;
		  sub2(gameVars);
		  return;
		}
		else
		{
		  gameVars->course = 5.0;
		  sub1(gameVars);
		  return;
		}
	}
	else if (gameVars->deltaCourseWarpFactor < 0.0)
	{
		gameVars->course = 7.0;
		sub2(gameVars);
		return;
	}
	else
	{
		gameVars->course = 1.0;
		sub1(gameVars);
		return;
	}
}

void sub1(GameVariables *gameVars)
{
	gameVars->navX = fabs(gameVars->navX);
	gameVars->deltaCourseWarpFactor = fabs(gameVars->deltaCourseWarpFactor);

	if (gameVars->deltaCourseWarpFactor <= gameVars->navX)
		{
		printf("  DIRECTION = %4.2f\n", gameVars->course + (gameVars->deltaCourseWarpFactor / gameVars->navX));
		}
	else
		{
		printf("  DIRECTION = %4.2f\n", gameVars->course + (((gameVars->deltaCourseWarpFactor * 2) - gameVars->navX) / gameVars->deltaCourseWarpFactor));
		}

	printf("  DISTANCE = %4.2f\n\n", (gameVars->navX > gameVars->deltaCourseWarpFactor) ? gameVars->navX : gameVars->deltaCourseWarpFactor);
}

void sub2(GameVariables *gameVars)
{
	gameVars->navX = fabs(gameVars->navX);
	gameVars->deltaCourseWarpFactor = fabs(gameVars->deltaCourseWarpFactor);

	if (gameVars->deltaCourseWarpFactor >= gameVars->navX)
		{
		printf("  DIRECTION = %4.2f\n", gameVars->course + (gameVars->navX / gameVars->deltaCourseWarpFactor));
		}
	else
	/* @@@ printf("  DIRECTION = %4.2f\n\n", gameVars->course + (((gameVars->navX * 2) - a) / gameVars->navX)); */
		{
		printf("  DIRECTION = %4.2f\n", gameVars->course + (((gameVars->navX * 2) - gameVars->deltaCourseWarpFactor) / gameVars->navX));
		}

	/* @@@ printf("  DISTANCE = %4.2f\n", (gameVars->navX > a) ? gameVars->navX : a); */
	printf("  DISTANCE = %4.2f\n\n", (gameVars->navX > gameVars->deltaCourseWarpFactor) ? gameVars->navX : gameVars->deltaCourseWarpFactor);
}


void shipDestroyed(GameVariables *gameVars)
{
	printf("The Enterprise has been destroyed. ");
	printf("The Federation will be conquered.\n\n");

	endOfTime(gameVars);
}

void endOfTime(GameVariables *gameVars)
{
	printf("It is stardate %d.\n\n", (int) gameVars->stardateCurr);

	resignCommision(gameVars);
}

void resignCommision(GameVariables *gameVars)
{
	printf("There were %d Klingon Battlecruisers left at the", gameVars->klingLeft);
	printf(" end of your mission.\n\n");

	endOfGame(gameVars);
}

void wonGame(GameVariables *gameVars)
{
  	printf("CONGRATULATION, CAPTAIN!   THE LAST KLINGON BATTLE CRUISER\n");
  	printf("MENACING THE FEDERATION HAS BEEN DESTROYED.\n\n");
 
  	if (gameVars->stardateCurr - gameVars->stardateStart > 0)
    {
    	printf("YOUR EFFICIENCY RATING IS %4.2f\n", 1000 * pow(gameVars->klingStart / (gameVars->stardateCurr - gameVars->stardateStart), 2));
    }

  	endOfGame(gameVars);
}

void endOfGame(GameVariables *gameVars)
{
  char temp[6];

  if (gameVars->starbaseTotal > 0)
    {
      	printf("THE FEDERATION IS IN NEED OF A NEW STARSHIP COMMANDER");
      	printf(" FOR A SIMILAR MISSION -- IF THERE IS A VOLUNTEER,");
      	printf("LET HIM STEP FORWARD AND ENTER 'AYE' ");

      	gets(temp);
      	printf("\n");
      	if (! strncmp(temp, "aye", 3))
      	{
      		//This breaks the eventHandler loop 
        	gameVars->currGame = false;
      	}
      	else
      	{
      		printf("\nMAY THE FORCE BE WITH YOU FRODO!\n");
      		gameVars->running = false;
      		gameVars->currGame = false;
      	}
    }
}


void klingonsMove(GameVariables *gameVars)
{
  int i;

  for (i = 0; i < 3; i++)
    {
      if (gameVars->klingData[i][2] > 0)
        {
          strcpy(gameVars->objInSector, "   ");
          gameVars->tempSectCoord[0] = gameVars->klingData[i][0];
          gameVars->tempSectCoord[1] = gameVars->klingData[i][1];
          insertInQuadrant(gameVars);

          findEmptyPlace(gameVars);

          gameVars->klingData[i][0] = gameVars->tempSectCoord[0];
          gameVars->klingData[i][1] = gameVars->tempSectCoord[1];
          strcpy(gameVars->objInSector, "+K+");
          insertInQuadrant(gameVars);
        }
    }

  klingonsShoot(gameVars);
}

//5990 REM KLINGONS SHOOTING
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
	      	hit = (int) ((gameVars->klingData[i][2] / findDistance(gameVars,i)) * (2 + rnd()));
	      	gameVars->shields = gameVars->shields - hit;
	      	gameVars->klingData[i][2] = (int)(gameVars->klingData[i][2] / (3 + rnd()));

	      	printf("%d unit hit on Enterprise from sector ", hit);
	      	printf("%d, %d\n", gameVars->klingData[i][1], gameVars->klingData[i][2]);

	          	if (gameVars->shields <= 0)
	            {
	              	printf("\n");
	              	shipDestroyed(gameVars);
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
	      	if (gameVars->damage[i] > -0.1 && gameVars->damage[i] < 0)
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
/*
8580 REM FIND EMPTY PLACE IN QUADRANT (FOR THINGS)
8590 R1=FNR(1) : R2=FNR(1) : A$="   " : Z1=R1 : Z2=R2 : GOSUB 8830 : IF Z3=0 THEN 8590
8600 RETURN
*/
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

/*
8660 REM INSERT IN STRING ARRAY FOR QUADRANT
8670 S8=INT(Z2-.5)*3+INT(Z1-.5)*24+1
8675 IF  LEN(A$)<>3 THEN  PRINT "ERROR" : STOP
8680 IF S8=1 THEN Q$=A$+RIGHT$(Q$,189) : RETURN
8690 IF S8=190 THEN Q$=LEFT$(Q$,189)+A$ : RETURN
8700 Q$=LEFT$(Q$,S8-1)+A$+RIGHT$(Q$,190-S8) : RETURN
*/
	int i, j = 0;

	gameVars->quadIndex = ((int)(gameVars->tempSectCoord[1] - 0.5) * 3) + ((int)(gameVars->tempSectCoord[0] - 0.5) * 24) + 1;
	if(strlen(gameVars->objInSector)!=3)  //IF  LEN(A$)<>3 THEN  PRINT "ERROR"
	{
		printf("ERROR\n");
		printf("[DEBUG] Error in insertInQuadrant()\n");	
	}
	for (i = gameVars->quadIndex - 1; i <= gameVars->quadIndex + 1; i++)
	{
    	gameVars->quadDisp[i] = gameVars->objInSector[j++];
    }
}

void getDeviceName(GameVariables *gameVars)
{
/*
8780 REM PRINTS DEVICE NAME
8790 ON R1 GOTO 8792,8794,8796,8798,8800,8802,8804,8806
8792 G2$="WARP ENGINES" : RETURN
8794 G2$="SHORT RANGE SENSORS" : RETURN
8796 G2$="LONG RANGE SENSORS" : RETURN
8798 G2$="PHASER CONTROL" : RETURN
8800 G2$="PHOTON TUBES" : RETURN
8802 G2$="DAMAGE CONTROL" : RETURN
8804 G2$="SHIELD CONTROL" : RETURN
8806 G2$="LIBRARY-COMPUTER" : RETURN
8820 REM STRING COMPARISON IN QUADRANT ARRAY
8830 Z1=INT(Z1+.5) : Z2=INT(Z2+.5) : S8=(Z2-1)*3+(Z1-1)*24+1 : Z3=0
8890 IF MID$(Q$,S8,3)<>A$ THEN RETURN
8900 Z3=1 : RETURN
*/

	static char *deviceName[] = {"Warp Engines","Short Range Sensors",
				"Long Range Sensors","Phaser Control","Photon Tubes",
				"Damage Control","Sheild Control","Library-Computer"};

  	if (gameVars->tempPos[0] < 0 || gameVars->tempPos[0] > 8)
	{
    	gameVars->tempPos[0] = 0;
	}

  	strcpy(gameVars->strResults, deviceName[gameVars->tempPos[1]]);
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
/*
9010 REM QUADRANT NAME IN G2$ FROM Z4,Z5 (=Q1,Q2)
9020 REM CALL WITH G5=1 TO GET REGION NAME ONLY
9030 IF Z5<=4 THEN ON Z4 GOTO 9040,9050,9060,9070,9080,9090,9100,9110
9035 GOTO 9120
9040 G2$="ANTARES" : GOTO 9210
9050 G2$="RIGEL" : GOTO 9210
9060 G2$="PROCYON" : GOTO 9210
9070 G2$="VEGA" : GOTO 9210
9080 G2$="CANOPUS" : GOTO 9210
9090 G2$="ALTAIR" : GOTO 9210
9100 G2$="SAGITTARIUS" : GOTO 9210
9110 G2$="POLLUX" : GOTO 9210
9120 ON Z4 GOTO 9130,9140,9150,9160,9170,9180,9190,9200
9130 G2$="SIRIUS" : GOTO 9210
9140 G2$="DENEB" : GOTO 9210
9150 G2$="CAPELLA" : GOTO 9210
9160 G2$="BETELGEUSE" : GOTO 9210
9170 G2$="ALDEBARAN" : GOTO 9210
9180 G2$="REGULUS" : GOTO 9210
9190 G2$="ARCTURUS" : GOTO 9210
9200 G2$="SPICA"
9210 IF G5<>1 THEN ON Z5 GOTO 9230,9240,9250,9260,9230,9240,9250,9260
9220 RETURN
9230 G2$=G2$+" I" : RETURN
9240 G2$=G2$+" II" : RETURN
9250 G2$=G2$+" III" : RETURN
9260 G2$=G2$+" IV" : RETURN
*/
    static char * quadName[] = {"Antares","Rigel","Procyon","Vega",
    "Canopus","Altair","gameVars->objInSectorgittarius","Pollux","Sirius","Deneb","Capella",
    "Betelgeuse","Aldebaran","Regulus","Arcturus","Spica"};

  	static char * sectName[] = {" I"," II"," III"," IV"};

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


// Other functions

void midStr(char *str1, char *str2, int i, int j)
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

  --i;
  j += i;

  /* @@@ while (i < j && i <= strlen(b)) */
  while (i < j && i <= (int)strlen(str2))
    *str1++ = *(str2 + i++);

  *str1 = '\0';
}



double findDistance(GameVariables *gameVars, int index)
{
/*
	470 DEF FND(D)=SQR((K(I,1)-S1)^2+(K(I,2)-S2)^2)
*/
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
	return(getRandRange(8));
}


int getRandRange(int max)
{
/*
Used to change the range for rand()	assuming min of 0

https://stackoverflow.com/questions/1202687/how-do-i-get-a-specific-range-of-numbers-from-rand

*/
  	return((rand() % max) + 1);
}

int doubleToInt (double dubs)
{
	//INT(Z1+.5) <-- This gets repeated a lot 
  	int num;

  	num = (int) (dubs + 0.5);

  	return(num);
}

