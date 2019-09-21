#include <iostream>
#include <math.h>
#include <time.h>
#include <stdlib.h>// necessário p/ as funções rand() e srand()
#include "Matriz.h"

using namespace std;

// ======== NAO OTIMIZADO   ========

void exibe (int matriz[4][4], int linhas, int colunas){
    for (int i = 0; i < linhas; i++ ){
        for (int j = 0; j < colunas; j++ ){
            cout << matriz[i][j] << "\t";
        }
        cout << endl;
    }
}

void calculaTempo(double tempoTotal[], int n){

    double soma = 0;
    for (int i = 0; i < n; i++){
        soma += tempoTotal[i];
        //cout << tempoTotal[i] << endl;
    }

    cout << "Tempo medio gasto: " << soma / n << "ms\n\n";
}

/********************************************/
/** As matrizes inicializam separadamente  **/
/** Inicializações desnecessárias          **/
/** laços for estão com posiçoes trocadas  **/
/** laços for inicializando da última pos  **/
/** Muitas operações trigonométricas       **/
/********************************************/

void teste1(int linhas, int colunas, long n){

    clock_t inicio, fim;
    double tempoTotal[n];


    int m1[linhas][colunas];
    int m2[linhas][colunas];

    for (int k = 0; k < n; k++){
        inicio = clock();

        //Inicialiando a matriz m1

        for (int j = colunas - 1; j >= 0; j--){         /*****************************************/
            for (int i = linhas - 1; i >= 0; i--) {     /** AFETANDO PRINCIPIO DA LOCALIDADE    **/
                m1[i][j] = i;                           /** com I e J iniciando nas ultimas     **/
            }                                           /** posicoes, sempre averá cache miss   **/
        }                                               /*****************************************/

        //Inicialiando a matriz m2

        for (int j = colunas - 1; j >= 0; j--){
            for (int i = linhas - 1; i >= 0; i--){
                m2[i][j] = i + j;
            }
        }


        //Soma das matrizes m1 + m2
        for (int j = colunas - 1; j >= 0; j--){
            for (int i = linhas - 1; i >= 0; i--){
                m1[i][j] += m2[i][j] * round(cos(i) + sin(j));
            }
        }

        fim = clock();

        tempoTotal[k] = 1000*(double)(fim-inicio)/(double)(CLOCKS_PER_SEC);
    }

    calculaTempo(tempoTotal, n);

}


/********************************************/
/** As matrizes inicializam separadamente  **/
/** Inicializações desnecessárias          **/
/** laços for inicializando da última pos  **/
/** Muitas operações trigonométricas       **/
/********************************************/
void teste2(int linhas, int colunas, long n){

    clock_t inicio, fim;
    double tempoTotal[n];


    int m1[linhas][colunas];
    int m2[linhas][colunas];

    for (int k = 0; k < n; k++){
        inicio = clock();

        //Inicialiando a matriz m1

        for (int i = linhas - 1; i >= 0; i--){
             for (int j = colunas - 1; j >= 0; j--){
                m1[i][j] = i;
            }
        }

        //Inicialiando a matriz m2

        for (int i = linhas - 1; i >= 0; i--){
             for (int j = colunas - 1; j >= 0; j--){
                m2[i][j] = i + j;
            }
        }


        //Soma das matrizes m1 + m2
        for (int i = linhas - 1; i >= 0; i--){
             for (int j = colunas - 1; j >= 0; j--){
                m1[i][j] += m2[i][j] * round(cos(i) + sin(j));
            }
        }

        fim = clock();

        tempoTotal[k] = 1000*(double)(fim-inicio)/(double)(CLOCKS_PER_SEC);
    }

    calculaTempo(tempoTotal, n);

}


/********************************************/
/** As matrizes inicializam separadamente  **/
/** Inicializações desnecessárias          **/
/** Muitas operações trigonométricas       **/
/********************************************/
void teste3(int linhas, int colunas, long n){

    clock_t inicio, fim;
    double tempoTotal[n];


    int m1[linhas][colunas];
    int m2[linhas][colunas];

    for (int k = 0; k < n; k++){
        inicio = clock();

        //Inicialiando a matriz m1

        for (int i = 0; i < linhas; i++){
             for (int j = 0; j < colunas; j++){
                m1[i][j] = i;
            }
        }

        //Inicialiando a matriz m2

        for (int i = 0; i < linhas; i++){
             for (int j = 0; j < colunas; j++){
                m2[i][j] = i + j;
            }
        }


        //Soma das matrizes m1 + m2
        for (int i = 0; i < linhas; i++){
             for (int j = 0; j < colunas; j++){
                m1[i][j] += m2[i][j] * round(cos(i) + sin(j));
            }
        }

        fim = clock();

        tempoTotal[k] = 1000*(double)(fim-inicio)/(double)(CLOCKS_PER_SEC);
    }

    calculaTempo(tempoTotal, n);

}

/********************************************/
/** Inicializações desnecessárias          **/
/** Muitas operações trigonométricas       **/
/********************************************/
void teste4(int linhas, int colunas, long n){

    clock_t inicio, fim;
    double tempoTotal[n];


    int m1[linhas][colunas];
    int m2[linhas][colunas];

    for (int k = 0; k < n; k++){
        inicio = clock();

        //Inicialiando a matriz m1

        for (int i = 0; i < linhas; i++){
             for (int j = 0; j < colunas; j++){
                m1[i][j] = i;
                m2[i][j] = i + j;
                m1[i][j] += m2[i][j] * round(cos(i) + sin(j));
            }
        }

        fim = clock();

        tempoTotal[k] = 1000 * (double)(fim-inicio) / (double)(CLOCKS_PER_SEC);
    }

    calculaTempo(tempoTotal, n);

}

