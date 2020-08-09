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


void zeros(GameVariables *gameVars)
{	
	//ints 
	gameVars->dockFlag					= 0;  			
	gameVars->damageRepFlag 			= 0;
	gameVars->currEnergy 				= 0; 
	gameVars->startEnergy				= 0;	
	gameVars->quadName					= 0;
	gameVars->klingStart				= 0; 
	gameVars->klingQuad					= 0;
	gameVars->klingLeft 				= 0; 
	gameVars->klingPow 					= 0;
	gameVars->torpLeft 					= 0; 
	gameVars->torpCap 					= 0;
	gameVars->entQuad[0]				= 0;	
	gameVars->tempPos[0]				= 0;			 			
	gameVars->shields 					= 0; 
	gameVars->stars 					= 0;
	gameVars->quadIndex					= 0;
	gameVars->stardateStart 			= 0; 
	gameVars->stardateEnd				= 0;
	gameVars->tempSectCoord[0]		    = 0;
	gameVars->compare					= 0;
	gameVars->tempQuadCoord[0]			= 0; 
	gameVars->starbaseQuadrant			= 0;
	gameVars->starbaseLocation[0]		= 0;
	gameVars->starbaseTotal				= 0;
	gameVars->galaxy[0][0]				= 0;
	gameVars->galaxyRecord[0][0]		= 0;
	gameVars->klingData[0][0]			= 0;
	gameVars->locationMove[0][0]		= 0;
	gameVars->outOfBoundsFlag			= 0;
	gameVars->n							= 0;
	
	//doubles
	gameVars->repairTime				= 0.0;
	gameVars->entSect[0]		 		= 0.0;
	gameVars->stardateCurr				= 0.0;
	gameVars->warpFactor				= 0.0;
	gameVars->navX 						= 0.0; 
	gameVars->navY 						= 0.0; 	
	gameVars->navX1 					= 0.0; 
	gameVars->navX2						= 0.0;
	gameVars->damage[0]					= 0.0;
	gameVars->course					= 0.0;
	gameVars->deltaCourseWarpFactor		= 0.0;

	//strings
	gameVars->objInSector[0]			= '0';
	gameVars->condition[0]				= '0';
	gameVars->quadDisp[0]				= '0';
	gameVars->tempStr[0][0]				= '0';
	gameVars->command[0]				= '0';
	gameVars->commandList[0][0]			= '0';
	gameVars->strResults[0]				= '0';
}


