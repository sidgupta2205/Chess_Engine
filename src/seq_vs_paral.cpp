#include "headers/compulsory_headers.h"
#include "headers/generators.h"
#include "headers/utils.h"


int main( int argc, char *argv[] )
{
	params p;
	p.id = 4;
	char sy, dy, ch[10];
	int sx, dx, i, score, stop, cout, cout2, legal, skip;
	int cmin, cmax, cpt;
   	double stats1[100];
	double stats2[100];
	p.num_node1=0;
	p.num_node2=0;
	p.time_sec1 = 0;
	p.time_sec2 = 0;
	
   struct config conf, conf1;
   
   	int size, rank;
    int div;
    int mod;
   	
	MPI_Init(&argc, &argv);
    // srand(time(NULL));
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	printf("%d",rank);
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
   p.num_node1=0;
   p.num_node2=0;
	
	int remaining = 10%size;

   while (!stop && (cpt < 50))
   {

		if(rank==0)
		{
			p.alpha= -INFINI;
			p.beta= +INFINI;



			// printf("%d\n", cpt);
			
			generate_succ(conf, p.mode, p.T, &p.n);
			
			p.score = -INFINI*p.mode;
			p.j = -1;
			
			gettimeofday(&begin, NULL);
		}
	    

    	MPI_Bcast(p,1,0,MPI_COMM_WORLD);

		//dummy code

		long local_num_node1 = 0, local_time_sec1= 0, local_time_sec2 = 0, local_num_node2 = 0;

		struct Temple_return temp;
		struct Temple_return* tempResultroot  = new Temple_return[10];

		if(rank>0 and p.mode==MIN)
		{
			int s  = p.n%rank;
			int e = (p.n+1)%rank;
			if(rank==size-1)
				e = e+remaining;

			for (i=s; i<e; i++) 
			{
				
				if (p.mode == MAX)
				{

					local_time_sec1 = 0;
					local_num_node1 = 0;
					
					cout = minmax_ab(p.T[i], MIN, p.depth-1, p.alpha, p.beta, &local_num_node1, &local_time_sec1);

					// modify the shared variable
					if (cout > temp.val) 
						{  		
							p.alpha =  cout;
							p.score = cout;
							p.j = i;
							temp.val = cout;
							temp.T = p.T[i];
						}
						p.num_node1 += local_num_node1;
						p.time_sec1 += local_time_sec1;
					// exit the critical section

				}
				else
				{
					local_time_sec1 = 0;
					local_num_node1 = 0;
					
					cout = minmax_ab(p.T[i], MIN, p.depth-1, p.alpha, p.beta, &local_num_node1, &local_time_sec1);

					// modify the shared variable
					if (cout < score) 
						{  		
							p.alpha =  cout;
							p.score = cout;
							temp.val = cout;
							temp.T = p.T[i];
						}
						p.num_node1 += local_num_node1;
						p.time_sec1 += local_time_sec1;
					
				}
				
			}
		}

		else if(p.mode==MAX and rank>0)
		{
			int s  = p.n%rank;
			int e = (p.n+1)%rank;
			if(rank==size-1)
				e = e+remaining;

			for (i=s; i<e; i++) 
			{
				
				if (p.mode == MAX)
				{

					local_time_sec2 = 0;
					local_num_node2 = 0;
					
					cout = minmax_ab(p.T[i], MIN, p.depth-1, p.alpha, p.beta, &local_num_node2, &local_time_sec2);

					// modify the shared variable
					if (cout > temp.val) 
						{  		
							p.alpha =  cout;
							p.score = cout;
							p.j = i;
							temp.val = cout;
							temp.T = p.T[i];
						}
						p.num_node2 += local_num_node2;
						p.time_sec2 += local_time_sec2;
					// exit the critical section

				}
				else
				{
					local_time_sec2 = 0;
					local_num_node2 = 0;
					
					cout = minmax_ab(p.T[i], MIN, p.depth-1, p.alpha, p.beta, &local_num_node2, &local_time_sec2);

					// modify the shared variable
					if (cout < score) 
						{  		
							p.alpha =  cout;
							p.score = cout;
							temp.val = cout;
							temp.T = p.T[i];
						}
						p.num_node2 += local_num_node2;
						p.time_sec2 += local_time_sec2;
					
				}
				
			}
		}

		// send best configuration to root process
		MPI_Gather(&temp, sizeof(Temple_return), datatype, nullptr, tempResultroot, datatype, 0, MPI_COMM_WORLD);

		// MPI_Barrier(MPI_COMM_WORLD);

		if(rank==0){
			compute_best_score(tempResultroot,p.n,&p.j,rank);
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
				printf(" *** Stopping ***\n");
				stop = 1;
			}
		}

		MPI_Bcast(p,1,1,MPI_COMM_WORLD);
		p.mode *= -1;
		
   } 

   if(rank==0)
   {
		int iiii;
		char res[30];
		FILE * f = fopen("results.txt", "w");

		snprintf(res, 30, "%ld", p.num_node1);
		fputs(res, f);
		fputs("\n", f);

		snprintf(res, 30, "%ld", p.num_node2);
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

   }

   MPI_Finalize();
	return EXIT_SUCCESS;
   
}
