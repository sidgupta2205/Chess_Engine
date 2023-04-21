
#include "headers/compulsory_headers.h"
#include "headers/generators.h"

int main( int argc, char *argv[] )
{
	char sy, dy, ch[10];
	int sx, dx, n, i, j, score, stop, cout, cout2, legal, depth, sauter;
	int cmin, cmax, mode, cpt;
   	double stats1[100];
	double stats2[100];
	long nb_node1=0;
	long nb_node2=0;
	long nb_sec1 = 0;
	long nb_sec2 = 0;


   struct config T[100], conf, conf1;

   if ( argc == 1 ) 
	depth = 5;  
   else
	depth = atoi( argv[1] ); 

   printf("\n\nProfondeur d'exploration = %d\n\n", depth);

   
   init( &conf );
  
   

   
   stop = 0;
   mode = MAX;
   
   struct timeval begin, end;
   int alpha, beta;
   double result;
   cpt = 0;
   nb_node1=0;
   nb_node2=0;
   long local_nb_node1 = 0, local_nb_sec1= 0, local_nb_sec2 = 0, local_nb_node2 = 0;

   while (!stop && (cpt < 50))
   {
	    alpha= -INFINI;
		beta= +INFINI;

		affich( conf );

		printf("%d\n", cpt);
		
		generer_succ(conf, mode, T, &n);
		
		score = -INFINI*mode;
		j = -1;
		
		gettimeofday(&begin, NULL);
		#pragma omp parallel private (local_nb_node2, local_nb_sec2, local_nb_node1, local_nb_sec1) 
		{
		
			#pragma omp for  schedule (dynamic) 
			for (i=0; i<n; i++) 
			{
				
				if (mode == MAX)
				{

					local_nb_sec1 = 0;
					local_nb_node1 = 0;
					
					cout = minmax_ab(T[i], MIN, depth-1, alpha, beta, &local_nb_node1, &local_nb_sec1);
					#pragma omp critical
					{
						if (cout > score) 
						{  		
							alpha =  cout;
							score = cout;
							j = i;
						}
						nb_node1 += local_nb_node1;
						nb_sec1 += local_nb_sec1;
						
					}
				

				}
				else
				{
					local_nb_sec2 = 0;
					local_nb_node2 = 0;
					cout = minmax_ab2(T[i], MAX, depth-1, alpha, beta, &local_nb_node2, &local_nb_sec2);
					
					#pragma omp critical
					{
						if ( cout < score ) 
						{  
							beta = cout;
							score = cout;
							j = i;
						}
						nb_sec2 += local_nb_sec2;
						nb_node2 += local_nb_node2;
					}
					
				}
				
			}
		}
		gettimeofday(&end, NULL);
		result = (double)(end.tv_usec - begin.tv_usec)/1000000 + end.tv_sec - begin.tv_sec;
		if (mode == MAX)
			stats1[cpt] = result;
		else
		{
			stats2[cpt] = result;
			cpt++;
		}
		


		if ( j != -1 ) 
		{ 
			copier( &T[j], &conf );
			conf.val = score;
			
		}
		else 
		{ 
			printf(" *** J'ai perdu ***\n");
			stop = 1;
		}
	   mode *= -1;
	  
   } 
   
	int iiii;
	char res[30];
	FILE * f = fopen("results.txt", "w");

	snprintf(res, 30, "%ld", nb_node1);
	fputs(res, f);
	fputs("\n", f);

	snprintf(res, 30, "%ld", nb_node2);
	fputs(res, f);
	fputs("\n", f);


	for (iiii = 0;iiii < cpt; iiii++)
	{
		snprintf(res, 30, "%f", stats1[iiii]);
		fputs(res, f);
		fputs(" ", f);
	}

	fputs("\n", f);
	for (iiii = 0;iiii < cpt; iiii++)
	{
		snprintf(res, 30, "%f", stats2[iiii]);
		fputs(res, f);
		fputs(" ", f);
	}

	fclose(f);

	return 0;
}


