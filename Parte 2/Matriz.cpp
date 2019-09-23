#include <iostream>
#include "Matriz.h"

using namespace std;

Matriz::Matriz(){}

void Matriz::preenche(){

    for (int i = 0; i < 1000; i++ ){
        for (int j = 0; j < 1000; j++ ){
            this -> dados[i][j] = i;
        }
    }

}

void Matriz::exibe(){

    for (int i = 0; i < 1000; i++ ){
        for (int j = 0; j < 1000; j++ ){
            cout << dados[i][j] << "\t";
        }
        cout << endl;
    }

}



