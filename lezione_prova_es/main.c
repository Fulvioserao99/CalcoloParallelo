#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define N 40000


int main(int argc, char **argv){

    //int mat[N][N];
    int *mat;
    mat=(int*)calloc(N*N,sizeof(int));
    //int vet[N];
    int *vet;
    vet=(int*)calloc(N,sizeof(int));
    double t0,t1;

    int max_val = 0;

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++)
            *(mat + i *N + j)=j;
    }

    omp_set_num_threads(8);


    t0=omp_get_wtime();
    #pragma omp parallel for schedule(static)
    for (int i=0; i<N; i++)
        *(vet+i) = *(mat + i*N + i);

    t1=omp_get_wtime();
    printf("Tempo: %f\n",t1-t0);



    omp_set_num_threads(2);

    t0=omp_get_wtime();
    #pragma omp parallel for reduction (max:max_val)
    for (int i=0; i<N; i++)
        if (*(vet+i)>max_val)
            max_val = *(vet+i);


    t1=omp_get_wtime();
    printf("Tempo max: %f, Max: %d\n",t1-t0, max_val);








    return 0;
}
