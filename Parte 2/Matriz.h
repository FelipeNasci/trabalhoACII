#ifndef MATRIZ_H
#define MATRIZ_H

#define LINHAS 100
#define COLUNAS 100

class Matriz{

public:

    //==========    CONSTRUTOR ==========
    Matriz();

    //==========    ATRIBUTOS ==========
    int dados[1000][1000];

    //==========    FUNCOES  ==========
    void preenche();

    void exibe();


};

#endif // MATRIZ_H
