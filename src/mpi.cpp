// need minmax_ab func, alpha, beta, score, 

#define MPI_COMM_WORLD 0
#include "headers/compulsory_headers.h"
#include "headers/mpi.h"
#include "headers/definations.h"
#include "headers/generators.h"
#include "headers/utils.h"

void MPI_Bcast(params &p,int ld,int os,int val ) {

    if(os==1)
        return;

    if(p.id==1)
    {
        int i, cout;
        long local_num_node1 = 0, local_time_sec1= 0, local_time_sec2 = 0, local_num_node2 = 0;
        #pragma omp parallel private(local_num_node2, local_time_sec2, local_num_node1, local_time_sec1)
        {
            #pragma omp for schedule(dynamic)
            for (i = 0; i < p.n; i++) {
                if (p.mode == MAX) {
                    local_time_sec1 = 0;
                    local_num_node1 = 0;
                    cout = minmax_ab(p.T[i], MIN, p.depth - 1, p.alpha, p.beta, &local_num_node1, &local_time_sec1);
                    #pragma omp critical
                    {
                        if (cout > p.score) {
                            p.alpha = cout;
                            p.score = cout;
                            p.j = i;
                        }
                        p.num_node1 += local_num_node1;
                        p.time_sec1 += local_time_sec1;
                    }
                } else {
                    local_time_sec2 = 0;
                    local_num_node2 = 0;
                    cout = minmax_ab2(p.T[i], MAX, p.depth - 1, p.alpha, p.beta, &local_num_node2, &local_time_sec2);
                    #pragma omp critical
                    {
                        if (cout < p.score) {
                            p.beta = cout;
                            p.score = cout;
                            p.j = i;
                        }
                        p.time_sec2 += local_time_sec2;
                        p.num_node2 += local_num_node2;
                    }
                }
            }
        }
    }

    else if(p.id==2)
    {
        int i, cout;
        long local_num_node1 = 0, local_time_sec1= 0, local_time_sec2 = 0, local_num_node2 = 0;
        #pragma omp parallel private (local_num_node2, local_time_sec2, local_num_node1, local_time_sec1) if (p.mode == MIN)
		{
		
			#pragma omp for schedule(dynamic)
            for (i = 0; i < p.n; i++) {
                if (p.mode == MAX) {
                    local_time_sec1 = 0;
                    local_num_node1 = 0;
                    cout = minmax_ab(p.T[i], MIN, p.depth - 1, p.alpha, p.beta, &local_num_node1, &local_time_sec1);
                    #pragma omp critical
                    {
                        if (cout > p.score) {
                            p.alpha = cout;
                            p.score = cout;
                            p.j = i;
                        }
                        p.num_node1 += local_num_node1;
                        p.time_sec1 += local_time_sec1;
                    }
                } else {
                    local_time_sec2 = 0;
                    local_num_node2 = 0;
                    cout = minmax_ab2(p.T[i], MAX, p.depth - 1, p.alpha, p.beta, &local_num_node2, &local_time_sec2);
                    #pragma omp critical
                    {
                        if (cout < p.score) {
                            p.beta = cout;
                            p.score = cout;
                            p.j = i;
                        }
                        p.time_sec2 += local_time_sec2;
                        p.num_node2 += local_num_node2;
                    }
                }
            }
		}
    }

    else if(p.id==3)
    {
        int i, cout;
        long local_num_node1 = 0, local_time_sec1= 0, local_time_sec2 = 0, local_num_node2 = 0;
        #pragma omp parallel private (local_num_node2, local_time_sec2, local_num_node1, local_time_sec1)
		{
		
			#pragma omp for schedule(dynamic)
            for (i = 0; i < p.n; i++) {
                if (p.mode == MAX) {
                    local_time_sec1 = 0;
                    local_num_node1 = 0;
                    cout = minmax_ab(p.T[i], MIN, p.depth - 1, p.alpha, p.beta, &local_num_node1, &local_time_sec1);
                    #pragma omp critical
                    {
                        if (cout > p.score) {
                            p.alpha = cout;
                            p.score = cout;
                            p.j = i;
                        }
                        p.num_node1 += local_num_node1;
                        p.time_sec1 += local_time_sec1;
                    }
                } else {
                    local_time_sec2 = 0;
                    local_num_node2 = 0;
                    cout = minmax_ab2(p.T[i], MAX, p.depth - 1, p.alpha, p.beta, &local_num_node2, &local_time_sec2);
                    #pragma omp critical
                    {
                        if (cout < p.score) {
                            p.beta = cout;
                            p.score = cout;
                            p.j = i;
                        }
                        p.time_sec2 += local_time_sec2;
                        p.num_node2 += local_num_node2;
                    }
                }
            }
		}
    }
    else if(p.id==4)
    {
        int i, cout;
        long local_num_node1 = 0, local_time_sec1= 0, local_time_sec2 = 0, local_num_node2 = 0;
        #pragma omp parallel private (local_num_node2, local_time_sec2, local_num_node1, local_time_sec1) if (p.mode == MIN)
		{
		
			#pragma omp for schedule(dynamic)
            for (i = 0; i < p.n; i++) {
                if (p.mode == MAX) {
                    local_time_sec1 = 0;
                    local_num_node1 = 0;
                    cout = minmax_ab(p.T[i], MIN, p.depth - 1, p.alpha, p.beta, &local_num_node1, &local_time_sec1);
                    #pragma omp critical
                    {
                        if (cout > p.score) {
                            p.alpha = cout;
                            p.score = cout;
                            p.j = i;
                        }
                        p.num_node1 += local_num_node1;
                        p.time_sec1 += local_time_sec1;
                    }
                } else {
                    local_time_sec2 = 0;
                    local_num_node2 = 0;
                    cout = minmax_ab(p.T[i], MAX, p.depth - 1, p.alpha, p.beta, &local_num_node2, &local_time_sec2);
                    #pragma omp critical
                    {
                        if (cout < p.score) {
                            p.beta = cout;
                            p.score = cout;
                            p.j = i;
                        }
                        p.time_sec2 += local_time_sec2;
                        p.num_node2 += local_num_node2;
                    }
                }
            }
		}
    }

    else if(p.id==5)
    {
        int i, cout;
        long local_num_node1 = 0, local_time_sec1= 0, local_time_sec2 = 0, local_num_node2 = 0;
        #pragma omp parallel private (local_num_node2, local_time_sec2, local_num_node1, local_time_sec1)
		{
			#pragma omp for schedule(dynamic)
            for (i = 0; i < p.n; i++) {
                if (p.mode == MAX) {
                    local_time_sec1 = 0;
                    local_num_node1 = 0;
                    cout = minmax_ab(p.T[i], MIN, p.depth - 1, p.alpha, p.beta, &local_num_node1, &local_time_sec1);
                    #pragma omp critical
                    {
                        if (cout > p.score) {
                            p.alpha = cout;
                            p.score = cout;
                            p.j = i;
                        }
                        p.num_node1 += local_num_node1;
                        p.time_sec1 += local_time_sec1;
                    }
                } else {
                    local_time_sec2 = 0;
                    local_num_node2 = 0;
                    cout = iterative_deepening(p.T[i], MAX, p.depth - 1, p.alpha, p.beta, &local_num_node2, &local_time_sec2);
                    #pragma omp critical
                    {
                        if (cout < p.score) {
                            p.beta = cout;
                            p.score = cout;
                            p.j = i;
                        }
                        p.time_sec2 += local_time_sec2;
                        p.num_node2 += local_num_node2;
                    }
                }
            }
		}
    }
   
}

void MPI_Init(int *, char*** argv)
{
    printf("Intializing process MPI\n");
}
    // srand(time(NULL));
void MPI_Comm_size(int p, int *size)
{
    *size = 5;
    // printf("Intializing process 1\n");
    // printf("Intializing process 3\n");
    // printf("Intializing process 2\n");
    // printf("Intializing process 5\n");
}
void MPI_Comm_rank(int q, int* rank)
{
    *rank = 0;
    return ;
}

void MPI_Barrier(int p)
{
    return;
}

MPI_Datatype::MPI_Datatype() {
    return;
}

void MPI_Gather(void *, int, int,void* ,void*, int, int, int)
{
         return;   
}

void MPI_Finalize()
{
         return;   
}



// int main()
// {
//     return 0;
// }