void eventHandler(GameVariables *gameVars)
{

	
/*
1990 IF S+E>10 THEN IF E>10 OR D(7)=0 THEN 2060
2020 PRINT : PRINT "** FATAL ERROR **   YOU'VE JUST STRANDED YOUR SHIP IN "
2030 PRINT "SPACE" : PRINT "YOU HAVE INSUFFICIENT MANEUVERING ENERGY,";
2040 PRINT " AND SHIELD CONTROL" : PRINT "IS PRESENTLY INCAPABLE OF CROSS";
2050 PRINT "-CIRCUITING TO ENGINE ROOM!!" : GOTO 6220
2060 INPUT "COMMAND: ";A$
*/
	if (gameVars->running == true && gameVars->currGame == true)
	{
		if (gameVars->shields + gameVars->currEnergy <= 10 || (gameVars->currEnergy < 10 || 
				gameVars->damage[6] < 0)) //1990 IF S+E>10 THEN IF E>10 OR D(7)=0 THEN 2060
	    {
	  		printf("\n** FATAL ERROR **   YOU'VE JUST STRANDED YOUR SHIP IN SPACE");
	  		printf("YOU HAVE INSUFFICIENT MANEUVERING ENERGY,\n");
	  		printf("AND SHIELD CONTROL");
	  		printf("IS PRESENTLY INCAPABLE OF CROSS\n");
	  		printf("-CIRCUITING TO ENGINE ROOM!!\n\n");
	  		endOfTime(gameVars);
	    }

	    // FOR I=1 TO 9 : IF LEFT$(A$,3)<>MID$(A1$,3*I-2,3) THEN 2160
		// 2140 ON I GOTO 2300,1980,4000,4260,4700,5530,5690,7290,6270
		printf("COMMAND? ");
		gets(gameVars->command);
	  	printf("\n");
		if(strcmp(gameVars->command,"nav")==0)
		{
			_courseControl(gameVars); //2300
		}
		else if (strcmp(gameVars->command,"srs")==0)
		{
			shortRangeScan(gameVars); //1980		
		}
		else if (strcmp(gameVars->command,"lrs")==0)
		{
			_longRangeScan(gameVars); //4000		
		}
		else if (strcmp(gameVars->command,"pha")==0)
		{
			_phaserControl(gameVars); //4260
		}
		else if (strcmp(gameVars->command,"tor")==0)
		{
			photonTorpedoes(gameVars); //4700	
		}
		else if (strcmp(gameVars->command,"she")==0)
		{
			shieldControl(gameVars); //5530	
		}
		else if (strcmp(gameVars->command, "dam")==0)
	    {
	        damageControl(gameVars); //5690
	    }
		else if (strcmp(gameVars->command,"com")==0)
		{
			libraryComputer(gameVars); //7290
		}
		else if (strcmp(gameVars->command,"xxx")==0)
		{
			endMission(gameVars); //6270		
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
	gameVars->stardateCurr		=(int)(getRandRange(20)+20)*100;  	// T
	gameVars->stardateStart		=gameVars->stardateCurr;	// T0
	gameVars->stardateEnd 		= 25+(int)(getRandRange(10)); 	 	// T9

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
	//IF K9>T9 THEN T9=K9+1
	if (gameVars->klingLeft > gameVars->stardateEnd)
	{
    	gameVars->stardateEnd = gameVars->klingLeft + 1;
	}
	//1150 IF G(Q1,Q2)<200 THEN G(Q1,Q2)=G(Q1,Q2)+120 : K9=K9+1
	//1160 B9=1 : G(Q1,Q2)=G(Q1,Q2)+10 : Q1=FNR(1) : Q2=FNR(1)
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

    // 1200 K7=K9 : IF B9<>1 THEN X$="S" : X0$=" ARE "
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
			gameVars->stardateStart + gameVars->stardateEnd, 
			gameVars->stardateEnd, 
			gameVars->tempStr[1]);
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
	gameVars->repairTime = (double) (getRandRange(100)/100)/50; // D4=.5*RND(1) //sets to a value 0 - 1 then takes half
	gameVars->galaxyRecord[gameVars->tempQuadCoord[0]][gameVars->tempQuadCoord[1]] = 
			gameVars->galaxy[gameVars->entQuad[0]][gameVars->entQuad[1]];

	if (gameVars->entQuad[0] >= 0 || gameVars->entQuad[0] <= 7 || 
		gameVars->entQuad[1] >= 0 || gameVars->entQuad[1] <= 7)
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
	gameVars->starbaseQuadrant = (int)(gameVars->galaxy[gameVars->entQuad[0]][gameVars->entQuad[1]] * .1) - 10 * gameVars->klingQuad;
	gameVars->stars = gameVars->galaxy[gameVars->entQuad[0]][gameVars->entQuad[1]] - 100 * gameVars->klingQuad - 10 * gameVars->starbaseQuadrant;

	// IF K3=0 THEN 1590
	if (gameVars->klingQuad > 0)
	{
	  	printf("COMBAT AREA  CONDITION RED\n");
	  	//IF S>200 THEN 1590 <-- because basic is apparent written for to be as unintuitive as possible...
	  	if (gameVars->shields < 200) // so this is technically the else logic... 
	  	{
	    	printf("SHIELDS DANGEROUSLY LOW\n");
		}
	}
	// 1590 FOR I=1 TO 3 : K(I,1)=0 : K(I,2)=0 : NEXT I
	for (i = 0; i < 3; i++)
	{
	  	gameVars->klingData[i][0] = 0;
	  	gameVars->klingData[i][1] = 0;
	  	gameVars->klingData[i][2] = 0;
	}
	// Q$=Z$+Z$+Z$+Z$+Z$+Z$+Z$+LEFT$(Z$,17) == 192 
	// because --> 270 Z$="                         " == 25x'\s'
	for (i = 0; i <= 192; i++)
	{
		gameVars->quadDisp[i] = ' ';
	}
	gameVars->quadDisp[193] = '\0';

	// Position Enterprise
	strcpy(gameVars->objInSector, "<E>");
	gameVars->tempSectCoord[0] = (int)gameVars->entSect[0];
	gameVars->tempSectCoord[1] = (int)gameVars->entSect[1];
	insertInQuadrant(gameVars);

	// Position Klingons
	//IF K3<1 THEN 1820
	//<else>FOR I=1 TO K3 : GOSUB 8590 : A$="+K+" : Z1=R1 : Z2=R2 <-- this type of logic is actual insanity
	if (gameVars->klingQuad > 0)// anyway this is the else statment...
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

	// Position Starbases
	/*
	IF B3<1 THEN 1910
	1880 GOSUB 8590 : A$=">B<" : Z1=R1 : B4=R1 : Z2=R2 : B5=R2 : GOSUB 8670

	*/
	if (gameVars->starbaseQuadrant > 0)
	{
	 	findEmptyPlace(gameVars);
	 	strcpy(gameVars->objInSector, ">B<");
  		gameVars->tempSectCoord[0] = gameVars->tempPos[0];
	  	gameVars->tempSectCoord[1] = gameVars->tempPos[1];
	 	insertInQuadrant(gameVars);

	 	gameVars->starbaseLocation[0] = gameVars->tempPos[0];
	 	gameVars->starbaseLocation[1] = gameVars->tempPos[1];
	}

	// Position Stars
	/*
	1910 FOR I=1 TO S3 : GOSUB 8590 : A$=" * " : Z1=R1 : Z2=R2 : GOSUB 8670 : NEXT I
	*/
	for (i = 1; i <= gameVars->stars; i++)
	{
  		findEmptyPlace(gameVars);
  		strcpy(gameVars->objInSector, " * ");
  		gameVars->tempSectCoord[0] = gameVars->tempPos[0];
	  	gameVars->tempSectCoord[1] = gameVars->tempPos[1];
  		insertInQuadrant(gameVars);
	}
	// 1980 GOSUB 6430 <-- thats srs
	shortRangeScan(gameVars);
}


void _courseControl(GameVariables *gameVars)
{
/*
2290 REM COURSE CONTROL BEGINS HERE
2300 INPUT "COURSE (0-9) ";C1 : IF C1=9 THEN C1=1
2310 IF C1>=1 AND C1<9 THEN 2350
2330 PRINT "   LT. SULU REPORTS, 'INCORRECT COURSE DATA, SIR!'" : GOTO 1990
2350 X$="8" : IF D(1)<0 THEN X$="0.2"
2360 PRINT "WARP FACTOR (0-";X$;") "; : INPUT W1 : IF D(1)<0 AND W1>.2 THEN 2470
2380 IF W1>0 AND W1<=8 THEN 2490
2390 IF W1=0 THEN 1990
2420 PRINT "   CHIEF ENGINEER SCOTT REPORTS 'THE ENGINES WON'T TAKE";
2430 PRINT " WARP ";W1;"!'" : GOTO 1990
2470 PRINT "WARP ENGINES ARE DAMAGED.  MAXIUM SPEED = WARP 0.2" : GOTO 1990
2490 N=INT(W1*8+.5) : IF E-N>=0 THEN 2590
2500 PRINT "ENGINEERING REPORTS   'INSUFFICIENT ENERGY AVAILABLE"
2510 PRINT "                       FOR MANEUVERING AT WARP";W1;"!'"
2530 IF S<N-E OR D(7)<0 THEN 1990
2550 PRINT "DEFLECTOR CONTROL ROOM ACKNOWLEDGES ";S;" UNITS OF ENERGY"
2560 PRINT "                         PRESENTLY DEPLOYED TO SHIELDS."
2570 GOTO 1990
*/

	int i, q4, q5;
	char temp[6];
	
	// gameVars->n = (int)(gameVars->warpFactor * 8.0); //2490 N=INT(W1*8+.5)
	printf("COURSE (0-9): ");

	gets(temp);

	printf("\n");

	gameVars->course = atof(temp);

	if (gameVars->course == 9.0) //IF C1=9 THEN C1=1
	{
		gameVars->course = 1.0;
	}
	// This line is implicit  
	// 2310 IF C1>=1 AND C1<9 THEN 2350
	// PRINT "   LT. SULU REPORTS, 'INCORRECT COURSE DATA, SIR!'" : GOTO 1990
	if (gameVars->course < 0.0 || gameVars->course > 9.0)
	{
	  printf("LT. SULU REPORTS, 'INCORRECT COURSE DATA, SIR!'\n");
	  return;
	}
	//2350 X$="8" : IF D(1)<0 THEN X$="0.2"
	strcpy(gameVars->tempStr[0], "8");
	if (gameVars->damage[0] < 0.0)
	{
		strcpy(gameVars->tempStr[0], "0.2");
	}

	printf("WARP FACTOR (0-%s): ", gameVars->tempStr[0]);
	gets(temp);
	printf("\n");
	gameVars->warpFactor = atof(temp);

	//2350 X$="8" : IF D(1)<0 THEN X$="0.2"
	if (gameVars->damage[0] < 0.0 && gameVars->warpFactor > 0.21)
	{
	  printf("WARP ENGINES ARE DAMAGED.  MAXIUM SPEED = WARP 0.2");
	  return;
	}
	//2380 IF W1>0 AND W1<=8 THEN 2490 <-- this line's else statemnts are below
	//2390 IF W1=0 THEN 1990
	if (gameVars->warpFactor <= 0.0)
		return;
	if (gameVars->warpFactor > 8.1)
	{
		printf("CHIEF ENGINEER SCOTT REPORTS 'THE ENGINES WON'T TAKE WARP %4.1f!'\n", gameVars->warpFactor);
	 	return;
	}

	//2490 N=INT(W1*8+.5) : IF E-N>=0 THEN 2590
	gameVars->n = doubleToInt(gameVars->warpFactor * 8.0); //N=INT(W1*8+.5)
	if (gameVars->currEnergy - gameVars->n < 0) // so opposite of line 2490
	{
	  printf("ENGINEERING REPORTS   'INSUFFICIENT ENERGY AVAILABLE for maneuvering");
	  printf("                       FOR MANEUVERING AT WARP %4.1f!'\n", gameVars->warpFactor);

	  if (gameVars->shields < gameVars->n - gameVars->currEnergy || gameVars->damage[6] < 0.0)
	    {
	      printf("DEFLECTOR CONTROL ROOM ACKNOWLEDGES\n");
	      printf("  %d UNITS OF ENERGY PRESENTLY DEPLOYED TO SHIELDS.\n", gameVars->shields);
	    }

	  return;
	}
	// 2580 REM KLINGONS MOVE/FIRE ON MOVING STARSHIP . . .
	if(gameVars->klingQuad!=0) //2590 ... IF K(I,3)=0 THEN 2700
	{	
		// printf("[DEBUG] gameVars->klingQuad : %d\n",gameVars->klingQuad);
		_klingonsMove(gameVars); 
	}

	_repairDamage(gameVars);
	
	// 3060 REM BEGIN MOVING STARSHIP
	strcpy(gameVars->objInSector, "   ");
	gameVars->tempSectCoord[0] = (int)gameVars->entSect[0];
	gameVars->tempSectCoord[1] = (int)gameVars->entSect[1];
	insertInQuadrant(gameVars); //8670
	//3110 X1=C(C1,1)+(C(C1+1,1)-C(C1,1))*(C1-INT(C1))
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
	q4 = gameVars->entQuad[0];				//temp entQuad
	q5 = gameVars->entQuad[0];				//temp entQuad
	
	//3170 FOR I=1 TO N : S1=S1+X1 : S2=S2+X2 : IF S1<1 OR S1>=9 OR S2<1 OR S2>=9 THEN 3500
	for (i = 0; i <= gameVars->n; i++)
	{
		gameVars->entSect[0] = gameVars->entSect[0] + gameVars->navX1;
	  	gameVars->entSect[1] = gameVars->entSect[1] + gameVars->navX2;
		gameVars->tempSectCoord[0] = (int)gameVars->entSect[0];
		gameVars->tempSectCoord[1] = (int)gameVars->entSect[1];

	  	if (gameVars->tempSectCoord[0] < 0 || 
	  		gameVars->tempSectCoord[0] > 7 ||
	  	  	gameVars->tempSectCoord[1] < 0 || 
	  	 	gameVars->tempSectCoord[1] > 7)
	    {
	    	// printf("[DEBUG] gameVars->tempSectCoord[0]: %d\n", gameVars->tempSectCoord[0]);
	    	// printf("[DEBUG] gameVars->tempSectCoord[1]: %d\n", gameVars->tempSectCoord[1]);
	      	_outOfBounds(gameVars);
	      	_completeManeuver(gameVars);
	      	return;
	    }

	  	// stringCompare(gameVars);

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

	_completeManeuver(gameVars);
}


void _completeManeuver(GameVariables *gameVars)
{
/*
Function that completes courseControl

3370 A$="<E>" : Z1=INT(S1) : Z2=INT(S2) : GOSUB 8670 : GOSUB 3910 : T8=1
3430 IF W1<1 THEN T8=.1*INT(10*W1)
3450 T=T+T8 : IF T>T0+T9 THEN 6220
*/

	double timeFactor;				// t8

	strcpy(gameVars->objInSector, "<E>");
	gameVars->tempSectCoord[0] = (int)gameVars->entSect[0];
	gameVars->tempSectCoord[1] = (int)gameVars->entSect[1];
	insertInQuadrant(gameVars);
	maneuverEnergy(gameVars);

	timeFactor = 1.0;

	if (gameVars->warpFactor < 1.0)
	{
		timeFactor = 0.1 * (int)(gameVars->warpFactor*10);
	}

	gameVars->stardateCurr = gameVars->stardateCurr + timeFactor;

	if (gameVars->stardateCurr > gameVars->stardateStart + gameVars->stardateEnd)
	{	
		endOfTime(gameVars); //6220
	}

	shortRangeScan(gameVars);
}


void _outOfBounds(GameVariables *gameVars)
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
	
	gameVars->navX = (8 * gameVars->entQuad[0]) + 
					  gameVars->navX + (gameVars->n * gameVars->navX1);
	gameVars->navY = (8 * gameVars->entQuad[1]) + 
					  gameVars->navY + (gameVars->n * gameVars->navY);

	gameVars->entQuad[0] = (int)(gameVars->navX / 8);
	gameVars->entQuad[1] = (int)(gameVars->navY / 8);
	gameVars->entSect[0] = (gameVars->navX - gameVars->entQuad[0] * 8);
	gameVars->entSect[1] = (gameVars->navY - gameVars->entQuad[1] * 8);
	// printf("[DEBUG] gameVars->entSect[0]: %f\n", gameVars->entSect[0]);
	// printf("[DEBUG] gameVars->entSect[1]: %f\n", gameVars->entSect[1]);
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
	// printf("[DEBUG] here2\n");
	if (gameVars->stardateCurr > gameVars->stardateStart + gameVars->stardateEnd)
	{
    	endOfTime(gameVars);
		gameVars->stardateCurr = gameVars->stardateCurr + 1;
		newQuadrant(gameVars);
	}
}


void maneuverEnergy(GameVariables *gameVars)
{
/*
3900 REM MANEUVER ENERGY S/R **
3910 E=E-N-10 : IF E>=0 THEN RETURN
3930 PRINT "SHIELD CONTROL SUPPLIES ENERGY TO COMPLETE THE MANEUVER."
3940 S=S+E : E=0 : IF S<=0 THEN S=0
*/
	// printf("[DEBUG] maneuverEnergy()\n");
  	gameVars->currEnergy = gameVars->currEnergy - gameVars->n - 10;

  	if (gameVars->currEnergy >= 0)
  	{
  		// printf("[DEBUG] if (gameVars->currEnergy >= 0)\n");
    	return;
  	}

  	printf("SHIELD CONTROL SUPPLIES ENERGY TO COMPLETE THE MANEUVER.\n\n");
  	gameVars->shields = gameVars->shields + gameVars->currEnergy;
  	gameVars->currEnergy = 0;

  	if (gameVars->shields <= 0)
  	{
  		// printf("[DEBUG] if (gameVars->shields <= 0)\n");
    	gameVars->shields = 0;
    }
}	


void shortRangeScan(GameVariables *gameVars)
{

/*
REM SHORT RANGE SENSOR SCAN & STARTUP SUBROUTINE
6430 FOR I=S1-1 TO S1+1 : FOR J=S2-1 TO S2+1
6450 IF INT(I+.5)<1ORINT(I+.5)>8ORINT(J+.5)<1ORINT(J+.5)>8 THEN 6540
6490 A$=">B<" : Z1=I : Z2=J : GOSUB 8830 : IF Z3=1 THEN 6580
6540 NEXT J : NEXT I : D0=0 : GOTO 6650
6580 D0=1 : C$="DOCKED" : E=E0 : P=P0
6620 PRINT "SHIELDS DROPPED FOR DOCKING PURPOSES" : S=0 : GOTO 6720
6650 IF K3>0 THEN C$="*RED*" : GOTO 6720
6660 C$="GREEN" : IF E<E0*.1 THEN C$="YELLOW"
6720 IF D(2)>=0 THEN 6770
6730 PRINT : PRINT "*** SHORT RANGE SENSORS ARE OUT ***" : PRINT : RETURN
6770 O1$="---------------------------------" : PRINT O1$ : FOR I=1 TO 8
6820 FOR J=(I-1)*24+1 TO (I-1)*24+22 STEP 3 : PRINT " ";MID$(Q$,J,3); : NEXT J
6830 ON I GOTO 6850,6900,6960,7020,7070,7120,7180,7240
6850 PRINT "        STARDATE           ";INT(T*10)*.1 : GOTO 7260
6900 PRINT "        CONDITION          ";C$ : GOTO 7260
6960 PRINT "        QUADRANT           ";Q1;",";Q2 : GOTO 7260
7020 PRINT "        SECTOR             ";S1;",";S2 : GOTO 7260
7070 PRINT "        PHOTON TORPEDOES   ";INT(P) : GOTO 7260
7120 PRINT "        TOTAL ENERGY       ";INT(E+S) : GOTO 7260
7180 PRINT "        SHIELDS            ";INT(S) : GOTO 7260
7240 PRINT "        KLINGONS REMAINING ";INT(K9)
*/
	int i, j;
	//6650 IF K3>0 THEN C$="*RED*" : GOTO 6720
	//6660 C$="GREEN" : IF E<E0*.1 THEN C$="YELLOW"
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

	//6430 FOR I=S1-1 TO S1+1 : FOR J=S2-1 TO S2+1
  	for (i = (int)(gameVars->entSect[0]-1); i <= (int)(gameVars->entSect[0]+1); i++)
  	{
    	for (j = (int)(gameVars->entSect[1]-1); j <= (int)(gameVars->entSect[1]+1); j++)
      	{	
      		// IF INT(I+.5)<1ORINT(I+.5)>8ORINT(J+.5)<1ORINT(J+.5)>8 THEN 6540
	      	if(i < 0 || i > 7 || j < 0 || j > 7)
	      	{
	      		return;
	      	}
	      	else
	        {
	          strcpy(gameVars->objInSector, ">B<");
	          gameVars->tempSectCoord[0] = i;
	          gameVars->tempSectCoord[1] = j;
	          stringCompare(gameVars);
	          //IF Z3=1 THEN 6580 ..D0=1 : C$="DOCKED" : E=E0 : P=P0
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
  	//6720 IF D(2)>=0 THEN 6770... else...
  	if (gameVars->damage[1] < 0.0)
    {
      printf("\n*** SHORT RANGE SENSORS ARE OUT ***\n");
      return;
    }
  	printf("------------------------\n");
  	
  	for (i = 0; i < 8; i++)
    {
      	for (j = 0; j < 24; j++)
      	{
        	putchar(gameVars->quadDisp[i * 24 + j]); 
      	}
/*
FOR J=(I-1)*24+1 TO (I-1)*24+22 STEP 3 : PRINT " ";MID$(Q$,J,3); : NEXT J
6830 ON I GOTO 6850,6900,6960,7020,7070,7120,7180,7240
6850 PRINT "        STARDATE           ";INT(T*10)*.1 : GOTO 7260
6900 PRINT "        CONDITION          ";C$ : GOTO 7260
6960 PRINT "        QUADRANT           ";Q1;",";Q2 : GOTO 7260
7020 PRINT "        SECTOR             ";S1;",";S2 : GOTO 7260
7070 PRINT "        PHOTON TORPEDOES   ";INT(P) : GOTO 7260
7120 PRINT "        TOTAL ENERGY       ";INT(E+S) : GOTO 7260
7180 PRINT "        SHIELDS            ";INT(S) : GOTO 7260
7240 PRINT "        KLINGONS REMAINING ";INT(K9)
*/
  	if (i == 0)
    	printf("    STARDATE            %d\n", (int) gameVars->stardateCurr);
  	if (i == 1)
    	printf("    CONDITION           %s\n", gameVars->condition);
  	if (i == 2)
    	printf("    QUADRANT            %d, %d\n",  gameVars->entQuad[0], gameVars->entQuad[1]);
  	if (i == 3)
    	printf("    SECTOR              %d, %d\n", doubleToInt(gameVars->entSect[0]), doubleToInt(gameVars->entSect[1]));
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


void _longRangeScan (GameVariables *gameVars)
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
	if (gameVars->damage[2] < 0.0)
	{
		printf("LONG RANGE SENSORS ARE INOPERABLE\n");
	}
	
	printf("LONG RANGE SCAN FOR QUADRANT %d, %d\n", 
			gameVars->entQuad[0], gameVars->entQuad[1]);
	printf("    -------------------\n");

	for (int i = gameVars->entQuad[0] - 1; i <= gameVars->entQuad[0] + 1; i++)
	{
		for (int j = gameVars->entQuad[1] - 1; j <= gameVars->entQuad[1] + 1; j++)
			{
				if (((i > 0) && (i < 8)) && ((j > 0) && (j < 8)))
				{
					gameVars->galaxyRecord[i][j] = gameVars->galaxy[i][j];
					printf(" %3.3d :",gameVars->galaxyRecord[i][j]);
				}
				else 
				{
					printf(" *** :");
				}
			}
		printf("\n");
	}
	printf("    -------------------\n");	
}


void _phaserControl(GameVariables *gameVars)
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
	int firePhasers = 3000; // X
	int maxDamage;
	int damageDone;
	//4260 IF D(4)<0 THEN PRINT "PHASERS INOPERATIVE" : GOTO 1990
	if (gameVars->damage[3] < 0)
	{
		printf("PHASERS INOPERATIVE\n");
		return;
	}
	//IF K3>0 THEN 4330... else...
	if (gameVars->klingStart <= 0)
	{
		printf("SCIENCE OFFICER SPOCK REPORTS  'SENSORS SHOW NO ENEMY SHIPS\n");
		printf("                                IN THIS QUADRANT'\n");
		return;
	}
	//4330 IF D(8)<0 THEN PRINT "COMPUTER FAILURE HAMPERS ACCURACY"
	if (gameVars->damage[7] < 0)
	{
		printf("COMPUTER FAILURE HAMPERS ACCURACY\n");
	}

	printf("PHASERS LOCKED ON TARGET;  \n");
	// This recursive behaviour is essentially a while loop
	// kind of cool.
	//4360 PRINT "ENERGY AVAILABLE =";E;" UNITS"
	//4370 INPUT "NUMBER OF UNITS TO FIRE? ";X : IF X<=0 THEN 1990
	//4400 IF E-X<0 THEN 4360
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
	//4410 E=E-X : IF D(7)<0 THEN X=X*RND(1)
	if (gameVars->damage[7] < 0)
	{
		firePhasers = (int)(firePhasers*RandomToOne());
	}
	gameVars->currEnergy = gameVars->currEnergy - firePhasers;
	maxDamage = (int)(firePhasers/gameVars->klingStart);
	
	//4450 H1=INT(X/K3) : FOR I=1 TO 3 : IF K(I,3)<=0 THEN 4670
	for (int i = 0; i < 3; i++)
	{
		if (gameVars->klingData [i][2] <= 0)
		{
			return;
		}
		
		damageDone = (maxDamage/findDistance(gameVars,i))*(RandomToOne()+2);
		
		//IF H>.15*K(I,3) THEN 4530... else...
		if (damageDone > (0.15 * gameVars->klingData[i][2]))
		{
			printf("SENSORS SHOW NO DAMAGE TO ENEMY AT %d, %d\n", 
				gameVars->klingData[i][0],gameVars->klingData[i][1]); //GOTO 4670
			return; //4670 NEXTI : GOSUB 6000 : GOTO 1990
		}
		
		gameVars->klingData[i][2] = gameVars->klingData[i][2] - damageDone; 
		
		printf("%d UNIT HIT ON KLINGON AT SECTOR %d, %d\n", 
			damageDone, gameVars->klingData [i][0], gameVars->klingData[i][1]);
		// IF K(I,3)<=0 THEN PRINT "*** KLINGON DESTROYED ***" : GOTO 4580
		if (gameVars->klingData[i][2] <= 0)
		{
			printf("*** KLINGON DESTROYED ***");
			gameVars->klingQuad--;
			gameVars->klingLeft--;
			gameVars->tempSectCoord[0] = gameVars->klingData[i][0];
			gameVars->tempSectCoord[1] = gameVars->klingData[i][1];
			insertInQuadrant(gameVars);
			gameVars->klingData[i][2] = 0;
			gameVars->galaxy[gameVars->entQuad[0]][gameVars->entQuad[1]] = 
				gameVars->galaxy [gameVars->entQuad[0]][gameVars->entQuad[1]] - 100;
			gameVars->galaxyRecord[gameVars->entQuad[0]][gameVars->entQuad[1]] = 
				gameVars->galaxy [gameVars->entQuad[0]][gameVars->entQuad[1]];
			//IF K9<=0 THEN 6370 // WIN!!
			if (gameVars->klingLeft <= 0)
			{
				wonGame(gameVars);
			}
		}
		//4560 PRINT "   (SENSORS SHOW";K(I,3);" UNITS REMAINING)" : GOTO 4670
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

	printf("Course (1-9): ");

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

	strcpy(gameVars->objInSector, ">B<");
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
	      	endMission(gameVars);
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
/*
7280 REM LIBRARY COMPUTER CODE
7290 IF D(8)<0 THEN PRINT "COMPUTER DISABLED" : GOTO 1990
7320 INPUT "COMPUTER ACTIVE AND AWAITING COMMAND: ";A : IF A<0 THEN 1990
7350 PRINT : H8=1 : ON A+1 GOTO 7540,7900,8070,8500,8150,7400
7360 PRINT "FUNCTIONS AVAILABLE FROM LIBRARY-COMPUTER : "
7370 PRINT "   0 = CUMULATIVE GALACTIC RECORD"
7372 PRINT "   1 = STATUS REPORT"
7374 PRINT "   2 = PHOTON TORPEDO DATA"
7376 PRINT "   3 = STARBASE NAV DATA"
7378 PRINT "   4 = DIRECTION/DISTANCE CALCULATOR"
7380 PRINT "   5 = GALAXY 'REGION NAME' MAP" : PRINT : GOTO 7320
*/

	if (gameVars->damage[7] < 0.0)
	{
		printf("COMPUTER DISABLED\n");
  		return;
	}

	printf("COMPUTER ACTIVE AND AWAITING COMMAND: ");
	char temp[6];
	gets(temp);
	printf("\n");
	if (! strncmp(temp, "0", 1))
	{
		_galacticRecord(gameVars);	//7540
	}
	else if (! strncmp(temp, "1", 1))
	{
		_statusReport(gameVars); 	//7900
	}
	else if (! strncmp(temp, "2", 1))
	{
		_torpedoData(gameVars);		//8070
	}
	else if (! strncmp(temp, "3", 1))
	{
		_navData(gameVars);			//8500	
	}
	else if (! strncmp(temp, "4", 1))
	{
		dirdistCalc(gameVars);		//8150
	}
	else if (! strncmp(temp, "5", 1))
	{
		galaxyMap(gameVars);		//7400
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


void _galacticRecord(GameVariables *gameVars)
{
/*
7530 REM CUM GALACTIC RECORD
7540 REM INPUT "DO YOU WANT A HARDCOPY? IS THE TTY ON (Y/N) ";A$
7542 REM IF A$="Y" THEN POKE 1229,2 : POKE1237,3 : NULL1
7543 PRINT : PRINT "        ";
7544 PRINT "COMPUTER RECORD OF GALAXY FOR QUADRANT ";Q1;",";Q2
7546 PRINT
7550 PRINT "       1     2     3     4     5     6     7     8"
7560 O1$="     ----- ----- ----- ----- ----- ----- ----- -----"
7570 PRINT O1$ : FOR I=1 TO 8 : PRINT I;"  "; : IF H8=0 THEN 7740
7630 FOR J=1 TO 8 : PRINT "   "; : IF Z(I,J)=0 THEN PRINT "***"; : GOTO 7720
7700 PRINT RIGHT$(STR$(Z(I,J)+1000),3);
7720 NEXT J : GOTO 7850
7740 Z4=I : Z5=1 : GOSUB 9030 : J0=INT(15-.5*LEN(G2$)) : PRINT TAB(J0);G2$;
7800 Z5=5 : GOSUB 9030 : J0=INT(39-.5*LEN(G2$)) : PRINT TAB(J0);G2$;
7850 PRINT : PRINT O1$ : NEXT I : PRINT : GOTO 1990
*/	

//This function is only called by libraryComputer 

	int i, j;

	printf("\nCOMPUTER RECORD OF GALAXY FOR QUADRANT %d,%d\n\n", gameVars->entQuad[0], gameVars->entQuad[1]);
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


void _statusReport(GameVariables *gameVars)
{
/*
7890 REM STATUS REPORT
7900 PRINT "   STATUS REPORT : " : X$="" : IF K9>1 THEN X$="S"
7940 PRINT "KLINGON";X$;" LEFT :  ";K9
7960 PRINT "MISSION MUST BE COMPLETED IN ";.1*INT((T0+T9-T)*10);" STARDATES"
7970 X$="S" : IF B9<2 THEN X$="" : IF B9<1 THEN 8010
7980 PRINT "THE FEDERATION IS MAINTAINING ";B9;" STARBASE";X$;" IN THE GALAXY"
7990 GOTO 5690
8010 PRINT "YOUR STUPIDITY HAS LEFT YOU ON YOUR OWN IN"
8020 PRINT "THE GALAXY -- YOU HAVE NO STARBASES LEFT!" : GOTO 5690
*/

//This function is only called by libraryComputer

	strcpy(gameVars->tempStr[0], "");

	printf("   STATUS REPORT : \n\n");

	if(gameVars->klingLeft > 1)
	{
		strcpy(gameVars->tempStr[0], "S");
	}
	printf("KLINGON%s LEFT :  %d\n", gameVars->tempStr[0], gameVars->klingLeft);

	printf("MISSION MUST BE COMPLETED IN %4.1f STARDATES\n", 
		.1 * (int)((gameVars->stardateStart + 
			gameVars->stardateEnd - gameVars->stardateCurr) * 10));
	//7970 X$="S" : IF B9<2 THEN X$="" : IF B9<1 THEN 8010
	if(gameVars->starbaseTotal < 1)//8010
	{
		printf("YOUR STUPIDITY HAS LEFT YOU ON YOUR OWN IN\n");
		printf("THE GALAXY -- YOU HAVE NO STARBASES LEFT!\n");
	}
	else
	{  
		strcpy(gameVars->tempStr[0], "s");
		if (gameVars->starbaseTotal < 2)
  		{
	  		strcpy(gameVars->tempStr[0], "");
  		}
		printf("THE FEDERATION IS MAINTAINING %d STARBASE%s IN THE GALAXY\n",
	  	gameVars->starbaseTotal, gameVars->tempStr[0]);
  	}

  printf("\n");
}


void _torpedoData(GameVariables *gameVars)
{
/*
8060 REM TORPEDO, BASE NAV, D/D CALCULATOR
8070 IF K3<=0 THEN 4270
8080 X$="" : IF K3>1 THEN X$="S"
8090 PRINT "FROM ENTERPRISE TO KLINGON BATTLE CRUSER";X$
8100 H8=0 : FOR I=1 TO 3 : IF K(I,3)<=0 THEN 8480
8110 W1=K(I,1) : X=K(I,2)
8120 C1=S1 : A=S2 : GOTO 8220
8150 PRINT "DIRECTION/DISTANCE CALCULATOR : "
8160 PRINT "YOU ARE AT QUADRANT ";Q1;",";Q2;" SECTOR ";S1;",";S2
8170 PRINT "PLEASE ENTER" : INPUT "  INITIAL COORDINATES (X,Y) ";C1,A
8200 INPUT "  FINAL COORDINATES (X,Y) ";W1,X
8220 X=X-A : A=C1-W1 : IF X<0 THEN 8350
8250 IF A<0 THEN 8410
8260 IF X>0 THEN 8280
8270 IF A=0 THEN C1=5 : GOTO 8290
8280 C1=1
8290 IF ABS(A)<=ABS(X) THEN 8330
8310 PRINT "DIRECTION =";C1+(((ABS(A)-ABS(X))+ABS(A))/ABS(A)) : GOTO 8460
8330 PRINT "DIRECTION =";C1+(ABS(A)/ABS(X)) : GOTO 8460
8350 IF A>0 THEN C1=3 : GOTO 8420
8360 IF X<>0 THEN C1=5 : GOTO 8290
8410 C1=7
8420 IF ABS(A)>=ABS(X) THEN 8450
8430 PRINT "DIRECTION =";C1+(((ABS(X)-ABS(A))+ABS(X))/ABS(X)) : GOTO 8460
8450 PRINT "DIRECTION =";C1+(ABS(X)/ABS(A))
8460 PRINT "DISTANCE =";SQR(X^2+A^2) : IF H8=1 THEN 1990
8480 NEXT I : GOTO 1990
8500 IF B3<>0 THEN PRINT "FROM ENTERPRISE TO STARBASE : " : W1=B4 : X=B5 : GOTO 8120
8510 PRINT "MR. SPOCK REPORTS,  'SENSORS SHOW NO STARBASES IN THIS";
8520 PRINT " QUADRANT.'" : GOTO 1990
*/

//This function is only called by libraryComputer

  	int i;
  	strcpy(gameVars->tempStr[0], "");
  	//IF K3<=0 THEN 4270
  	if (gameVars->klingQuad <= 0)
  	{
	    printf("SCIENCE OFFICER SPOCK REPORTS  'SENSORS SHOW NO ENEMY SHIPS\n");
	    printf("                                IN THIS QUADRANT'\n\n");
	    return; //1990
  	}
	else if (gameVars->klingQuad > 1)
	{
    	strcpy(gameVars->tempStr[0], "s");
	}

  	printf("FROM ENTERPRISE TO KLINGON BATTLE CRUSER%s:\n\n", gameVars->tempStr[0]);

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
    	else
    	{
    		return; //IF K(I,3)<=0 THEN 8480 .. 8480 NEXT I : GOTO 1990
    	}
  	}
}

void _navData(GameVariables *gameVars)
{
/*
8500 IF B3<>0 THEN PRINT "FROM ENTERPRISE TO STARBASE : " : W1=B4 : X=B5 : GOTO 8120
8510 PRINT "MR. SPOCK REPORTS,  'SENSORS SHOW NO STARBASES IN THIS";
8520 PRINT " QUADRANT.'" : GOTO 1990
*/
	if (gameVars->starbaseQuadrant <= 0)
	{
		printf("MR. SPOCK REPORTS,  'SENSORS SHOW NO STARBASES IN THIS\n");
		printf(" QUADRANT.'\n\n");
		return;
	}
	else
	{
		printf("FROM ENTERPRISE TO STARBASE : \n");
		gameVars->warpFactor = gameVars->starbaseLocation[0];
		gameVars->navX  = gameVars->starbaseLocation[1];
		gameVars->course = gameVars->entSect[0];
		gameVars->deltaCourseWarpFactor  = gameVars->entSect[1];

		computeVector(gameVars); //GOTO 8120
	}

}

void dirdistCalc(GameVariables *gameVars)
{
/*
8150 PRINT "DIRECTION/DISTANCE CALCULATOR : "
8160 PRINT "YOU ARE AT QUADRANT ";Q1;",";Q2;" SECTOR ";S1;",";S2
8170 PRINT "PLEASE ENTER" : INPUT "  INITIAL COORDINATES (X,Y) ";C1,A
8200 INPUT "  FINAL COORDINATES (X,Y) ";W1,X
*/

	// This implementation was found online and seemed easier than parsing the comma.
	char temp[6];

	printf("DIRECTION/DISTANCE CALCULATOR : \n\n");
	printf("YOU ARE AT QUADRANT %d,%d SECTOR %d,%d\n\n", gameVars->entQuad[0], gameVars->entQuad[1],
	
	(int)gameVars->entSect[0], (int)gameVars->entSect[1]);

	printf("PLEASE ENTER INITIAL X COORDINATE: ");
	gets(temp);
	gameVars->course = atoi(temp);

	printf("PLEASE ENTER INITIAL Y COORDINATE: ");
	gets(temp);
	gameVars->deltaCourseWarpFactor = atoi(temp);

	printf("PLEASE ENTER FINAL X COORDINATE: ");
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
/*
7390 REM SETUP TO CHANGE CUM GAL RECORD TO GALAXY MAP
7400 H8=0 : G5=1 : PRINT "                        THE GALAXY" : GOTO 7550
7530 REM CUM GALACTIC RECORD
7540 REM INPUT "DO YOU WANT A HARDCOPY? IS THE TTY ON (Y/N) ";A$
7542 REM IF A$="Y" THEN POKE 1229,2 : POKE1237,3 : NULL1
7543 PRINT : PRINT "        ";
7544 PRINT "COMPUTER RECORD OF GALAXY FOR QUADRANT ";Q1;",";Q2
7546 PRINT
7550 PRINT "       1     2     3     4     5     6     7     8"
7560 O1$="     ----- ----- ----- ----- ----- ----- ----- -----"
7570 PRINT O1$ : FOR I=1 TO 8 : PRINT I;"  "; : IF H8=0 THEN 7740
7630 FOR J=1 TO 8 : PRINT "   "; : IF Z(I,J)=0 THEN PRINT "***"; : GOTO 7720
7700 PRINT RIGHT$(STR$(Z(I,J)+1000),3);
7720 NEXT J : GOTO 7850
7740 Z4=I : Z5=1 : GOSUB 9030 : J0=INT(15-.5*LEN(G2$)) : PRINT TAB(J0);G2$;
7800 Z5=5 : GOSUB 9030 : J0=INT(39-.5*LEN(G2$)) : PRINT TAB(J0);G2$;
7850 PRINT : PRINT O1$ : NEXT I : PRINT : GOTO 1990
*/
	int i, j, j0;

	gameVars->quadName = 1;

	printf("\n                   The Galaxy\n\n");
	printf("    1     2     3     4     5     6     7     8\n");
//7570 PRINT O1$ : FOR I=1 TO 8 : PRINT I;"  "; : IF H8=0 THEN 7740
	for (i = 0; i < 8; i++)
	{
		printf("  ----- ----- ----- ----- ----- ----- ----- -----\n");
		printf("%d ", i);
		//7740 Z4=I : Z5=1 : GOSUB 9030 : J0=INT(15-.5*LEN(G2$)) : PRINT TAB(J0);G2$;
		gameVars->tempQuadCoord[0] = i;
		gameVars->tempQuadCoord[1] = 1;
		quadrantName(gameVars);
		
		j0 = (int)(15 - (strlen(gameVars->strResults) / 2));
		
		//PRINT TAB(J0)
		for (j = 0; j < j0; j++)
		{
			printf(" ");
		}
		
		printf(gameVars->strResults);
		
		for (j = 0; j < j0; j++)
	  	{
			printf(" ");
	  	}
	  	// I saw this logic in other examples but it's not in the original
		//if (! (strlen(gameVars->strResults) % 2))
  		//{
	  	//	printf(" ");
  		//}
		
		//7800 Z5=5 : GOSUB 9030 : J0=INT(39-.5*LEN(G2$)) : PRINT TAB(J0);G2$;
		gameVars->tempQuadCoord[1] = 5;
		quadrantName(gameVars);
		j0 = (int)(39 - (strlen(gameVars->strResults) / 2));
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
//8220 X=X-A : A=C1-W1 : 
	gameVars->navX = gameVars->navX - gameVars->deltaCourseWarpFactor;
	gameVars->deltaCourseWarpFactor = gameVars->course - gameVars->warpFactor; // delta of course and warp factor
	//8220 ... IF X<0 THEN 8350
	if(gameVars->navX < 0.0)
	{	//IF A>0 THEN C1=3 : GOTO 8420
		if(gameVars->deltaCourseWarpFactor > 0.0)
		{    
		  gameVars->course = 3.0;
		  _direction_calc2(gameVars); //GOTO 8420
		  return;
		}
		if(gameVars->navX != 0)
		{
		  gameVars->course = 5.0;
		  _direction_calc1(gameVars); //GOTO 8290
		  return;
		}
	}
	//8250 IF A<0 THEN 8410
	else if(gameVars->deltaCourseWarpFactor < 0.0)
	{
		gameVars->course = 7.0;
		_direction_calc2(gameVars);
		return;
	}
	//8260 IF X>0 THEN 8280
	else if(gameVars->navX > 0.0)
	{
		gameVars->course = 1.0;
		_direction_calc1(gameVars);
		return;
	}
	else
	{ //this error state is unaccounted for in the original code
		printf("[ERROR] void computeVector(GameVariables *gameVars)\n");
	}
}

void _direction_calc1(GameVariables *gameVars)
{
/*
8290 IF ABS(A)<=ABS(X) THEN 8330
8310 PRINT "DIRECTION =";C1+(((ABS(A)-ABS(X))+ABS(A))/ABS(A)) : GOTO 8460
8330 PRINT "DIRECTION =";C1+(ABS(A)/ABS(X)) : GOTO 8460
...
8460 PRINT "DISTANCE =";SQR(X^2+A^2) : IF H8=1 THEN 1990
*/
	gameVars->navX = fabs(gameVars->navX);
	gameVars->deltaCourseWarpFactor = fabs(gameVars->deltaCourseWarpFactor);

	if (gameVars->deltaCourseWarpFactor <= gameVars->navX)
		{
		printf("  DIRECTION = %4.2f\n", gameVars->course + 
						(gameVars->deltaCourseWarpFactor / gameVars->navX));
		}
	else
		{
		printf("  DIRECTION = %4.2f\n", gameVars->course + 
						(((gameVars->deltaCourseWarpFactor * 2) - 
						gameVars->navX) / gameVars->deltaCourseWarpFactor));
		}
	printf("  DISTANCE = %4.2f\n\n", (gameVars->navX > gameVars->deltaCourseWarpFactor) ? gameVars->navX : gameVars->deltaCourseWarpFactor);
}

void _direction_calc2(GameVariables *gameVars)
{
/*
8420 IF ABS(A)>=ABS(X) THEN 8450
8430 PRINT "DIRECTION =";C1+(((ABS(X)-ABS(A))+ABS(X))/ABS(X)) : GOTO 8460
8450 PRINT "DIRECTION =";C1+(ABS(X)/ABS(A))
8460 PRINT "DISTANCE =";SQR(X^2+A^2) : IF H8=1 THEN 1990
*/
	gameVars->navX = fabs(gameVars->navX);
	gameVars->deltaCourseWarpFactor = fabs(gameVars->deltaCourseWarpFactor);

	if (gameVars->deltaCourseWarpFactor >= gameVars->navX)
		{
		printf("  DIRECTION = %4.2f\n", gameVars->course + (gameVars->navX / gameVars->deltaCourseWarpFactor));
		}
	else
		{
		printf("  DIRECTION = %4.2f\n", gameVars->course + (((gameVars->navX * 2) - gameVars->deltaCourseWarpFactor) / gameVars->navX));
		}
	printf("  DISTANCE = %4.2f\n\n", (gameVars->navX > gameVars->deltaCourseWarpFactor) ? gameVars->navX : gameVars->deltaCourseWarpFactor);
}


void shipDestroyed(GameVariables *gameVars)
{
/*
6240 PRINT : PRINT "THE ENTERPRISE HAS BEEN DESTROYED. THE FEDERATION ";
6250 PRINT "WILL BE CONQUERED" : GOTO  6220
*/
	printf("THE ENTERPRISE HAS BEEN DESTROYED. THE FEDERATION \n");
	printf("WILL BE CONQUERED\n\n");

	endOfTime(gameVars); //6220
}

void endOfTime(GameVariables *gameVars)
{
	/*6220 PRINT "IT IS STARDATE";T : GOTO  6270*/
	printf("IT IS STARDATE %d.\n\n", (int)gameVars->stardateCurr);

	endMission(gameVars); //6270
}

void endMission(GameVariables *gameVars)
{
/*
6270 PRINT "THERE WERE ";K9;" KLINGON BATTLE CRUISERS LEFT AT"
6280 PRINT "THE END OF YOUR MISSION."
6290 PRINT : PRINT : IF B9=0 THEN 6360 <-- So if you kill all the star bases you do not get to continue...

*/
	printf("THERE WERE %d KLINGON BATTLE CRUISERS LEFT AT\n", gameVars->klingLeft);
	printf("THE END OF YOUR MISSION.\n\n");

	endOfGame(gameVars);
}

void wonGame(GameVariables *gameVars)
{
	/*
6370 PRINT "CONGRATULATION, CAPTAIN!   THEN  LAST KLINGON BATTLE CRUISER"
6380 PRINT "MENACING THE FEDERATION HAS BEEN DESTROYED." : PRINT
6400 PRINT "YOUR EFFICIENCY RATING IS";1000*(K7/(T-T0))^2 : GOTO 6290
	*/
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
	/*
6290 PRINT : PRINT : IF B9=0 THEN 6360
6310 PRINT "THE FEDERATION IS IN NEED OF A NEW STARSHIP COMMANDER"
6320 PRINT "FOR A SIMILAR MISSION -- IF THERE IS A VOLUNTEER,"
6330 INPUT "LET HIM STEP FORWARD AND ENTER 'AYE' ";A$ : IF A$="AYE" THEN 10
6360 END <-- -_- ...this is why no one uses basic...
	*/
  	char temp[6];

  	if(gameVars->starbaseTotal > 0)
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
        	return;
      	}
      	else
      	{
      		printf("\nMAY THE FORCE BE WITH YOU FRODO!\n"); 
      		gameVars->running = false;
      		gameVars->currGame = false;
      		exit(EXIT_SUCCESS) // 6360 END
      	}
    }
    else if(gameVars->starbaseTotal <= 0)
    {
    	printf("You killed all the Starbases\n");
    	printf("which apparently means you must\n");
    	printf("be inconvenienced to play again :P\n");
    	printf("\nEND\n");

    }

}


void _klingonsMove(GameVariables *gameVars)
{

//Called in courseControl

/*
2580 REM KLINGONS MOVE/FIRE ON MOVING STARSHIP . . .
2590 FOR I=1 TO K3 : IF K(I,3)=0 THEN 2700
2610 A$="   " : Z1=K(I,1) : Z2=K(I,2) : GOSUB 8670 : GOSUB 8590
2660 K(I,1)=Z1 : K(I,2)=Z2 : A$="+K+" : GOSUB 8670
2700 NEXT I : GOSUB 6000 : D1=0 : D6=W1 : IF W1>=1 THEN D6=1
2770 FOR I=1 TO 8 : IF D(I)>=0 THEN 2880
2790 D(I)=D(I)+D6 : IF D(I)>-.1 AND D(I)<0 THEN D(I)=-.1 : GOTO 2880
2800 IF D(I)<0 THEN 2880
2810 IF D1<>1 THEN D1=1 : PRINT "DAMAGE CONTROL REPORT :   ";
2840 PRINT TAB(8); : R1=I : GOSUB 8790 : PRINTG2$;" REPAIR COMPLETED."
2880 NEXT I : IF RND(1)>.2 THEN 3070
2910 R1=FNR(1) : IF RND(1)>=.6 THEN 3000
2930 D(R1)=D(R1)-(RND(1)*5+1) : PRINT "DAMAGE CONTROL REPORT :   ";
2960 GOSUB 8790 : PRINTG2$;" DAMAGED" : PRINT : GOTO 3070
3000 D(R1)=D(R1)+RND(1)*3+1 : PRINT "DAMAGE CONTROL REPORT :   ";
3030 GOSUB 8790 : PRINTG2$;" STATE OF REPAIR IMPROVED" : PRINT
*/
  int i;

  for (i = 0; i < 3; i++)
    {
      if (gameVars->klingData[i][2] > 0)
        {
          strcpy(gameVars->objInSector, "   ");
          gameVars->tempSectCoord[0] = gameVars->klingData[i][0];
          gameVars->tempSectCoord[1] = gameVars->klingData[i][1];
          insertInQuadrant(gameVars); //8660 REM INSERT IN STRING ARRAY FOR QUADRANT

          findEmptyPlace(gameVars);

          gameVars->klingData[i][0] = gameVars->tempSectCoord[0];
          gameVars->klingData[i][1] = gameVars->tempSectCoord[1];
          strcpy(gameVars->objInSector, "+K+");
          insertInQuadrant(gameVars);
        }
    }

  klingonsShoot(gameVars);
}


void klingonsShoot(GameVariables *gameVars)
/*
5990 REM KLINGONS SHOOTING
6000 IF K3<=0 THEN RETURN
6010 IF D0<>0 THEN PRINT "STARBASE SHIELDS PROTECT THE ENTERPRISE" : RETURN
6040 FOR I=1 TO 3 : IF K(I,3)<=0 THEN 6200
6060 H=INT((K(I,3)/FND(1))*(2+RND(1))) : S=S-H : K(I,3)=K(I,3)/(3+RND(0))
6080 PRINT H;" UNIT HIT ON ENTERPRISE FROM SECTOR ";K(I,1);",";K(I,2)
6090 IF S<=0 THEN 6240
6100 PRINT "      <SHIELDS DOWN TO ";S;" UNITS>" : IF H<20 THEN 6200
6120 IF RND(1)>.6ORH/S<=.02 THEN 6200
6140 R1=FNR(1) : D(R1)=D(R1)-H/S-.5*RND(1) : GOSUB 8790
6170 PRINT "DAMAGE CONTROL REPORTS ";G2$;" DAMAGED BY THE HIT'"
6200 NEXT I : RETURN
*/
{
	int hit, i; //H

	if (gameVars->klingQuad <= 0)
		return;

	if (gameVars->dockFlag != 0)
	{
	  	printf("STARBASE SHIELDS PROTECT THE ENTERPRISE\n\n");
	  	return;
	}

	for (i = 0; i < 3; i++)
	{
		//IF K(I,3)<=0 THEN 6200... else...
	  	if (gameVars->klingData[i][2] > 0)
    	{
    		//6060 H=INT((K(I,3)/FND(1))*(2+RND(1))) : S=S-H : K(I,3)=K(I,3)/(3+RND(0))
	      	hit = (int)((gameVars->klingData[i][2] / findDistance(gameVars,i)) * (2 + RandomToOne()));
	      	gameVars->shields = gameVars->shields - hit;
	      	gameVars->klingData[i][2] = (int)(gameVars->klingData[i][2] / (3 + RandomToOne()));

	      	printf("%d UNIT HIT ON ENTERPRISE FROM SECTOR ", hit);
	      	printf("%d, %d\n", gameVars->klingData[i][1], gameVars->klingData[i][2]);

	          	if (gameVars->shields <= 0)
	            {
	              	printf("\n");
	              	shipDestroyed(gameVars); //6240
	            }

          printf("      <SHIELDS DOWN TO %d UNITS>\n\n", gameVars->shields);

	      	if(hit >= 20)
	        {	
	        	//IF RND(1)>.6ORH/S<=.02 THEN 6200... else...
	          	if(RandomToOne() <= 0.6 || (hit / gameVars->shields) > 0.2)
	            {
	              	gameVars->tempPos[0] = findRandom();
	        	  	gameVars->damage[gameVars->tempPos[0]] = gameVars->damage[gameVars->tempPos[0]] - (hit / gameVars->shields) - (0.5 * RandomToOne());

	              	getDeviceName(gameVars);

	              	printf("DAMAGE CONTROL REPORTS '%s' DAMAGED BY THE HIT\n\n", 
	              			gameVars->strResults);
	            }
	            else
	            {
	            	return;
	            }
	        }
   	 	}
   	 	else
   	 	{
   	 		return;
   	 	}
	}
} 

void _repairDamage(GameVariables *gameVars)
{

//Called in courseControl

/*
2700 NEXT I : GOSUB 6000 : D1=0 : D6=W1 : IF W1>=1 THEN D6=1
2770 FOR I=1 TO 8 : IF D(I)>=0 THEN 2880
2790 D(I)=D(I)+D6 : IF D(I)>-.1 AND D(I)<0 THEN D(I)=-.1 : GOTO 2880
2800 IF D(I)<0 THEN 2880
2810 IF D1<>1 THEN D1=1 : PRINT "DAMAGE CONTROL REPORT :   ";
2840 PRINT TAB(8); : R1=I : GOSUB 8790 : PRINTG2$;" REPAIR COMPLETED."
2880 NEXT I : IF RND(1)>.2 THEN 3070
2910 R1=FNR(1) : IF RND(1)>=.6 THEN 3000
2930 D(R1)=D(R1)-(RND(1)*5+1) : PRINT "DAMAGE CONTROL REPORT :   ";
2960 GOSUB 8790 : PRINTG2$;" DAMAGED" : PRINT : GOTO 3070
3000 D(R1)=D(R1)+RND(1)*3+1 : PRINT "DAMAGE CONTROL REPORT :   ";
3030 GOSUB 8790 : PRINTG2$;" STATE OF REPAIR IMPROVED" : PRINT
*/

	int i;
	double repairFactor; //d6 

	repairFactor = gameVars->warpFactor;
	//2700 ...IF W1>=1 THEN D6=1
	if(gameVars->warpFactor >= 1.0)
	{
		repairFactor = 1;
	}

	for(i = 0; i < 8; i++)
	{
		//2770...IF D(I)>=0 THEN 2880 <-- oh this code...
		//anyway this is logic for the else of the above statement.
	  	if(gameVars->damage[i] < 0.0)
    	{
	      	gameVars->damage[i] = gameVars->damage[i] + repairFactor;
	      	if(gameVars->damage[i] > -0.1 && gameVars->damage[i] < 0)
	        {
	        	gameVars->damage[i] = -0.1;
	        }
	        //2800 IF D(I)<0 THEN 2880
	      	else if(gameVars->damage[i] >= 0.0)
	        {
	        	if(gameVars->damageRepFlag != 1)
	     	   	{
	            	gameVars->damageRepFlag = 1;
	        	}
	          	printf("DAMAGE CONTROL REPORT :   \n");
	          	gameVars->tempPos[0] = i;
	          	getDeviceName(gameVars); //GOSUB 8790
	          	printf("    %s  REPAIR COMPLETED.\n\n", gameVars->strResults);
	        }
	    }
	}
	//2880 NEXT I : IF RND(1)>.2 THEN 3070
	if(RandomToOne() <= 0.2)
	{
	  	gameVars->tempPos[0] = findRandom();
  		//2910 R1=FNR(1) : IF RND(1)>=.6 THEN 3000
	  	if(RandomToOne() < .6)
	    {
	      	gameVars->damage[gameVars->tempPos[0]] = gameVars->damage[gameVars->tempPos[0]] - 
	      											(RandomToOne() * 5.0 + 1.0);
	      	printf("DAMAGE CONTROL REPORT :   \n");
	      	getDeviceName(gameVars); //8790
	      	printf("    %s  DAMAGED\n\n", gameVars->strResults);
	    }
	  	else
	    {
	      gameVars->damage[gameVars->tempPos[0]] = gameVars->damage[gameVars->tempPos[0]] + 
	      										   (RandomToOne() * 3.0 + 1.0);
	      printf("DAMAGE CONTROL REPORT :   \n");
	      getDeviceName(gameVars); //GOSUB 8790
	      printf("    %s STATE OF REPAIR IMPROVED\n\n", gameVars->strResults);
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
	// printf("[DEBUG] gameVars->objInSector: %s\n", gameVars->objInSector);
	int i, j = 0;
	//S8=INT(Z2-.5)*3+INT(Z1-.5)*24+1
	gameVars->quadIndex = (int)(gameVars->tempSectCoord[1] - 0.5) * 3 + 
		(int)(gameVars->tempSectCoord[0] - 0.5) * 24 + 1;
	if(strlen(gameVars->objInSector)!=3)  //IF  LEN(A$)<>3 THEN  PRINT "ERROR"
	{
		printf("ERROR\n");
		// printf("[DEBUG] Error in insertInQuadrant()\n");	
	}
	// printf("[DEBUG] gameVars->quadIndex: %d\n", gameVars->quadIndex);
	for(i = gameVars->quadIndex - 1; i <= gameVars->quadIndex + 1; i++)
	{
		if(j < 3 && i < 193)
		{
			gameVars->quadDisp[i] = gameVars->objInSector[j++]; // this line is causing a seqfault
		}
		else if(i >= 193)
		{
			// printf("[DEBUG] i(gameVars->quadIndex): %d\t",i);
			printf("I mean that's not good\n");
		}
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

	char *deviceName[] = {"Warp Engines","Short Range Sensors",
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
/*
8820 REM STRING COMPARISON IN QUADRANT ARRAY
8830 Z1=INT(Z1+.5) : Z2=INT(Z2+.5) : S8=(Z2-1)*3+(Z1-1)*24+1 : Z3=0
8890 IF MID$(Q$,S8,3)<>A$ THEN RETURN
8900 Z3=1 : RETURN
*/
	int i;
	char temp[4];
	gameVars->tempSectCoord[0] = (int)(gameVars->tempSectCoord[0] + 0.5);
	gameVars->tempSectCoord[1] = (int)(gameVars->tempSectCoord[1] + 0.5);

	gameVars->quadIndex = ((gameVars->tempSectCoord[1] - 1) * 3) +
						((gameVars->tempSectCoord[0] - 1) * 24) + 1;

	midStr(temp, gameVars->quadDisp, gameVars->quadIndex, 3);
	// MID()
	i = strncmp(temp, gameVars->objInSector, 3);
	// printf("[DEBUG] i: %d\n", i);
	//IF MID$(Q$,S8,3)<>A$ THEN RETURN
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
    char *quadName[] = {"ANTARES","RIGEL","PROCYON","VEGA",
    "CANOPUS","ALTAIR","SAGITTARIUS","POLLUX","SIRIUS","DENEB","CAPELLA",
    "BETELGEUSE","ALDEBARAN","REGULUS","ARCTURUS","SPICA"};

  	char *sectName[] = {" I"," II"," III"," IV"};

  	if (gameVars->tempQuadCoord[0] < 0 || 
  		gameVars->tempQuadCoord[0] > 7 || 
  		gameVars->tempQuadCoord[1] < 0 || 
  		gameVars->tempQuadCoord[1] > 7)
    {	
    	strcpy(gameVars->strResults, "Unknown");
    }
  	if (gameVars->tempQuadCoord[1] < 4)
    {
    	strcpy(gameVars->strResults, quadName[gameVars->tempQuadCoord[0]]);
    }
  	else
    {	
    	strcpy(gameVars->strResults, quadName[gameVars->tempQuadCoord[0]+8]);
    }
  	if (gameVars->quadName != 1)
    {
     	if (gameVars->tempQuadCoord[1] > 3)
      	{
	      	gameVars->tempQuadCoord[1] = gameVars->tempQuadCoord[1] - 3;
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
  	while (i < j && i <= (int)strlen(str2))
  	{
    	*str1++ = *(str2 + i++);
  	}

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

double RandomToOne(void)
{

  double d;

  d = rand() / (double) RAND_MAX;
  
  return d;
}



int findRandom(void)
{
	//475 DEF FNR(R)=INT(RND(R)*7.98+1.01)
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

// char* MID(char* str1; int pos, int length)
// {
// 	int i=0;
// 	char mid_str[length];
// 	// int length = strlen(str1);
// 	for(int i = pos; i <= pos + length; i++)
// 	{
// 		mid_str[i] = str1[pos];
// 		i++;
// 	}
// 	return mid_str;
// }