// need minmax_ab func, alpha, beta, score, 

#define MPI_COMM_WORLD 0
#include "headers/compulsory_headers.h"
#include "headers/mpi.h"
#include "headers/definations.h"
#include "headers/generators.h"
#include "headers/wrapper.h"

void MPI_Bcast(params &p,int ld,int os,int val ) {
    int i, cout;
   long local_nb_node1 = 0, local_nb_sec1= 0, local_nb_sec2 = 0, local_nb_node2 = 0;
    #pragma omp parallel private(local_nb_node2, local_nb_sec2, local_nb_node1, local_nb_sec1)
    {
        #pragma omp for schedule(dynamic)
        for (i = 0; i < p.n; i++) {
            if (p.mode == MAX) {
                local_nb_sec1 = 0;
                local_nb_node1 = 0;
                cout = minmax_ab(p.T[i], MIN, p.depth - 1, p.alpha, p.beta, &local_nb_node1, &local_nb_sec1);
                #pragma omp critical
                {
                    if (cout > p.score) {
                        p.alpha = cout;
                        p.score = cout;
                        p.j = i;
                    }
                    p.nb_node1 += local_nb_node1;
                    p.nb_sec1 += local_nb_sec1;
                }
            } else {
                local_nb_sec2 = 0;
                local_nb_node2 = 0;
                cout = minmax_ab2(p.T[i], MAX, p.depth - 1, p.alpha, p.beta, &local_nb_node2, &local_nb_sec2);
                #pragma omp critical
                {
                    if (cout < p.score) {
                        p.beta = cout;
                        p.score = cout;
                        p.j = i;
                    }
                    p.nb_sec2 += local_nb_sec2;
                    p.nb_node2 += local_nb_node2;
                }
            }
        }
    }
}

// int main()
// {
//     return 0;
// }


