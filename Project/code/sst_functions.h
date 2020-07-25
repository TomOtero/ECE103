/*
	ECE 103 Engineering Programming
	Team 9: Tom Otero, Ed Rees, Kevin Deleon
	Last update: 07/25/20

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
	
	//doubles
	double repairTime;									// d4
	double entSect[2];		 							// s1, s2
	double stardateCurr;								// t
	double warpFactor;									// w1
	double navx, navy, navx1, navx2;					// x, y, x1, x2
	double damage[8];									// d[8]

	//strings
	char objInSector[4];								//
	char condition[7];
	char quadDisp[194];
	char tempStr[2][10];
	char command[6];
	char commandList[9][6];								// A1$

}GameVariables;
#endif


#ifndef SST_FUN
#define SST_FUN

	void intro(void);
	void clear(GameVariables *gameVars);
	void initialize(GameVariables *gameVars);
	void event_handler(GameVariables *gameVars);
	void command_help(void);
	void galaxy_setup(GameVariables *gameVars);

	double find_distance(GameVariables *gameVars, int index);

	int find_random(void);


#endif


