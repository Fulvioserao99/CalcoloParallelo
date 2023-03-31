#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main(){

	srand(time(NULL));

	//omp_set_num_threads(8); -- eventualmente cambiare da qui il numero di threads impiegati a piacimento

	//i = indice ciclo for // N = dimensione problema // t = numero threads disponibili // nloc = numero locazioni per thread // r = resto // id = id del thread // step = quali thread fanno cosa // indice = indice array
	int i,N,t,nloc,r,id,step,indice;

	float *a,*b,*c; // i tre vettori

	printf("Inserire N\n");
	scanf("%d",&N);

	a=(float*)calloc(N,sizeof(float));
	b=(float*)calloc(N,sizeof(float));
	c=(float*)calloc(N,sizeof(float));

	puts("Riempio gli arrays\n");	
	for (int k=0; k<N; k++){
		a[k]=rand()%4+0.33f;
		b[k]=rand()%5+0.21f;
	}


	#pragma omp parallel private(nloc,i,indice,id,step) shared(a,b,c,r)
	{

		t=omp_get_num_threads(); //thread totali
		r=N%t; //resto tra dimensione problema e thread -- se > 0, qualche thread farà del lavoro aggiuntivo
		id=omp_get_thread_num(); //identificativo del thread
		nloc=N/t; //numero effettivo di locazioni per thread
		printf("sono %d, di %d: numeri %d resto%d\n", omp_get_thread_num(),t,nloc,r);

		if(id < r){        //se l'identificativo del thread è minore di N%t

			nloc++;        //il thread si prende un elemento in più
			step=0;

		}

		else
			step=r;



		for(i=0; i<nloc; i++){
			
			indice = i+nloc*id+step;
			c[indice]=a[indice]+b[indice];

		}


	}

	for(int i=0; i<N; i++)
		printf("Locazione %d: %f\n",i,c[i]);




}
