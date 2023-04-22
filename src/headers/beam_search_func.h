
#include "new_structures.h"
#include "definations.h"

static int minmax_ab( struct config conf, int mode, int niv, int min, int max, long * nb_noeuds, long * nb_coupes);


static int AucunCoupPossible( struct config conf )
{
      	
	return 0;

} 

static int feuille( struct config conf, int *cout )
{
	
	
	*cout = 0;

	
	if ( conf.xrB == -1 ) { 
	   *cout = -100;
	   return 1; 
	}

	
	if ( conf.xrN == -1 ) {
	   *cout = +100;
	   return 1;
	}

	
	if (  conf.xrB != -1 &&  conf.xrN != -1 && AucunCoupPossible( conf ) )
	   return 1;

	
	return 0;

}  

static void copier( struct config *c1, struct config *c2 ) 
{
	int i, j;

	for (i=0; i<8; i++)
		for (j=0; j<8; j++)
			c2->mat[i][j] = c1->mat[i][j];

	c2->val = c1->val;
	c2->xrB = c1->xrB;
	c2->yrB = c1->yrB;
	c2->xrN = c1->xrN;
	c2->yrN = c1->yrN;

	c2->roqueB = c1->roqueB;
	c2->roqueN = c1->roqueN;
} 


static int egal(char c1[8][8], char c2[8][8] )
{
	int i, j;

	for (i=0; i<8; i++)
		for (j=0; j<8; j++)
			if (c1[i][j] != c2[i][j]) return 0;
	return 1;
} 

static int nbrPieces(struct config board, bool type) 
{
    int i, j, nbr = 0;
    if(type)
    {
        for(i = 0 ; i <= 7 ; i++)
        {
            for(j = 0 ; j <= 7 ; j++)
            {
                if(board.mat[i][j] > 0)
                {
                    nbr ++;
                }
            }
        }
    }
    else
    {
        for(i = 0 ; i <= 7 ; i++)
        {
            for(j = 0 ; j <= 7 ; j++)
            {
                if(board.mat[i][j] < 0)
                {
                    nbr ++;
                }
            }
        }
    }
    return nbr;
}


