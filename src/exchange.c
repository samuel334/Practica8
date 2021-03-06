#include "nprmutation.h"
#include <stdlib.h>
#include <time.h>

/*funcion para barajear los elemntos de un array*/
void shuffle(int size, int array[size]){
	int i, j, temp;
	for(i = 0;i<(size - 1);i++){
		j = rand()%((size - 1) - i + 1) + i;
		temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}
}

/*generar poblacion inicial de manera aleatoria, la representacion del cromosoma es para permutaciones*/
void generatePopulation(int p_lgth, int c_lgth, int population[p_lgth][c_lgth]){
	int i, j, gen;
	for(i = 0;i<p_lgth;i++){
		for(j = 0;j<c_lgth;j++){
			population[i][j] = j + 1;	//fijar valor de gen de individuo i
		}
		shuffle(c_lgth, population[i]);
	}
}

/*mutar poblacion*/
void mutation(int p_lgth, int c_lgth, int individual[p_lgth][c_lgth]){
	int i, j, r, temp;	//variables auxiliares
	int index[c_lgth];	//arreglo con indices y tamaño igual al del cromosoma
	for(i = 0;i<c_lgth;i++) index[i] = i;	//rellenar arreglo de indices
	for(i = 0;i<p_lgth;i++){
		/*imprimier en pantalla el individuo a mutar*/
		printf("individuo: ");
		for(j = 0;j<c_lgth;j++) printf("%d ", individual[i][j]);
		printf("\t|\t");
		/*seleccionar aleatorimente indices de los genes a intercambiar 
		barajeando los dos primeros elementos del arreglo de indices*/
		for(j = 0;j<2;j++){
			r = rand()%((c_lgth - 1) - j + 1) + j;
			temp = index[j];
			index[j] = index[r];
			index[r] = temp;
		}
		/*imprimir el valor de los genes a intercambiar*/
		printf("valor1: %d, valor2: %d", individual[i][index[0]], individual[i][index[1]]);
		/*mutar individuo*/
		exchange(c_lgth, individual[i], index[0], index[1]);	//mutacion por intercambio reciproco
		/*imprimir individuo mutado*/
		printf("\t|\tmutacion: ");
		for(j = 0;j<c_lgth;j++) printf("%d ", individual[i][j]);
		printf("\n");
	}
}

int main(int argc, char *argv[]){
	if(argc!=3) exit(1);
	int p_lgth = atoi(argv[1]); //numero de individuos por generacion
	int c_lgth = atoi(argv[2]);	//tamaño del cromosoma
	if(p_lgth<0 || p_lgth%2 || c_lgth<3) exit(1);
	srand(time(NULL));
	int individual[p_lgth][c_lgth];	//poblacion
	/*generar poblacion inicial*/
	generatePopulation(p_lgth, c_lgth, individual);
	/*mutar poblacion*/
	mutation(p_lgth, c_lgth, individual);
	return 1;
}
