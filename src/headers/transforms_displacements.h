#include "beam_search_func.h"

static void transformPion( struct config conf, int a, int b, int x, int y, struct config T[], int *n )
{
	int signe = +1;
	if (conf.mat[a][b] < 0 ) signe = -1;
	copier(&conf, &T[*n]);
	T[*n].mat[a][b] = 0;
	T[*n].mat[x][y] = signe *'q';
	(*n)++;
	copier(&conf, &T[*n]);
	T[*n].mat[a][b] = 0;
	T[*n].mat[x][y] = signe *'k';
	(*n)++;
	copier(&conf, &T[*n]);
	T[*n].mat[a][b] = 0;
	T[*n].mat[x][y] = signe *'b';
	(*n)++;
	copier(&conf, &T[*n]);
	T[*n].mat[a][b] = 0;
	T[*n].mat[x][y] = signe *'r';
	(*n)++;

} 



static int threatened_square( int mode, int x, int y, struct config conf )
{
	int i, j, a, b, stop;

	
	for (i=0; i<8; i += 1) {
	   
	   a = x + D[i][0];
	   b = y + D[i][1];	  	 
	   if ( a >= 0 && a <= 7 && b >= 0 && b <= 7 ) 
		if ( conf.mat[a][b]*mode == 'e' ) return 1;
	} 

	
	for (i=0; i<8; i++)
	   if ( x+dC[i][0] <= 7 && x+dC[i][0] >= 0 && y+dC[i][1] <= 7 && y+dC[i][1] >= 0 )
		if ( conf.mat[ x+dC[i][0] ] [ y+dC[i][1] ] * mode == 'k' )  
		   return 1;

	
	if ( (x-mode) >= 0 && (x-mode) <= 7 && y > 0 && conf.mat[x-mode][y-1]*mode == 'p' )
	   return 1;
	if ( (x-mode) >= 0 && (x-mode) <= 7 && y < 7 && conf.mat[x-mode][y+1]*mode == 'p' )
	   return 1;

	
	for (i=0; i<8; i += 1) {
	   
	   stop = 0;
	   a = x + D[i][0];
	   b = y + D[i][1];	  	 
	   while ( !stop && a >= 0 && a <= 7 && b >= 0 && b <= 7 ) 
		if ( conf.mat[a][b] != 0 )  stop = 1;
		else {
		    a = a + D[i][0];
		    b = b + D[i][1];
		}
	   if ( stop )  {
		if ( conf.mat[a][b]*mode == 'b' && i % 2 != 0 ) return 1; 
		if ( conf.mat[a][b]*mode == 'r' && i % 2 == 0 ) return 1;
		if ( conf.mat[a][b]*mode == 'q' ) return 1;
	   }
	} 
	


	return 0;

} 