static int estim(struct config board) 
{
    int i, j;
    int matrice = 0;
    int isole = 0, rowB, rowN, nbrPionB = 0, nbrPionN = 0, doubl = 0;
    bool pionPosB_1 = false, pionPosB_2 = false, pionPosB = false;
    bool pionPosN_1 = false, pionPosN_2 = false, pionPosN = false;
    int k, rockB_nbrOpen = 0, rockN_nbrOpen = 0, rockValue = 0;
    int queenN_nbrOpen = 0, queenB_nbrOpen = 0, queenValue = 0;
    int nbrBishopB = 0, nbrBishopN = 0, bishopValue = 0;
    int resultat, materiel=0;
    for(j = 0 ; j <= 7 ; j++)
    {
        for(i = 0 ; i <= 7 ; i++)
        {
            switch(board.mat[i][j])
            {
                case 'p':
                    materiel += 100;

                    matrice += PawnTable[j + i * 8];

                    nbrPionB ++;
                    pionPosB = true;
                    if(!pionPosB_1)
                    {
                        if(!pionPosB_2)
                        {
                            pionPosB_2 = true;
                            rowB = j;
                        }
                        else
                        {
                            if (rowB != j)
                            {
                                pionPosB_1 = true;
                            }
                        }
                    }
                break;
                case -'p':
                    materiel -= 100;

                    matrice -= PawnTable[j + (7 - i) * 8];

                    nbrPionN ++;
                    pionPosN = true;
                    if(!pionPosN_1)
                    {
                        if(!pionPosN_2)
                        {
                            pionPosN_2 = true;
                            rowN = j;
                        }
                        else
                        {
                            if (rowN != j)
                            {
                                pionPosN_1 = true;
                            }
                        }
                    }
                break;
                case 'C':
                    materiel += 300;

                    matrice += KnightTable[j + i * 8];
                break;
                case -'C':
                    materiel -= 300;

                    matrice -= KnightTable[j + (7 - i) * 8];
                break;
                case 'f':
                    materiel += 325;

                    matrice += BishopTable[j + i * 8];

                    nbrBishopB ++;
                break;
                case -'f':
                    materiel -= 325;

                    matrice -= BishopTable[j + (7 - i) * 8];

                    nbrBishopN ++;
                break;
                case 't':
                    materiel += 500;

                    matrice += RookTable[j + i * 8];

                    k = 0;
                    while((k <= 7) && (board.mat[k][j] != 'p'))
                    {
                        if(((board.mat[k][j] == 0) || (board.mat[k][j] == 't')) || (board.mat[k][j] < 0))
                        {
                            rockB_nbrOpen ++;
                        }
                        k++;
                    }
                break;
                case -'t':
                    materiel -= 500;

                    matrice -= RookTable[j + (7 - i) * 8];

                    k = 7;
                    while((k >= 0) && (board.mat[k][j] != -'p'))
                    {
                        if(((board.mat[k][j] == 0) || (board.mat[k][j] == -'t')) || (board.mat[k][j] < 0))
                        {
                            rockN_nbrOpen ++;
                        }
                        k --;
                    }
                break;
                case 'n':
                    materiel += 1000;
                    k = 0;
                    while((k <= 7) && (board.mat[k][j] != 'p'))
                    {
                        if(((board.mat[k][j] == 0) || (board.mat[k][j] == 'n')) || (board.mat[k][j] < 0))
                        {
                            queenB_nbrOpen ++;
                        }
                        k++;
                    }
                break;
                case -'n':
                    materiel -= 1000;
                    k = 7;
                    while((k >= 0) && (board.mat[k][j] != -'p'))
                    {
                        if(((board.mat[k][j] == 0) || (board.mat[k][j] == -'n')) || (board.mat[k][j] < 0))
                        {
                            queenN_nbrOpen ++;
                        }
                        k --;
                    }
                break;
                case 'r':
                    if(nbrPieces(board, true) > 8)
                    {
                        matrice += KingO[j + i * 8];
                    }
                    if(nbrPieces(board, true) < 7)
                    {
                        matrice += KingE[j + i * 8];
                    }
                break;
                case -'r':
                    if(nbrPieces(board, true) > 8)
                    {
                        matrice -= KingO[j + (7 - i) * 8];
                    }
                    if(nbrPieces(board, true) < 7)
                    {
                        matrice -= KingE[j + (7 - i) * 8];
                    }
                break;
            }
        }

        if(nbrPionB > 0)
        {
            doubl = doubl + nbrPionB - 1;
        }
        if(nbrPionN > 0)
        {
            doubl = doubl + nbrPionN - 1;
        }
        nbrPionB = 0;
        nbrPionN = 0;

        if(!pionPosB && !pionPosB_1 && pionPosB_2)
        {
            isole ++;
        }
        if(!pionPosB)
        {
            pionPosB_1 = false;
            pionPosB_2 = false;
        }
        pionPosB = false;

        nbrPionN = 0;
        if(!pionPosN && !pionPosN_1 && pionPosN_2)
        {
            isole --;
        }
        if(!pionPosN)
        {
            pionPosN_1 = false;
            pionPosN_2 = false;
        }
        pionPosN = false;

        if(rockB_nbrOpen == 8)
        {
            rockValue += RookOpenFile;
        }
        else
        {
            if(rockB_nbrOpen > 5)
            {
                rockValue += RookSemiOpenFile;
            }
        }
        if(rockN_nbrOpen == 8)
        {
            rockValue -= RookOpenFile;
        }
        else
        {
            if(rockN_nbrOpen > 5)
            {
                rockValue -= RookSemiOpenFile;
            }
        }
        rockB_nbrOpen = 0;
        rockN_nbrOpen = 0;

        if(queenB_nbrOpen == 8)
        {
            queenValue += QueenOpenFile;
        }
        else
        {
            if(queenB_nbrOpen > 5)
            {
                queenValue += QueenSemiOpenFile;
            }
        }
        if(queenN_nbrOpen == 8)
        {
            queenValue -= QueenOpenFile;
        }
        else
        {
            if(queenN_nbrOpen > 5)
            {
                queenValue -= QueenSemiOpenFile;
            }
        }
        queenB_nbrOpen = 0;
        queenN_nbrOpen = 0;

        if(nbrBishopB == 2)
        {
            bishopValue += BishopPair;
            nbrBishopB = 0;
        }
        if(nbrBishopN == 2)
        {
            bishopValue -= BishopPair;
            nbrBishopN = 0;
        }
    }
    resultat = materiel + doubl * PawnDouble + isole * PawnIsolated + rockValue + queenValue + bishopValue + matrice;

    return resultat;
}

