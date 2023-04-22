// need minmax_ab func, alpha, beta, score, 
#include "definations.h"
struct params
{
    int id;
    int n;
    int depth;
    int mode;
    int alpha;
    int beta;
    int score;
    int j;
    long num_node1;
    long time_sec1;
    long num_node2;
    long time_sec2;
    struct config T[100];
};

class MPI_Datatype
{
    public:
        MPI_Datatype();
};


void MPI_Bcast(params &p,int ld,int os,int val );

void MPI_Init(int *, char*** argv);
    // srand(time(NULL));
void MPI_Comm_size(int , int *);
void MPI_Comm_rank(int, int*);
void MPI_Barrier(int);
void MPI_Gather(void *, int, int,void* ,void*, int, int, int);
void MPI_Finalize();


