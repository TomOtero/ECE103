
#ifndef	GAME_VARS
#define GAME_VARS
typedef struct
{

	//ints
	int dockFlag, damageRepFlag; 
	int currEnergy, startEnergy;
	int quadName;
	int klingData, klingStart;
	int klingQuad, klingLeft, klingPow;;
	int torpLeft, torpCap;
	int entQuad1, entQuad2;
	int tempPos1, tempPos2; 
	int shields, stars;
	int stardateStart, stardateDone, tempSectCoord1;
	int tempSectCoord2;
	int starbaseQuadrant;
	int starbaseTotal;
	int starbaseLocation[2];
	int galaxy[8][8];
	int galaxyRecord[8][8];
	int klingData[3][3];
	
	//doubles
	double repairTime;
	double entSect1, entSect2; 
	double stardateCurr;
	double warpFactor;
	double navx1, navy1, navx2, navy2;
	double damage[8];

	//strings
	char objInSector[4];
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
	double find_random(GameVariables *gameVars);


#endif