static void displacementsBl(struct config conf, int x, int y, struct config T[], int *n )
{
	int i, j, a, b, stop;

	switch(conf.mat[x][y]) {
	
	case -'p' : 
		
		if ( x > 0 && conf.mat[x-1][y] == 0 ) {				
			copier(&conf, &T[*n]);
			T[*n].mat[x][y] = 0;
			T[*n].mat[x-1][y] = -'p';
			(*n)++;
			if ( x == 1 ) transformPion( conf, x, y, x-1, y, T, n );
		}
		if ( x == 6 && conf.mat[5][y] == 0 && conf.mat[4][y] == 0) {	
			copier(&conf, &T[*n]);
			T[*n].mat[6][y] = 0;
			T[*n].mat[4][y] = -'p';
			(*n)++;
		}
		if ( x > 0 && y >0 && conf.mat[x-1][y-1] > 0 ) {		
			copier(&conf, &T[*n]);
			T[*n].mat[x][y] = 0;
			T[*n].mat[x-1][y-1] = -'p';
			
			if (T[*n].xkingW == x-1 && T[*n].ykingW == y-1) { 
				T[*n].xkingW = -1; T[*n].ykingW = -1; 
			}

			(*n)++;
			if ( x == 1 ) transformPion( conf, x, y, x-1, y-1, T, n ); 
		}
		if ( x > 0 && y < 7 && conf.mat[x-1][y+1] > 0 ) {		
			copier(&conf, &T[*n]);
			T[*n].mat[x][y] = 0;
			T[*n].mat[x-1][y+1] = -'p';
			
			if (T[*n].xkingW == x-1 && T[*n].ykingW == y+1) { 
				T[*n].xkingW = -1; T[*n].ykingW = -1; 
			}

			(*n)++;
			if ( x == 1 ) transformPion( conf, x, y, x-1, y+1, T, n );
		}
		break;

	
	case -'k' : 
		for (i=0; i<8; i++)
		   if ( x+dC[i][0] <= 7 && x+dC[i][0] >= 0 && y+dC[i][1] <= 7 && y+dC[i][1] >= 0 )
			if ( conf.mat[ x+dC[i][0] ] [ y+dC[i][1] ] >= 0 )  {
			   copier(&conf, &T[*n]);
			   T[*n].mat[x][y] = 0;
			   T[*n].mat[ x+dC[i][0] ][ y+dC[i][1] ] = -'k';
			   
			   if (T[*n].xkingW == x+dC[i][0] && T[*n].ykingW == y+dC[i][1]) { 
				T[*n].xkingW = -1; T[*n].ykingW = -1; 
			   }

			   (*n)++;
			}
		break;

	
	case -'b' : 
		for (i=1; i<8; i += 2) {
		   
		   stop = 0;
		   a = x + D[i][0];
		   b = y + D[i][1];	  	 
		   while ( !stop && a >= 0 && a <= 7 && b >= 0 && b <= 7 ) {
			if ( conf.mat[ a ] [ b ] < 0 )  stop = 1;
			else {
			   copier(&conf, &T[*n]);
			   T[*n].mat[x][y] = 0;
			   if ( T[*n].mat[a][b] > 0 ) stop = 1;
			   T[*n].mat[a][b] = -'b';
			   
			   if (T[*n].xkingW == a && T[*n].ykingW == b) { T[*n].xkingW = -1; T[*n].ykingW = -1; }

			   (*n)++;
		   	   a = a + D[i][0];
		   	   b = b + D[i][1];
			}
		   } 
		} 
		break;

	
	case -'r' : 
		for (i=0; i<8; i += 2) {
		   
		   stop = 0;
		   a = x + D[i][0];
		   b = y + D[i][1];	  	 
		   while ( !stop && a >= 0 && a <= 7 && b >= 0 && b <= 7 ) {
			if ( conf.mat[ a ] [ b ] < 0 )  stop = 1;
			else {
			   copier(&conf, &T[*n]);
			   T[*n].mat[x][y] = 0;
			   if ( T[*n].mat[a][b] > 0 ) stop = 1;
			   T[*n].mat[a][b] = -'r';
			   
			   if (T[*n].xkingW == a && T[*n].ykingW == b) { T[*n].xkingW = -1; T[*n].ykingW = -1; }

			   if ( conf.castlingB != 'e' && conf.castlingB != 'q' ) {
			      if ( x == 7 && y == 0 && conf.castlingB != 'p')
			   	T[*n].castlingB = 'g'; 
			      else if ( x == 7 && y == 0 )
			   	   T[*n].castlingB = 'q'; 
			      if ( x == 7 && y == 7 && conf.castlingB != 'g' )
			   	T[*n].castlingB = 'p'; 
			      else if ( x == 7 && y == 7 )
			   	   T[*n].castlingB = 'q'; 
			   }

			   (*n)++;
		   	   a = a + D[i][0];
		   	   b = b + D[i][1];
			}
		   } 
		} 
		break;

	
	case -'q' : 
		for (i=0; i<8; i += 1) {
		   
		   stop = 0;
		   a = x + D[i][0];
		   b = y + D[i][1];	  	 
		   while ( !stop && a >= 0 && a <= 7 && b >= 0 && b <= 7 ) {
			if ( conf.mat[ a ] [ b ] < 0 )  stop = 1;
			else {
			   copier(&conf, &T[*n]);
			   T[*n].mat[x][y] = 0;
			   if ( T[*n].mat[a][b] > 0 ) stop = 1;
			   T[*n].mat[a][b] = -'q';
			   
			   if (T[*n].xkingW == a && T[*n].ykingW == b) { T[*n].xkingW = -1; T[*n].ykingW = -1; }

			   (*n)++;
		   	   a = a + D[i][0];
		   	   b = b + D[i][1];
			}
		   } 
		} 
		break;

	
	case -'e' : 
		
		if ( conf.castlingB != 'q' && conf.castlingB != 'e' ) {
		   if ( conf.castlingB != 'g' && conf.mat[7][1] == 0 && conf.mat[7][2] == 0 && conf.mat[7][3] == 0 )
		      if ( !threatened_square( MAX, 7, 1, conf ) && !threatened_square( MAX, 7, 2, conf ) && \
			   !threatened_square( MAX, 7, 3, conf ) && !threatened_square( MAX, 7, 4, conf ) )  {
			
			copier(&conf, &T[*n]);
			T[*n].mat[7][4] = 0;
			T[*n].mat[7][0] = 0;
			T[*n].mat[7][2] = -'e'; T[*n].xkingB = 7; T[*n].ykingB = 2;
			T[*n].mat[7][3] = -'r';
			T[*n].castlingB = 'e'; 
			(*n)++;
		      }
		   if ( conf.castlingB != 'p' && conf.mat[7][5] == 0 && conf.mat[7][6] == 0 )
		      if ( !threatened_square( MAX, 7, 4, conf ) && !threatened_square( MAX, 7, 5, conf ) && \
			   !threatened_square( MAX, 7, 6, conf ) )  {
			
			copier(&conf, &T[*n]);
			T[*n].mat[7][4] = 0;
			T[*n].mat[7][7] = 0;
			T[*n].mat[7][6] = -'e'; T[*n].xkingB = 7; T[*n].ykingB = 6;
			T[*n].mat[7][5] = -'r';
			T[*n].castlingB = 'e'; 
			(*n)++;

		      }
		}
			
		
		for (i=0; i<8; i += 1) {
		   
		   a = x + D[i][0];
		   b = y + D[i][1];	  	 
		   if ( a >= 0 && a <= 7 && b >= 0 && b <= 7 ) 
			if ( conf.mat[a][b] >= 0 ) {
			   copier(&conf, &T[*n]);
			   T[*n].mat[x][y] = 0;
			   T[*n].mat[a][b] = -'e'; T[*n].xkingB = a; T[*n].ykingB = b;
			   
			   if (T[*n].xkingW == a && T[*n].ykingW == b) { T[*n].xkingW = -1; T[*n].ykingW = -1; }

			   T[*n].castlingB = 'q'; 
			   (*n)++;
			}
		} 
		break;

	}

} 



