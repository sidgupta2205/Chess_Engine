#include "definations.h"

struct config {
	char mat[8][8];
	int val;
	char xkingB, ykingB, xkingW, ykingW;
	char castlingB, castlingW;	
};
 
struct Temple_return
{
	int val;
	config T;
};

static int PawnIsolated = -30;


static int PawnDouble = -30;


static int RookOpenFile = 70;


static int RookSemiOpenFile = 50;


static int QueenOpenFile = 50;


static int QueenSemiOpenFile = 30;


static int BishopPair = 50;
static int PawnTable[64] = {
	0	    ,  	0   	,   0   	,   0   	,   0   	,  	0	    ,	0	    ,	0	    ,
	50	    ,  	50	    ,   0	    ,   -10     ,   -10     ,  	0	    ,	50	    ,	50	    ,
	25	    ,  	0	    ,  	0	    ,  	25	    ,  	25	    ,  	0	    ,	0	    ,	25	    ,
	0	    ,  	0	    ,  	50	    ,  	90	    ,  	90	    ,  	50	    ,	0	    ,	0	    ,
	25	    ,  	25	    ,  	25	    ,  	50	    ,  	50	    ,  	25	    ,	25	    ,	25	    ,
	50      ,  	50	    ,  	50	    ,  	90	    ,  	90	    ,  	50	    ,	50	    ,	50	    ,
	90	    ,   90 	    ,  	90	    ,  	90	    ,  	90	    ,  	90	    ,	90	    ,	90	    ,
	0	    ,  	0	    ,  	0	    ,  	0	    ,  	0	    ,  	0	    ,	0	    ,	0
};

static int KnightTable[64] = {
	0   	,	-50	    ,	0	    ,	0	    ,	0	    ,	0	    ,	-50 	,	0   	,
	0   	,	0	    ,	0	    ,	25	    ,	25	    ,	0	    ,	0	    ,	0   	,
	0	    ,	0	    ,	50	    ,	50	    ,	50	    ,	50	    ,	0	    ,	0	    ,
	0	    ,	25	    ,	50	    ,	90	    ,	90	    ,	50	    ,	25	    ,	0   	,
	25	    ,	50	    ,	70	    ,	90	    ,	90	    ,	70	    ,	50	    ,	25	    ,
	25	    ,  	50	    ,	50	    ,	90	    ,	90	    ,	50	    ,	50	    ,	25	    ,
	0	    ,	0	    ,	25	    ,	50	    ,	50	    ,	25	    ,	0	    ,	0   	,
	0	    ,	0	    ,	0	    ,	0	    ,	0	    ,	0	    ,	0	    ,	0
};

static int BishopTable[64] = {
	0	    ,	0	    ,	-50	    ,	0	    ,	0	    ,	-50	    ,	0	    ,	0   	,
	0	    ,  	0	    ,	0	    ,	50	    ,	50	    ,	0	    ,	0	    ,	0	    ,
	0	    ,	0	    ,	50	    ,	70	    ,	70	    ,	50  	,	0	    ,	0	    ,
	0	    ,	50	    ,	70	    ,	90	    ,	90	    ,	70	    ,	50	    ,	0   	,
	0	    ,	50	    ,	70	    ,	90	    ,	90	    ,	70	    ,	50	    ,	0   	,
	0	    ,	0	    ,	50	    ,	70	    ,	70	    ,	50	    ,	0	    ,	0   	,
	0	    ,	0	    ,	0	    ,	50	    ,	50	    ,	0   	,	0	    ,	0   	,
	0	    ,	0   	,	0	    ,	0	    ,	0	    ,	0   	,	0	    ,	0
};

static int RookTable[64] = {
    0   	,	0	    ,	25  	,	50	    ,	50	    ,	25	    ,	0	    ,	0	    ,
	0	    ,	0	    ,	25	    ,	50	    ,	50	    ,	25	    ,	0	    ,	0   	,
	0	    ,	0	    ,	25	    ,	50	    ,	50	    ,	25	    ,	0	    ,	0	    ,
	0	    ,	0	    ,	25	    ,	50	    ,	50	    ,	25  	,	0	    ,	0   	,
	0	    ,	0	    ,	25	    ,	50	    ,	50	    ,	25	    ,	0	    ,	0	    ,
	0	    ,	0	    ,	25	    ,	50	    ,	50	    ,	25	    ,	0	    ,	0	    ,
	90	    ,	90	    ,	90	    ,	90	    ,	90	    ,	90	    ,	90	    ,	90	    ,
	0	    ,	0	    ,	25	    ,	50	    ,	50	    ,	25	    ,	0	    ,	0
};

static int KingMid[64] = {
	-500    ,	-50	    ,	0   	,	0   	,	0   	,	0   	,	-50	    ,	-500	,
	-50     ,	0	    ,	50 	    ,	50	    ,	50	    ,	50	    ,	0   	,	-50     ,
	0	    ,	50	    ,	90	    ,	90	    ,	90	    ,	90	    ,	50	    ,	0	    ,
	0	    ,	50	    ,	90	    ,	99	    ,	99	    ,	90	    ,	50	    ,	0	    ,
	0	    ,	50	    ,	90	    ,	99	    ,	99	    ,	90	    ,	50	    ,	0	    ,
	0	    ,	50	    ,	90	    ,	90	    ,	90	    ,	90	    ,	50	    ,	0	    ,
	-50     ,	0	    ,	50	    ,	50	    ,	50	    ,	50	    ,	0	    ,	-50	    ,
	-500 	,	-50	    ,	0	    ,	0	    ,	0	    ,	0	    ,	-50	    ,	-500
};

