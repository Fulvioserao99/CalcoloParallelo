#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define N 10000001


int main(int argc, char **argv){


    omp_set_num_threads(10); //setto il numero di threads //OPZIONALE

    double sum=0; //il prodotto scalare
    double t0,t1; //i tempi

    float *a,*b; //gli arrays (o vettori)

    //alloco gli arrays
    a=(float*)calloc(N,sizeof(float));
	b=(float*)calloc(N,sizeof(float));



    //inizializzo gli arrays con valori predefiniti
    //N.B. Non è stata usata la rand per avere riscontro dell'accuratezza
    //dei risultati
    for (int k=0; k<N; k++){
        a[k]=2.3f;
        b[k]=2.4f;
	}


    t0=omp_get_wtime(); //presa dei tempi pre direttiva
    #pragma omp parallel for schedule(static) reduction(+:sum)//è stato scelto lo scheduling statico per avere la maggiore efficienza
        for (int i=0; i<N; ++i){
            sum+=a[i] * b[i];

        }
    t1=omp_get_wtime(); //presa dei tempi post direttiva
    printf("Tempo: %f, somma:%f\n",t1-t0,sum); //output con tempo di esecuzione e scalare

    free(a);
    free(b);


    return 0;
}
