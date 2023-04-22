#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define N 1000000


int main(int argc, char **argv){


    int n_threads, id_thread,i;

    double sum=0,sumtot=0;
    double t0,t1;
    t0=omp_get_wtime();
    #pragma omp parallel private(i) num_threads(10)
    {
        #pragma omp for schedule(static) reduction(+:sum)
        for (i=1; i<=N; i++)
            sum+=i;

        //#pragma omp atomic
            //sumtot+=sum;
    }

    t1=omp_get_wtime();
    printf("Tempo: %f, somma:%f\n",t1-t0,sum);



    return 0;
}
