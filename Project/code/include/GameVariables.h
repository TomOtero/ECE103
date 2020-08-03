/*
	ECE 103 Engineering Programming
	Team 9: Tom Otero, Ed Rees, Kevin Deleon
	Last update: 07/25/20

	This file contains the Struct of game variables for the 
	super_star_trek.c and function files.

*/

#ifndef	GAME_VARS
#define GAME_VARS
typedef struct
{

	//ints
	int dockFlag, damageRepFlag; 						// d0, d1
	int currEnergy, startEnergy;						// e, e0	
	int quadName;										// g5
	int klingStart, klingQuad;							// k7, k3
	int klingLeft, klingPow;							// k9, s9
	int torpLeft, torpCap;								// p, p0
	int entQuad[2];										// q1, q2
	int tempPos[2];			 							// r1, r2
	int shields, stars;									// s, s3
	int quadIndex;										// s8
	int stardateStart, stardateEnd;						// t0, t9
	int tempSectCoord[2];								// z1, z2
	int compare;										// z3
	int tempQuadCoord[2];								// z4, z5 
	int starbaseQuadrant;								// b3
	int starbaseLocation[2];							// b4, b5
	int starbaseTotal;									// b9
	int galaxy[8][8];									// g[8][8]
	int galaxyRecord[8][8];								// z[8][8]
	int klingData[3][3];								// k[3][3]
	int locationMove[9][2];								// c[9][2]
	int outOfBoundsFlag;
	int n;												// Number of sectors to travel //2490
	
	//doubles
	double repairTime;									// d4
	double entSect[2];		 							// s1, s2
	double stardateCurr;								// t
	double warpFactor;									// w1
	double navX, navY, navX1, navX2;					// x, y, x1, x2
	double damage[8];									// d[8]
	double course;										// c1
	double deltaCourseWarpFactor;						// a

	//strings
	char objInSector[4];								// A$
	char condition[7];									// C$
	char quadDisp[194];									// $Q
	char tempStr[2][10];								// X$ X0$
	char command[6];
	char commandList[9][6];								// A1$
	char strResults[255];								// sG2

}GameVariables;
#endif




