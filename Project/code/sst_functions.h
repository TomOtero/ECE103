
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
	int entQuad1, entQuad2;								// q1, q2
	int tempPos1, tempPos2; 							// r1, r2
	int shields, stars;									// s, s3
	int quadIndex;										// s8
	int stardateStart, stardateDone,					// t0, t9
	int tempSectCoord[2];								// z1, z2
	int compare;										// z3
	int tempQuadCoord[2];								// z4, z5 
	int starbaseQuadrant;								// b3
	int starbaseLocation[2];							// b4, b5
	int starbaseTotal;									// b9
	int galaxy[8][8];									// g[8][8]
	int galaxyRecord[8][8];								// z[8][8]
	int klingData[3][3];								// k[3][3]
	
	//doubles
	double repairTime;									// d4
	double entSect[2];		 							// s1, s2
	double stardateCurr;								// t
	double warpFactor;									// w1
	double navx, navy, navx2, navy2;					// x, y, x1, x2
	double damage[8];									// d[8]

	//strings
	char objInSector[4];								//
	char condition[7];
	char quadDisp[194];
	char tempStr[100];
	char command[6];

}GameVariables;
#endif

#ifndef SST_FUN
#define SST_FUN

	void intro(void);
	void clear(GameVariables *gameVars);
	void initialize(GameVariables *gameVars);
	void event_handler(GameVariables *gameVars);
	void command_help(void);

	double find_distance(GameVariables *gameVars);
	int find_random(GameVariables *gameVars);


#endif


