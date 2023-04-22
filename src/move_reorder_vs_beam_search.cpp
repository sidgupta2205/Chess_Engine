#include "headers/compulsory_headers.h"
#include "headers/generators.h"
#include "headers/wrapper.h"



int main( int argc, char *argv[] )
{
	params p;
	char sy, dy, ch[10];
	int sx, dx, i, score, stop, cout, cout2, legal, sauter;
	int cmin, cmax, cpt;
   	double stats1[100];
	double stats2[100];
	p.nb_node1=0;
	p.nb_node2=0;
	p.nb_sec1 = 0;
	p.nb_sec2 = 0;
   struct config conf, conf1;
   
//    MPI_Init(&argc, &argv);
//     // srand(time(NULL));
//     MPI_Comm_size(MPI_COMM_WORLD, &size);
//     MPI_Comm_rank(MPI_COMM_WORLD, &rank);

   if ( argc == 1 ) 
	p.depth = 5;  
   else
	p.depth = atoi( argv[1] ); 
   
   printf("\n \nDepthOfExploration = %d\n\n", p.depth);
   
   init( &conf );
   stop = 0;
   p.mode = MAX;
   
   struct timeval begin, end;
   double result;
   cpt = 0;
   p.nb_node1=0;
   p.nb_node2=0;

   while (!stop && (cpt < 50))
   {
	    p.alpha= -INFINI;
		p.beta= +INFINI;

		affich( conf );

		printf("%d\n", cpt);
		
		generer_succ(conf, p.mode, p.T, &p.n);
		
		p.score = -INFINI*p.mode;
		p.j = -1;
		
		gettimeofday(&begin, NULL);

    	MPI_Bcast(p,1,0,MPI_COMM_WORLD);

		//dummy code

		
		gettimeofday(&end, NULL);
		result = (double)(end.tv_usec - begin.tv_usec)/1000000 + end.tv_sec - begin.tv_sec;
		if (p.mode == MAX)
			stats1[cpt] = result;
		else
		{
			stats2[cpt] = result;
			cpt++;
		}
		


		if ( p.j != -1 ) 
		{ 
			copier( &p.T[p.j], &conf );
			conf.val = p.score;
			
		}
		else 
		{ 
			printf(" *** J'ai perdu ***\n");
			stop = 1;
		}
	   p.mode *= -1;
	  
   } 
   
	int iiii;
	char res[30];
	FILE * f = fopen("results.txt", "w");

	snprintf(res, 30, "%ld", p.nb_node1);
	fputs(res, f);
	fputs("\n", f);

	snprintf(res, 30, "%ld", p.nb_node2);
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


