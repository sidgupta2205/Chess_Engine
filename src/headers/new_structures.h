#include "definations.h"

struct config {
	char mat[8][8];
	int val;
	char xrN, yrN, xrB, yrB;
	char roqueN, roqueB;	
};


int PawnIsolated = -30;


int PawnDouble = -30;


int RookOpenFile = 70;


int RookSemiOpenFile = 50;


int QueenOpenFile = 50;


int QueenSemiOpenFile = 30;


int BishopPair = 50;
int PawnTable[64] = {
	0	    ,  	0   	,   0   	,   0   	,   0   	,  	0	    ,	0	    ,	0	    ,
	50	    ,  	50	    ,   0	    ,   -10     ,   -10     ,  	0	    ,	50	    ,	50	    ,
	25	    ,  	0	    ,  	0	    ,  	25	    ,  	25	    ,  	0	    ,	0	    ,	25	    ,
	0	    ,  	0	    ,  	50	    ,  	90	    ,  	90	    ,  	50	    ,	0	    ,	0	    ,
	25	    ,  	25	    ,  	25	    ,  	50	    ,  	50	    ,  	25	    ,	25	    ,	25	    ,
	50      ,  	50	    ,  	50	    ,  	90	    ,  	90	    ,  	50	    ,	50	    ,	50	    ,
	90	    ,   90 	    ,  	90	    ,  	90	    ,  	90	    ,  	90	    ,	90	    ,	90	    ,
	0	    ,  	0	    ,  	0	    ,  	0	    ,  	0	    ,  	0	    ,	0	    ,	0
};

int KnightTable[64] = {
	0   	,	-50	    ,	0	    ,	0	    ,	0	    ,	0	    ,	-50 	,	0   	,
	0   	,	0	    ,	0	    ,	25	    ,	25	    ,	0	    ,	0	    ,	0   	,
	0	    ,	0	    ,	50	    ,	50	    ,	50	    ,	50	    ,	0	    ,	0	    ,
	0	    ,	25	    ,	50	    ,	90	    ,	90	    ,	50	    ,	25	    ,	0   	,
	25	    ,	50	    ,	70	    ,	90	    ,	90	    ,	70	    ,	50	    ,	25	    ,
	25	    ,  	50	    ,	50	    ,	90	    ,	90	    ,	50	    ,	50	    ,	25	    ,
	0	    ,	0	    ,	25	    ,	50	    ,	50	    ,	25	    ,	0	    ,	0   	,
	0	    ,	0	    ,	0	    ,	0	    ,	0	    ,	0	    ,	0	    ,	0
};

int BishopTable[64] = {
	0	    ,	0	    ,	-50	    ,	0	    ,	0	    ,	-50	    ,	0	    ,	0   	,
	0	    ,  	0	    ,	0	    ,	50	    ,	50	    ,	0	    ,	0	    ,	0	    ,
	0	    ,	0	    ,	50	    ,	70	    ,	70	    ,	50  	,	0	    ,	0	    ,
	0	    ,	50	    ,	70	    ,	90	    ,	90	    ,	70	    ,	50	    ,	0   	,
	0	    ,	50	    ,	70	    ,	90	    ,	90	    ,	70	    ,	50	    ,	0   	,
	0	    ,	0	    ,	50	    ,	70	    ,	70	    ,	50	    ,	0	    ,	0   	,
	0	    ,	0	    ,	0	    ,	50	    ,	50	    ,	0   	,	0	    ,	0   	,
	0	    ,	0   	,	0	    ,	0	    ,	0	    ,	0   	,	0	    ,	0
};