static int KingEnd[64] = {
	0	    ,	25	    ,	25	    ,	-50     ,	-50 	,	0	    ,	50	    ,	25	    ,
	-300	,	-300	,	-300	,	-300	,	-300	,	-300	,	-300	,	-300	,
	-500	,	-500	,	-500	,	-500	,	-500	,	-500	,	-500	,	-500	,
	-700	,	-700	,	-700	,	-700	,	-700	,	-700	,	-700	,	-700	,
	-700	,	-700	,	-700	,	-700	,	-700	,	-700	,	-700	,	-700	,
	-700	,	-700	,	-700	,	-700	,	-700	,	-700	,	-700	,	-700	,
	-700	,	-700	,	-700	,	-700	,	-700	,	-700	,	-700	,	-700	,
	-700	,	-700	,	-700	,	-700	,	-700	,	-700	,	-700	,	-700
};

static int dC[8][2] = { {-2,+1} , {-1,+2} , {+1,+2} , {+2,+1} , {+2,-1} , {+1,-2} , {-1,-2} , {-2,-1} };

static int D[8][2] = { {+1,0} , {+1,+1} , {0,+1} , {-1,+1} , {-1,0} , {-1,-1} , {0,-1} , {+1,-1} }; 


// Intialising Structures

static void init( struct config *conf )
{
   	int i, j;

    	for (i=0; i<8; i++)
		for (j=0; j<8; j++)
			conf->mat[i][j] = 0;	

	// conf->mat[0][0] =  'r'; conf->mat[0][1] =  'k'; conf->mat[0][2] = 'b'; conf->mat[0][3] =  'q';
	// conf->mat[0][4] =  'e'; conf->mat[0][5] =  'b'; conf->mat[0][6] = 'k'; conf->mat[0][7] =  'r';

	// for (j=0; j<8; j++) {
	// 	conf->mat[1][j] = 'p';
 	// 	conf->mat[6][j] = -'p'; 
	// 	conf->mat[7][j] = -conf->mat[0][j];
	// }

	conf->mat[0][5] =  'r';
	conf->mat[4][5] =  'r';
	conf->mat[2][5] =  'b';
	conf->mat[2][2] =  'e';
	conf->mat[2][3] =  'p';
	conf->mat[2][4] =  -'e';
	conf->mat[2][7] =  -'b';

	conf->xkingW = 2; conf->ykingW = 2;
	conf->xkingB = 2; conf->ykingB = 4;

	conf->castlingW = 'e';
	conf->castlingB = 'e';

	conf->val = 0;

} 


static void affich( struct config conf )
{
	int i, j, k;
	for (i=0;  i<8; i++)
		printf("\t  %c", i+'a');
   	printf("\n");

	for (i=0;  i<8; i++)
		printf("\t----- ");
   	printf("\n");

	for(i=8; i>0; i--)  {
		printf("    %d", i);
		for (j=0; j<8; j++)
			if ( conf.mat[i-1][j] < 0 ) {
				printf("\t %s-%c",KRED, -conf.mat[i-1][j]);
				printf("%s", KWHT);
			}
			else if ( conf.mat[i-1][j] > 0 ) {
				printf("\t%s +%c",KGRN,  conf.mat[i-1][j]);
				printf("%s", KWHT);
			}
				  else printf("\t  ");
		printf("\n");

		for (k=0;  k<8; k++)
			printf("\t----- ");
   		printf("\n");

	}
	printf("\n");

} 



static int comp (const void * elem1, const void * elem2) 
{
    struct config f = *((struct config *)elem1);
    struct config s = *((struct config *)elem2);
    if (f.val < s.val) return  1;
    if (f.val > s.val) return -1;
    return 0;
}


static void rand_init(struct config *conf) {
    int i, j;

    // Clear the board
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            conf->mat[i][j] = 0;
        }
    }

    // Set the pieces to the standard starting position
    conf->mat[0][0] = 'r';
    conf->mat[0][1] = 'k';
    conf->mat[0][2] = 'b';
    conf->mat[0][3] = 'q';
    conf->mat[0][4] = 'e';
    conf->mat[0][5] = 'b';
    conf->mat[0][6] = 'k';
    conf->mat[0][7] = 'r';
    conf->mat[1][0] = 'p';
    conf->mat[1][1] = 'p';
    conf->mat[1][2] = 'p';
    conf->mat[1][3] = 'p';
    conf->mat[1][4] = 'p';
    conf->mat[5][5] = 'p';
    conf->mat[1][6] = 'p';
    conf->mat[1][7] = 'p';
    conf->mat[7][0] = -'r';
    conf->mat[7][1] = -'k';
    conf->mat[7][2] = -'b';
    conf->mat[7][3] = -'e';
    conf->mat[7][4] = -'q';
    conf->mat[7][5] = -'b';
    conf->mat[7][6] = -'k';
    conf->mat[7][7] = -'r';
    conf->mat[6][0] = -'p';
    conf->mat[6][1] = -'p';
    conf->mat[6][2] = -'p';
    conf->mat[5][3] = -'p';
    conf->mat[6][4] = -'p';
    conf->mat[6][5] = -'p';
    conf->mat[6][6] = -'p';
    conf->mat[6][7] = -'p';

    // Set the kings to a random position
    srand(time(NULL));
    int xB = rand() % 8;
    int yB = rand() % 8;
    int xN = rand() % 8;
    int yN = rand() % 8;
    conf->mat[xB][yB] = 'k';
    conf->xkingW = xB;
    conf->ykingW = yB;
    conf->mat[xN][yN] = -'k';
    conf->xkingB = xN;
    conf->ykingB = yN;

    // Set the other variables
   conf->xkingW = 0; conf->ykingW = 4;
	conf->xkingB = 7; conf->ykingB = 4;

	conf->castlingW = 'e';
	conf->castlingB = 'e';

	conf->val = 0;
}