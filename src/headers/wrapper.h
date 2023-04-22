// need minmax_ab func, alpha, beta, score, 

#define MPI_COMM_WORLD 0

struct params
{
    int n;
    int depth;
    int mode;
    int alpha;
    int beta;
    int score;
    int j;
    long nb_node1;
    long nb_sec1;
    long nb_node2;
    long nb_sec2;
    struct config T[100];
};

void MPI_Bcast(params &p,int ld,int os,int val );
 


