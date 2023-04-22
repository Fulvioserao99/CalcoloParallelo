#include <stdio.h>
#include<omp.h>
#define N 100000000


int main(int argc, char **argv){


    long int i, n = N;
    double x, dx, f, sum, pi;


    printf("numero di intervalli: %ld\n", n);

    sum = 0.0;

    dx = 1.0 / (double) n;


    double t0,t1;
    t0=omp_get_wtime(); //prendo il tempo del sistema pre esecuzione della parte parallela
    #pragma omp parallel for private(x,f,i) shared(dx,n) reduction(+:sum)
    for (i = 1; i <= n; i++){

        x = dx * ((double) (i - 0.5));
        f = 4.0 / (1.0 + x*x);
        sum = sum + f;

    }
    t1=omp_get_wtime(); //systime dopo la parte parallela - mi aiuta a determinare il tempo complessivo d'esecuzione
    pi = dx*sum;
    printf("PI %.24f\nTempo:%f\n", pi,t1-t0);

    return 0;
}
