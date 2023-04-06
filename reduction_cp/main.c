#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main(){
    //direttiva opzionale per settare il numero di thread che dovranno operare // su linux si può ottenere lo stesso risultato modificando
    //la variabile d'ambiente OMP_NUM_THREADS --> export OMP_NUM_THREADS=n_threads
    //omp_set_num_threads(10);

    int i,N=1234567,t,nloc,id,step,indice,r;

    float *a,sum,sumtot=0;


    printf("Inserire N\n");
	scanf("%d",&N);

	a=(float*)calloc(N,sizeof(float));

    puts("Riempio l'array\n");

    for (int k=0; k<N; k++)
		a[k]=1;

    double t0,t1;
    t0=omp_get_wtime(); //prendo il tempo del sistema pre esecuzione della parte parallela
    #pragma omp parallel private(nloc,i,id,step) shared(r) reduction(+:sumtot) //la clausola reduction si occupa in autonomia di effettuare le somme parziali
    {
        t=omp_get_num_threads(); //thread totali
        r=N%t; //resto tra dimensione problema e thread -- se > 0, qualche thread farà del lavoro aggiuntivo
        id=omp_get_thread_num(); //identificativo del thread
        nloc=N/t; //numero effettivo di locazioni per thread
        sum=0;

        if(id < r){        //se l'identificativo del thread è minore di N%t

		nloc++;        //il thread si prende un elemento in più
		step=0;

	}

	else
		step=r;



        for(i=0; i<nloc; i++)
            sumtot+=a[i+nloc*id+step];


    }
    t1=omp_get_wtime(); //systime dopo la parte parallela - mi aiuta a determinare il tempo complessivo d'esecuzione

    printf("Somma totale: %f\nTempo:%f\n", sumtot,t1-t0);





}
