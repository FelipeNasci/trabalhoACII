#include <iostream>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "Matriz.h"
#include "envTest.h

/**********************************************/
/** As matrizes inicializam separadamente   **/
/** Inicializacoes desnecessarias           **/
/** lacos for estao com posicoes trocadas   **/
/** lacos for inicializando da ultima pos   **/
/** Muitas operacoes trigonometricas        **/
/*********************************************/

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
            }                                           /** posicoes, sempre avera cache miss   **/
        }                                               /*****************************************/

        //Inicialiando a matriz m2
        for (int j = colunas - 1; j >= 0; j--)
            for (int i = linhas - 1; i >= 0; i--)
                m2[i][j] = i + j;

        //Soma das matrizes m1 + m2
        for (int j = colunas - 1; j >= 0; j--)
            for (int i = linhas - 1; i >= 0; i--)
                m1[i][j] += m2[i][j] * round(cos(i) + sin(j));

        fim = clock();

        tempoTotal[k] = (double)(fim - inicio);
    }

    calculaTempo(tempoTotal, n);

}


void teste2(int linhas, int colunas, long n){

    clock_t inicio, fim;
    double tempoTotal[n];

    int m1[linhas][colunas];
    int m2[linhas][colunas];

    for (int k = 0; k < n; k++){
        inicio = clock();

        for (int i = linhas - 1; i >= 0; i--)
             for (int j = colunas - 1; j >= 0; j--)
                m1[i][j] = i;

        for (int i = linhas - 1; i >= 0; i--)
             for (int j = colunas - 1; j >= 0; j--)
                m2[i][j] = i + j;

        for (int i = linhas - 1; i >= 0; i--)
             for (int j = colunas - 1; j >= 0; j--)
                m1[i][j] += m2[i][j] * round(cos(i) + sin(j));

        fim = clock();

        tempoTotal[k] = (double)(fim - inicio);
    }

    calculaTempo(tempoTotal, n);
}

void teste3(int linhas, int colunas, long n){

    clock_t inicio, fim;
    double tempoTotal[n];

    int m1[linhas][colunas];
    int m2[linhas][colunas];

    for (int k = 0; k < n; k++){
        inicio = clock();

        for (int i = 0; i < linhas; i++)
             for (int j = 0; j < colunas; j++)
                m1[i][j] = i;

        for (int i = 0; i < linhas; i++)
             for (int j = 0; j < colunas; j++)
                m2[i][j] = i + j;

        for (int i = 0; i < linhas; i++)
             for (int j = 0; j < colunas; j++)
                m1[i][j] += m2[i][j] * round(cos(i) + sin(j));

        fim = clock();

        tempoTotal[k] = (double)(fim - inicio);

    }

    calculaTempo(tempoTotal, n);

}

void teste4(int linhas, int colunas, long n){

    clock_t inicio, fim;
    double tempoTotal[n];


    int m1[linhas][colunas];
    int m2[linhas][colunas];

    for (int k = 0; k < n; k++){
        inicio = clock();

        for (int i = 0; i < linhas; i++){
             for (int j = 0; j < colunas; j++){
                m1[i][j] = i;
                m2[i][j] = i + j;
                m1[i][j] += m2[i][j] * round(cos(i) + sin(j));
            }
        }

        fim = clock();

        tempoTotal[k] = (double)(fim - inicio);
    }

    calculaTempo(tempoTotal, n);

}

/*********************************************/
/** Muitas opera��es trigonom�tricas        **/
/** H� opera��es trigonom�tricas e round()  **/
/** a cada itera��o                         **/
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
        tempoTotal[k] = (double)(fim - inicio);
    }

    calculaTempo(tempoTotal, n);

}

void teste6(int linhas, int colunas, long n){

    clock_t inicio, fim;
    double tempoTotal[n];

    int m1[linhas][colunas];
    int m2[linhas][colunas];

    short seno[n], coss[n];  //valores serao arredondados

    for (int k = 0; k < n; k++){
        seno[k] = sin(k);       /** Inserindo valores trigonometricos em um vetor   **/
        coss[k] = cos(k);       /** para evitar calculos a cada iteracao            **/
    }

    for (int k = 0; k < n; k++){

        inicio = clock();

        for (int i = 0; i < linhas; i++){
             for (int j = 0; j < colunas; j++){
                m2[i][j] = i + j;
                m1[i][j] = i + m2[i][j] * round(coss[i] + seno[j]);
            }
        }

        fim = clock();

        tempoTotal[k] = (double)(fim - inicio);
    }

    calculaTempo(tempoTotal, n);

}

void teste7(int linhas, int colunas, long n){

    clock_t inicio, fim;
    double tempoTotal[n];

    int m1[linhas][colunas];
    int m2[linhas][colunas];

    srand(time(NULL));

    for (int k = 0; k < n; k++){

        inicio = clock();

        for (int i = 0; i < linhas; i++){
             for (int j = 0; j < colunas; j++){
                m2[i][j] = i + j;
                m1[i][j] = i + m2[i][j] * round( cos( rand() % n ) + sin( rand() % n ) );
            }
        }

        fim = clock();

        tempoTotal[k] = (double)(fim - inicio);
    }

    calculaTempo(tempoTotal, n);

}

void teste8(int linhas, int colunas, long n){

    clock_t inicio, fim;
    double tempoTotal[n];

    int m1[linhas][colunas];
    int m2[linhas][colunas];

    short seno[n], coss[n];

    srand(time(NULL));

    for (int k = 0; k < n; k++){
        seno[k] = sin(k);
        coss[k] = cos(k);
    }

    for (int k = 0; k < n; k++){

        inicio = clock();

        for (int i = 0; i < linhas; i++){
             for (int j = 0; j < colunas; j++){
                m2[i][j] = i + j;
                m1[i][j] = i + m2[i][j] * round(coss[ rand() % n] + seno[ rand() % n]);
            }
        }

        fim = clock();

        tempoTotal[k] = (double)(fim - inicio);
    }

    calculaTempo(tempoTotal, n);

}

void calculaTempo(double tempoTotal[], int n){

    double soma = 0;
    for (int i = 0; i < n; i++){
        soma += (tempoTotal[i] / ((double)(CLOCKS_PER_SEC) / 1000));
        cout << tempoTotal[i] << endl;
    }

    cout << "Tempo medio gasto: " << soma / n << "ms\n\n";
}

void exibe (int matriz[][4], int linhas, int colunas){

    for (int i = 0; i < linhas; i++ ){
        for (int j = 0; j < colunas; j++ ){
            cout << matriz[i][j] << "\t";
        }
        cout << endl;
    }
}