/*********************************************/
/** Muitas operações trigonométricas        **/
/** Há operações trigonométricas e round()  **/
/** a cada iteração                         **/
/*********************************************/

void teste5(int linhas, int colunas, long n){

    clock_t inicio, fim;
    double tempoTotal[n];

    int m1[linhas][colunas];
    int m2[linhas][colunas];

    for (int k = 0; k < n; k++){
        inicio = clock();

        for (int i = 0; i < linhas; i++){
             for (int j = 0; j < colunas; j++){
                m2[i][j] = i + j;
                m1[i][j] = i + m2[i][j] * round(cos(i) + sin(j));
            }
        }

        fim = clock();
        tempoTotal[k] = 1000 * (double)(fim-inicio) / (double)(CLOCKS_PER_SEC);
    }

    calculaTempo(tempoTotal, n);

}


/*********************************************/
/** Foram criados vetores para armazenar    **/
/** senos e cossenos a serem utilizados     **/
/** a fim de reduzir o número de operações  **/
/** em cada iteração = acesso direto        **/
/*********************************************/

void teste6(int linhas, int colunas, long n){

    clock_t inicio, fim;
    double tempoTotal[n];

    int m1[linhas][colunas];
    int m2[linhas][colunas];

    short seno[n], coss[n];  //valores serão arredondados

    for (int k = 0; k < n; k++){
        seno[k] = round (sin(k));       /** Inserindo valores trigonométricos em um vetor   **/
        coss[k] = round (cos(k));       /** para evitar cálculos a cada iteração            **/
    }

    for (int k = 0; k < n; k++){

        inicio = clock();

        for (int i = 0; i < linhas; i++){
             for (int j = 0; j < colunas; j++){
                m2[i][j] = i + j;
                m1[i][j] = i + m2[i][j] * coss[i] + seno[j];
            }
        }

        fim = clock();

        tempoTotal[k] = 1000 * (double)(fim-inicio) / (double)(CLOCKS_PER_SEC);
    }

    calculaTempo(tempoTotal, n);

}

/*********************************************/
/** O custo das operações trigonométricas   **/
/** a cada iteração e estão agregadas ao    **/
/** custo da função round() e rand()        **/
/** (para números aleatórios)               **/
/*********************************************/

void teste7(int linhas, int colunas, long n){

    clock_t inicio, fim;
    double tempoTotal[n];

    int m1[linhas][colunas];
    int m2[linhas][colunas];

    srand(time(NULL));

    for (int k = 0; k < n; k++){

        inicio = clock();

        //Inicialiando a matriz m1

        for (int i = 0; i < linhas; i++){
             for (int j = 0; j < colunas; j++){
                m2[i][j] = i + j;
                m1[i][j] = i + m2[i][j] * round(cos( rand() % n) + sin( rand() % n));
            }
        }

        fim = clock();

        tempoTotal[k] = 1000 * (double)(fim-inicio) / (double)(CLOCKS_PER_SEC);
    }

    calculaTempo(tempoTotal, n);

}

/*********************************************/
/** As operações trigonométricas estão      **/
/** armazenadas em um vetor (seno e coss)   **/
/** e são As operações trigonométricas      **/
/** estão acessadas aleatoriamente          **/
/** através da função rand()                **/
/*********************************************/

void teste8(int linhas, int colunas, long n){

    clock_t inicio, fim;
    double tempoTotal[n];

    int m1[linhas][colunas];
    int m2[linhas][colunas];

    short seno[n], coss[n];  //valores serão arredondados

    srand(time(NULL));

    for (int k = 0; k < n; k++){
        seno[k] = round (sin(k));
        coss[k] = round (cos(k));
    }

    for (int k = 0; k < n; k++){

        inicio = clock();

        for (int i = 0; i < linhas; i++){
             for (int j = 0; j < colunas; j++){
                m2[i][j] = i + j;
                m1[i][j] = i + m2[i][j] * coss[ rand() % n] + seno[ rand() % n];
            }
        }

        fim = clock();

        tempoTotal[k] = 1000 * (double)(fim-inicio) / (double)(CLOCKS_PER_SEC);
    }

    calculaTempo(tempoTotal, n);

}

void clearCache(){

    unsigned long cls[6144];  //CACHE DE 6k

    for (long i = 0; i <  6144; i++){
        cls[i] = 0;
    }

}

int main()
{

    int n = 100;

    clearCache();
    cout << "teste1" << endl;
    teste1(150, 1500, n);

    clearCache();
    cout << "teste2" << endl;
    teste2(150, 1500, n);

    clearCache();
    cout << "teste3" << endl;
    teste3(150, 1500, n);

    clearCache();
    cout << "teste4" << endl;
    teste4(150, 1500, n);

    clearCache();
    cout << "teste5" << endl;
    teste5(150, 1500, n);

    clearCache();
    cout << "teste6" << endl;
    teste6(150, 1500, n);

    clearCache();
    cout << "teste7" << endl;
    teste7(150, 1500, n);

    clearCache();
    cout << "teste8" << endl;
    teste8(150, 1500, n);

    return 0;
}
