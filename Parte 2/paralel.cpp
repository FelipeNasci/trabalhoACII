#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

#define NUM_THREADS 2

using namespace std;

void teste1(int linhas, int colunas)
{
    clock_t t1, t2;
    float tempo1, tempo2;

    int i, j, k;

    int lista[linhas][colunas];
    int soma[linhas][colunas];

    // int** lista = new int* [linhas];
    // for (i = 0; i < linhas; ++i) {
    //     lista[i] = new int[colunas];
    // }

    // int** soma = new int* [linhas];
    // for (i = 0; i < linhas; ++i) {
    //     soma[i] = new int[colunas];
    // }
    
    // Inicialização do Array
    for (i = 0; i < linhas; ++i) {
        for (j = 0; j < colunas; ++j) {
            lista[i][j] = 50;
            soma[i][j] = 50;  
        }
    }

    t1 = clock();
    // Somando os dois arrays de maneira sequencial
    for (k = 0; k < 100; ++k) {
        for (i = 0; i < linhas; ++i) {
            for (j = 0; j < colunas; ++j) {
                soma[i][j] += lista[i][j];
            }
        }
    }
    
    tempo1 = ((float)(clock() - t1)/CLOCKS_PER_SEC);
    cout << tempo1 << "s" << endl;


    t2 = clock();
    // Somando dois arrays usando paralelismo
    // #pragma omp parallel num_threads(NUM_THREADS)
    // {
    //     #pragma omp for private(i, j) collapse(2)
    // #pragma omp parallel for num_threads(4)
    // for (k = 0; k < 100; ++k){
    //     for (i = 0; i < linhas; ++i) {
    //         for (j = 0; j < colunas; ++j) {
    //             soma[i][j] += lista[i][j];
    //         }
    //     }
    // }
    // }

    #pragma omp parallel for num_threads(4)
        for(long k = 0; k < 10000; k++)
	    for(int i = 0; i < linhas; i++){
		for(int j = 0; j < colunas; j++){
		    soma[i][j] += lista[i][j];
		}
	    }
    tempo2 = ((float)(clock() - t2)/CLOCKS_PER_SEC);
    cout << tempo2 << "s" << endl;

    // delete(lista);
    // delete(soma);

    // cout << (tempo1 - tempo2) << endl;
    // cout << (tempo2 / tempo1) << endl;
}

int main()
{   
    teste1(150, 1500);
    teste1(250, 2500);
    teste1(300, 3000);

    return 0;
}