/*#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

#define NUM_THREADS 2

using namespace std;

void clearCache()
{
    unsigned long cls[6144];  //CACHE DE 6k
    for (long i = 0; i <  6144; i++) {
        cls[i] = 0;
    }
}

void teste1(int tam)
{
    clock_t t1, t2;
    float tempo1, tempo2;

    int i, j;
    int** lista = new int* [tam];
    for (i = 0; i < tam; ++i) {
        lista[i] = new int[tam];
    }

    int** soma = new int* [tam];
    for (i = 0; i < tam; ++i) {
        soma[i] = new int[tam];
    }

    // Inicialização do Array
    for (i = 0; i < tam; ++i) {
        for (j = 0; j < tam; ++j) {
            lista[i][j] = j;
        }
    }

    t1 = clock();
    // Somando os dois arrays de maneira sequencial
    for (i = 0; i < tam; ++i) {
        for (j = 0; j < tam; ++j) {
            soma[i][j] += lista[i][j];
            // cout << soma[i][j] << endl;
        }
    }
    tempo1 = ((float)(clock() - t1)/CLOCKS_PER_SEC);
    cout << tempo1 << "s" << endl;

    // cout << (tempo1 - tempo2) << endl;
    // cout << (tempo2 / tempo1) << endl;

    delete(lista);
    delete(soma);
}

void teste2(int tam)
{
    clock_t t1, t2;
    float tempo1, tempo2;

    int i, j;
    int** lista = new int* [tam];
    for (i = 0; i < tam; ++i) {
        lista[i] = new int[tam];
    }

    int** soma = new int* [tam];
    for (i = 0; i < tam; ++i) {
        soma[i] = new int[tam];
    }

    // Inicialização do Array
    for (i = 0; i < tam; ++i) {
        for (j = 0; j < tam; ++j) {
            lista[i][j] = j;
        }
    }

    t2 = clock();
    // Somando dois arrays usando paralelismo
    #pragma omp parallel num_threads(NUM_THREADS)
    {
        #pragma omp for private(i, j) collapse(2)
        for (i = 0; i < tam; ++i) {
            for (j = 0; j < tam; ++j) {
                soma[i][j] += lista[i][j];// * round(cos(i) + sin(j));
            }
        }
    }
    tempo2 = ((float)(clock() - t2)/CLOCKS_PER_SEC);
    cout << tempo2 << "s" << endl;

    // cout << (tempo1 - tempo2) << endl;
    // cout << (tempo2 / tempo1) << endl;

    delete(lista);
    delete(soma);
}

int main()
{
    int tam;
    tam = 10000;

    // for (int i = 100; i < 1000; i += 100) {
        // tam = i;
        // clearCache();
        teste1(tam);

        // clearCache();
        teste2(tam);
    // }

    return 0;
}

*/