int RookTable[64] = {
    0   	,	0	    ,	25  	,	50	    ,	50	    ,	25	    ,	0	    ,	0	    ,
	0	    ,	0	    ,	25	    ,	50	    ,	50	    ,	25	    ,	0	    ,	0   	,
	0	    ,	0	    ,	25	    ,	50	    ,	50	    ,	25	    ,	0	    ,	0	    ,
	0	    ,	0	    ,	25	    ,	50	    ,	50	    ,	25  	,	0	    ,	0   	,
	0	    ,	0	    ,	25	    ,	50	    ,	50	    ,	25	    ,	0	    ,	0	    ,
	0	    ,	0	    ,	25	    ,	50	    ,	50	    ,	25	    ,	0	    ,	0	    ,
	90	    ,	90	    ,	90	    ,	90	    ,	90	    ,	90	    ,	90	    ,	90	    ,
	0	    ,	0	    ,	25	    ,	50	    ,	50	    ,	25	    ,	0	    ,	0
};

int KingE[64] = {
	-500    ,	-50	    ,	0   	,	0   	,	0   	,	0   	,	-50	    ,	-500	,
	-50     ,	0	    ,	50 	    ,	50	    ,	50	    ,	50	    ,	0   	,	-50     ,
	0	    ,	50	    ,	90	    ,	90	    ,	90	    ,	90	    ,	50	    ,	0	    ,
	0	    ,	50	    ,	90	    ,	99	    ,	99	    ,	90	    ,	50	    ,	0	    ,
	0	    ,	50	    ,	90	    ,	99	    ,	99	    ,	90	    ,	50	    ,	0	    ,
	0	    ,	50	    ,	90	    ,	90	    ,	90	    ,	90	    ,	50	    ,	0	    ,
	-50     ,	0	    ,	50	    ,	50	    ,	50	    ,	50	    ,	0	    ,	-50	    ,
	-500 	,	-50	    ,	0	    ,	0	    ,	0	    ,	0	    ,	-50	    ,	-500
};

int KingO[64] = {
	0	    ,	25	    ,	25	    ,	-50     ,	-50 	,	0	    ,	50	    ,	25	    ,
	-300	,	-300	,	-300	,	-300	,	-300	,	-300	,	-300	,	-300	,
	-500	,	-500	,	-500	,	-500	,	-500	,	-500	,	-500	,	-500	,
	-700	,	-700	,	-700	,	-700	,	-700	,	-700	,	-700	,	-700	,
	-700	,	-700	,	-700	,	-700	,	-700	,	-700	,	-700	,	-700	,
	-700	,	-700	,	-700	,	-700	,	-700	,	-700	,	-700	,	-700	,
	-700	,	-700	,	-700	,	-700	,	-700	,	-700	,	-700	,	-700	,
	-700	,	-700	,	-700	,	-700	,	-700	,	-700	,	-700	,	-700
};

int dC[8][2] = { {-2,+1} , {-1,+2} , {+1,+2} , {+2,+1} , {+2,-1} , {+1,-2} , {-1,-2} , {-2,-1} };

int D[8][2] = { {+1,0} , {+1,+1} , {0,+1} , {-1,+1} , {-1,0} , {-1,-1} , {0,-1} , {+1,-1} }; 


// Intialising Structures

void init( struct config *conf )
{
   	int i, j;

    	for (i=0; i<8; i++)
		for (j=0; j<8; j++)
			conf->mat[i][j] = 0;	

	conf->mat[0][0] =  't'; conf->mat[0][1] =  'c'; conf->mat[0][2] = 'f'; conf->mat[0][3] =  'n';
	conf->mat[0][4] =  'r'; conf->mat[0][5] =  'f'; conf->mat[0][6] = 'c'; conf->mat[0][7] =  't';

	for (j=0; j<8; j++) {
		conf->mat[1][j] = 'p';
 		conf->mat[6][j] = -'p'; 
		conf->mat[7][j] = -conf->mat[0][j];
	}

	conf->xrB = 0; conf->yrB = 4;
	conf->xrN = 7; conf->yrN = 4;

	conf->roqueB = 'r';
	conf->roqueN = 'r';

	conf->val = 0;

} 


void affich( struct config conf )
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



int comp (const void * elem1, const void * elem2) 
{
    struct config f = *((struct config *)elem1);
    struct config s = *((struct config *)elem2);
    if (f.val < s.val) return  1;
    if (f.val > s.val) return -1;
    return 0;
}