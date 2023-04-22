#include "transforms_displacements.h"
#include "definations.h"

static void generer_succ( struct config conf, int mode, struct config T[], int *n )
{
	int i, j, k, stop;

	*n = 0;

	if ( mode == MAX ) 
	{		
	   for (i=0; i<8; i++)
	      for (j=0; j<8; j++)
		 if ( conf.mat[i][j] > 0 )
		    deplacementsB(conf, i, j, T, n );

	   
	   for (k=0; k < *n; k++) {
	      	i = T[k].xrB; j = T[k].yrB;  
		
		if ( caseMenaceePar( MIN, i, j, T[k] ) ) {
		    T[k] = T[(*n)-1];	
		    (*n)--;
		    k--;
		}
	    } 
	}

	else 
	{ 				
	   for (i=0; i<8; i++)
	      for (j=0; j<8; j++)
		 if ( conf.mat[i][j] < 0 )
		    deplacementsN(conf, i, j, T, n );

	   
	   for (k=0; k < *n; k++) 
	   {
		i = T[k].xrN; j = T[k].yrN;
		
		if ( caseMenaceePar( MAX, i, j, T[k] ) ) {
		    T[k] = T[(*n)-1];	
		    (*n)--;
		    k--;
		}
	   } 
	} 

} 







static int minmax_ab2( struct config conf, int mode, int niv, int alpha, int beta, long * nb_noeuds, long * nb_coupes)
{
	
 	int n, i, score, score2;
 	struct config T[100];
	*nb_noeuds += 1;

   	if ( feuille(conf, &score) ) 
		return score;

   	if ( niv == 0 ) 
		return estim(conf);

   	if ( mode == MAX ) 
	{

	   generer_succ( conf, MAX, T, &n );
	   trier_config_table(T, n);
	  

	   score = alpha;
	   for ( i=0; i<n/2; i++ ) 
	   {
   	    	score2 = minmax_ab2( T[i], MIN, niv-1, score, beta, nb_noeuds, nb_coupes);
			if (score2 > score) score = score2;
			if (score > beta) 
			{
				
					*nb_coupes += 1;
					
					return beta;   
			}
	   } 
	}
	else  
	{ 

	   generer_succ( conf, MIN, T, &n );
	   trier_config_table(T, n);
	  
	   score = beta;
	   for ( i=n-1; i >=n/2; i--) 
	   {
   	    	score2 = minmax_ab2( T[i], MAX, niv-1, alpha, score, nb_noeuds, nb_coupes);
			if (score2 < score) score = score2;
			if (score < alpha) 
			{
				
					*nb_coupes += 1;
					
					return alpha;   
	    	}
	   }
	}


	return score;

} 


static int minmax_ab( struct config conf, int mode, int niv, int alpha, int beta, long * nb_noeuds, long * nb_coupes)
{
	
 	int n, i, score, score2;
 	struct config T[100];
	*nb_noeuds += 1;

   	if ( feuille(conf, &score) ) 
		return score;

   	if ( niv == 0 ) 
		return estim(conf);

   	if ( mode == MAX ) 
	{

	   generer_succ( conf, MAX, T, &n );

	   score = alpha;
	   for ( i=0; i<n; i++ ) 
	   {
   	    	score2 = minmax_ab( T[i], MIN, niv-1, score, beta, nb_noeuds, nb_coupes);
			if (score2 > score) score = score2;
			if (score > beta) 
			{
				
					*nb_coupes += 1;
					
					return beta;   
			}
	   } 
	}
	else  
	{ 

	   generer_succ( conf, MIN, T, &n );

	   score = beta;
	   for ( i=0; i<n; i++ ) 
	   {
   	    	score2 = minmax_ab( T[i], MAX, niv-1, alpha, score, nb_noeuds, nb_coupes);
			if (score2 < score) score = score2;
			if (score < alpha) 
			{
				
					*nb_coupes += 1;
					
					return alpha;   
	    	}
	   }
	}

	if ( score == +INFINI ) score = +100;
    if ( score == -INFINI ) score = -100;
	return score;

} 

static int minmax( struct config conf, int mode, int niv)
{
 	int n, i, score, score2;
 	struct config T[100];

   	if ( feuille(conf, &score) ) 
		return score;

   	if ( niv == 0 ) 
		return estim( conf );

   	if ( mode == MAX ) {

	   generer_succ( conf, MAX, T, &n );

	   score = -INFINI;
	   for ( i=0; i<n; i++ ) 
	   {
   	    	score2 = minmax( T[i], MIN, niv-1);
			if (score2 > score) score = score2;
		
	   } 
	}
	else  { 

	   generer_succ( conf, MIN, T, &n );

	   score = +INFINI;
	   for ( i=0; i<n; i++ ) {
   	    	score2 = minmax( T[i], MAX, niv-1);
		if (score2 < score) score = score2;
	
	   }
	}

        if ( score == +INFINI ) score = +100;
        if ( score == -INFINI ) score = -100;

	return score;

}

static int iterative_deepening(struct config conf, int mode, int niv, int alpha, int beta, long * nb_noeuds, long * nb_coupes)
{
	int n,j, i, score, score2;
 	struct config T[100];

	if ( feuille(conf, &score) ) 
		return score;

   	if ( niv == 0 ) 
		return estim(conf);
	
	if (mode == MAX)
	{

		generer_succ(conf, MAX, T, &n);

		for (i = 0; i < niv; i++)
		{
			for (j = 0; j < n; j++)
			{
				T[j].val =  minmax_ab(T[j], MIN, i, alpha, beta, nb_noeuds, nb_coupes);
			}

			trier_config_table(T, n);
			
		}

		score = T[0].val;
	}
	else 
	{
		generer_succ(conf, MIN, T, &n);

		for (i = 0; i < niv; i++)
		{
			for (j = n-1; j >= 0; j--)
			{
				T[j].val =  minmax_ab(T[j], MAX, i, alpha, beta, nb_noeuds, nb_coupes);
			}

			trier_config_table(T, n);
		}

		score = T[n-1].val;
	}
	return score;
}