static void displacementsW(struct config conf, int x, int y, struct config T[], int *n )
{
	int i, j, a, b, stop;

	switch(conf.mat[x][y]) {
	
	case 'p' :  
		if ( x <7 && conf.mat[x+1][y] == 0 ) {				
			copier(&conf, &T[*n]);
			T[*n].mat[x][y] = 0;
			T[*n].mat[x+1][y] = 'p';
			(*n)++;
			if ( x == 6 ) transformPion( conf, x, y, x+1, y, T, n );
		}
		if ( x == 1 && conf.mat[2][y] == 0 && conf.mat[3][y] == 0) {	
			copier(&conf, &T[*n]);
			T[*n].mat[1][y] = 0;
			T[*n].mat[3][y] = 'p';
			(*n)++;
		}
		if ( x < 7 && y > 0 && conf.mat[x+1][y-1] < 0 ) {		
			copier(&conf, &T[*n]);
			T[*n].mat[x][y] = 0;
			T[*n].mat[x+1][y-1] = 'p';
			
			if (T[*n].xkingB == x+1 && T[*n].ykingB == y-1) { 
				T[*n].xkingB = -1; T[*n].ykingB = -1; 
			}

			(*n)++;
			if ( x == 6 ) transformPion( conf, x, y, x+1, y-1, T, n );
		}
		if ( x < 7 && y < 7 && conf.mat[x+1][y+1] < 0 ) {		
			copier(&conf, &T[*n]);
			T[*n].mat[x][y] = 0;
			T[*n].mat[x+1][y+1] = 'p';
			
			if (T[*n].xkingB == x+1 && T[*n].ykingB == y+1) { 
				T[*n].xkingB = -1; T[*n].ykingB = -1; 
			}

			(*n)++;
			if ( x == 6 ) transformPion( conf, x, y, x+1, y+1, T, n );
		}
		break;

	
	case 'k' : 
		for (i=0; i<8; i++)
		   if ( x+dC[i][0] <= 7 && x+dC[i][0] >= 0 && y+dC[i][1] <= 7 && y+dC[i][1] >= 0 )
			if ( conf.mat[ x+dC[i][0] ] [ y+dC[i][1] ] <= 0 )  {
			   copier(&conf, &T[*n]);
			   T[*n].mat[x][y] = 0;
			   T[*n].mat[ x+dC[i][0] ][ y+dC[i][1] ] = 'k';
			   
			   if (T[*n].xkingB == x+dC[i][0] && T[*n].ykingB == y+dC[i][1]) { 
				T[*n].xkingB = -1; T[*n].ykingB = -1; 
			   }

			   (*n)++;
			}
		break;

	
	case 'b' : 
		for (i=1; i<8; i += 2) {
		   
		   stop = 0;
		   a = x + D[i][0];
		   b = y + D[i][1];	  	 
		   while ( !stop && a >= 0 && a <= 7 && b >= 0 && b <= 7 ) {
			if ( conf.mat[ a ] [ b ] > 0 )  stop = 1;
			else {
			   copier(&conf, &T[*n]);
			   T[*n].mat[x][y] = 0;
			   if ( T[*n].mat[a][b] < 0 ) stop = 1;
			   T[*n].mat[a][b] = 'b';
			   
			   if (T[*n].xkingB == a && T[*n].ykingB == b) { T[*n].xkingB = -1; T[*n].ykingB = -1; }

			   (*n)++;
		   	   a = a + D[i][0];
		   	   b = b + D[i][1];
			}
		   } 
		} 
		break;

	
	case 'r' : 
		for (i=0; i<8; i += 2) {
		   
		   stop = 0;
		   a = x + D[i][0];
		   b = y + D[i][1];	  	 
		   while ( !stop && a >= 0 && a <= 7 && b >= 0 && b <= 7 ) {
			if ( conf.mat[ a ] [ b ] > 0 )  stop = 1;
			else {
			   copier(&conf, &T[*n]);
			   T[*n].mat[x][y] = 0;
			   if ( T[*n].mat[a][b] < 0 ) stop = 1;
			   T[*n].mat[a][b] = 'r';
			   
			   if (T[*n].xkingB == a && T[*n].ykingB == b) { T[*n].xkingB = -1; T[*n].ykingB = -1; }

			   if ( conf.castlingW != 'e' && conf.castlingW != 'q' ) {
			     if ( x == 0 && y == 0 && conf.castlingW != 'p')
			   	T[*n].castlingW = 'g'; 
			     else if ( x == 0 && y == 0 )
			   	   T[*n].castlingW = 'q'; 
			     if ( x == 0 && y == 7 && conf.castlingW != 'g' )
			   	T[*n].castlingW = 'p'; 
			     else if ( x == 0 && y == 7 )
			   	   T[*n].castlingW = 'q'; 
			   }

			   (*n)++;
		   	   a = a + D[i][0];
		   	   b = b + D[i][1];
			}
		   } 
		} 
		break;

	
	case 'q' : 
		for (i=0; i<8; i += 1) {
		   
		   stop = 0;
		   a = x + D[i][0];
		   b = y + D[i][1];	  	 
		   while ( !stop && a >= 0 && a <= 7 && b >= 0 && b <= 7 ) {
			if ( conf.mat[ a ] [ b ] > 0 )  stop = 1;
			else {
			   copier(&conf, &T[*n]);
			   T[*n].mat[x][y] = 0;
			   if ( T[*n].mat[a][b] < 0 ) stop = 1;
			   T[*n].mat[a][b] = 'q';
			   
			   if (T[*n].xkingB == a && T[*n].ykingB == b) { T[*n].xkingB = -1; T[*n].ykingB = -1; }

			   (*n)++;
		   	   a = a + D[i][0];
		   	   b = b + D[i][1];
			}
		   } 
		} 
		break;

	
	case 'e' : 
		
		if ( conf.castlingW != 'q' && conf.castlingW != 'e' ) {
		   if ( conf.castlingW != 'g' && conf.mat[0][1] == 0 && conf.mat[0][2] == 0 && conf.mat[0][3] == 0 )
		      if ( !threatened_square( MIN, 0, 1, conf ) && !threatened_square( MIN, 0, 2, conf ) && \
			   !threatened_square( MIN, 0, 3, conf ) && !threatened_square( MIN, 0, 4, conf ) )  {
			
			copier(&conf, &T[*n]);
			T[*n].mat[0][4] = 0;
			T[*n].mat[0][0] = 0;
			T[*n].mat[0][2] = 'e'; T[*n].xkingW = 0; T[*n].ykingW = 2;
			T[*n].mat[0][3] = 'r';
			T[*n].castlingW = 'e'; 
			(*n)++;
		      }
		   if ( conf.castlingW != 'p' && conf.mat[0][5] == 0 && conf.mat[0][6] == 0 )
		      if ( !threatened_square( MIN, 0, 4, conf ) && !threatened_square( MIN, 0, 5, conf ) && \
			   !threatened_square( MIN, 0, 6, conf ) )  {
			
			copier(&conf, &T[*n]);
			T[*n].mat[0][4] = 0;
			T[*n].mat[0][7] = 0;
			T[*n].mat[0][6] = 'e'; T[*n].xkingW = 0; T[*n].ykingW = 6;
			T[*n].mat[0][5] = 'r';
			T[*n].castlingW = 'e'; 
			(*n)++;

		      }
		}
			
		
		for (i=0; i<8; i += 1) {
		   
		   a = x + D[i][0];
		   b = y + D[i][1];	  	 
		   if ( a >= 0 && a <= 7 && b >= 0 && b <= 7 ) 
			if ( conf.mat[a][b] <= 0 ) {
			   copier(&conf, &T[*n]);
			   T[*n].mat[x][y] = 0;
			   T[*n].mat[a][b] = 'e'; T[*n].xkingW = a; T[*n].ykingW = b;
			   
			   if (T[*n].xkingB == a && T[*n].ykingB == b) { T[*n].xkingB = -1; T[*n].ykingB = -1; }

			   T[*n].castlingW = 'q'; 
			   (*n)++;
			}
		} 
		break;

	}

} 

static void trier_config_table(struct config T [], int n)
{
	int i;
	for (i = 0; i < n; i++)
		T[i].val = estim(T[i]);

	qsort(T, n, sizeof(T[0]), comp);
	return;
}
