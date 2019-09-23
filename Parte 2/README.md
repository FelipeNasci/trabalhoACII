# Parte 2 - Programação Paralela

## Introdução

Chamamos de Computação Paralela o ramo da computação que se preocupa em quebrar as instruções de um determinado programa em partes idependentes e executá-las ao mesmo tempo, de maneira concorrente.

O Paralelismo, em computação, ganhou espaço quando engenheiros da computação, preocupados em entregar processadores cada vez mais rápidos, perceberam que o custo-benefício da prática -- até então corrente --, de aumentar a frequência e densidade de transistores de um processador havia atingido um nível insustentável em termos de consumo de energia. Mudou-se, então, a estratégia: ao invés de criar processadores muito rápidos que executem apenas uma tarefa por vez, passa-se a criar processadores não tão rápidos que possam executar várias tarefas ao mesmo tempo.

Embora o paradigma sequencial, em nível de hardware, tenha mudado para o paralelo, restava mudar o paradigma corrente em nível de software. Escreveram-se, então, ferramentas para que programadores tirassem proveito deste paralelismo. Assim, várias linguagens antes pensadas para processadores *single-core* ganharam bibliotecas e APIs que auxiliaram o compilador a traduzir o código de maneira tal, que certas instruções independentes passaram a ser executadas usando concorrência. Foi o caso do C++ e da API OpenMP.

*Open Multi-Processing*, ou OpenMP, é uma API para C, C++ e Fortran, que permite, usando o modelo de execução *fork-join*, a adição de simultaneidade a um programa. Esta API é mantida e disponibilizada gratuitamente por um consórcio de várias gigantes do mundo da tecnologia, como AMD, Intel, IBM, e outras mais.

Este trabalho tentou paralelizar o código escrito no trabalho anterior, *Otimização de Memória Cache*, analisando os resultados encontrados. Além, usou o OpenMP em um novo código C++ a fim de entender seus benefícios, como pode ser visto adiante.

## Objetivos

- Paralelizar o código do trabalho anterior, *Otimização de Memória Cache*, usando o OpenMP;
  - Comparar e entender os resultados encontrados;
- Escrever novo código que faça uso adequado do OpenMP.

## Métodos - Modificando o Código Existente

Inicialmente, de posse do código escrito para o trabalho *Otimização de Memória Cache* (que realizou diversos testes em operações envolvendo matrizes de 150 linhas e 1500 colunas a fim de verificar os princípios do uso adequado de memória cache), procurou-se paralelizar somente os laços responsáveis pelas operações entre matrizes. As citadas operações estão contidas no arquivo `envTest.cpp`.

Ao preâmbulo do código, é necessário importar o arquivo de *header* `omp.h`. Como segue:

```C++
#include <omp.h>
```

Uma vez feita a importação, é necessário especificar um parâmetro ao compilador para a correta execução do programa: `-fopenmp`. De maneira que um comando em terminal, usando o compilador `g++`, teria um formato parecido com o que segue:

```bash
g++ -fopenmp <arquivo1.cpp> <arquivo2.cpp> ... <arquivon.cpp> -o <programa>
```

Novamente, ao cabeçalho do código, adicionou-se a seguinte linha, que permite controlar o número de threads usados.

```C++
#define NUM_THREADS 4
```

Antes de cada laço operando matrizes a ser identificado, é necessário adicionar um `#pragma` específico, que descreve como aquele laço deve ser tratado pelo compilador. O `#pragma` segue a seguinte estrutura:

```C++
#pragma omp parallel for num_threads(NUM_THREADS)
```

Adicionar o `#pragma` acima antes de um laço torna apenas aquele laço imediato paralelo. Isto é, para que tudo corra bem, é necessário que o laço seja escrito pensando no paralelismo. Geralmente se usa este `#pragma`, exatamente como está, em laços simples, ou seja, não-aninhados.

Para laços aninhados, do tipo

```C++
int a = 0;
for (int i = 0; i < 100; ++i) {
    for (int j = 0; j < 100; ++j) {
        a = i + j;
    }
}
```

pode passar despercebido aos sentidos do programador a noção de que o laço interno necessite do índice `i` do laço externo para a correta execução. Que isso, distribuído em várias *threads*, se traduz na leitura do mesmo `i` **NUM_THREADS** vezes, o que acarreta a chamada **condição de corrida** na escrita do valor dessa variável `a` do tipo `int`, valendo a *thread* que terminar por último.

Para evitar condição de corrida, usamos o parâmetro `private()`, que permite que variáveis sejam entendidas como *private* no escopo de cada *thread*. Ficando:

```C++
#pragma omp parallel for private(i, j) num_threads(NUM_THREADS)
```

Por último, como mencionado anteriormente, a adição de um `#pragma` só paraleliza o laço imediatamente subsequente. Para dividir a carga dos laços aninhandos de maneira balanceada entre os *threads* disponíveis, usamos o parâmetro `collapse(n)`, onde `n` é o número de laços a serem colapsados. Assim:

```C++
#pragma omp parallel for private(i, j) num_threads(NUM_THREADS) collapse(2)
```

Em seguida, se identificou em cada um dos 8 testes, quais laços eram os responsáveis pelas operações entre matrizes. Cada um deles é explicitado à seguir já adicionados de seus respectivos `#pragma`s.

### teste1()

```C++
#pragma omp parallel for private(i, j) num_threads(NUM_THREADS) collapse(2)
    for (j = colunas - 1; j >= 0; j--)
        for (i = linhas - 1; i >= 0; i--)
            m1[i][j] += m2[i][j] * round(cos(i) + sin(j));
```

### teste2()

```C++
#pragma omp parallel for private(i, j) num_threads(NUM_THREADS) collapse(2)
    for (i = linhas - 1; i >= 0; i--)
            for (j = colunas - 1; j >= 0; j--)
            m1[i][j] += m2[i][j] * round(cos(i) + sin(j));
```

### teste3()

```C++
#pragma omp parallel for private(i, j) num_threads(NUM_THREADS) collapse(2)
    for (i = 0; i < linhas; i++)
            for (j = 0; j < colunas; j++)
            m1[i][j] += m2[i][j] * round(cos(i) + sin(j));
```

### teste4()

```C++
#pragma omp parallel for private(i, j) num_threads(NUM_THREADS) collapse(2)
    for (i = 0; i < linhas; i++){
            for (j = 0; j < colunas; j++){
            m1[i][j] = i;
            m2[i][j] = i + j;
            m1[i][j] += m2[i][j] * round(cos(i) + sin(j));
        }
    }
```

### teste5()

```C++
#pragma omp parallel for private(i, j) num_threads(NUM_THREADS) collapse(2)
    for (i = 0; i < linhas; i++){
            for (j = 0; j < colunas; j++){
            m2[i][j] = i + j;
            m1[i][j] = i + m2[i][j] * round(cos(i) + sin(j));
        }
    }
```

### teste6()

```C++
#pragma omp parallel for private(i, j) num_threads(NUM_THREADS) collapse(2)
    for (i = 0; i < linhas; i++){
            for (j = 0; j < colunas; j++){
            m2[i][j] = i + j;
            m1[i][j] = i + m2[i][j] * round(coss[i] + seno[j]);
        }
    }
```

### teste7()

```C++
#pragma omp parallel for private(i, j) num_threads(NUM_THREADS) collapse(2)
    for (i = 0; i < linhas; i++){
            for (j = 0; j < colunas; j++){
            m2[i][j] = i + j;
            m1[i][j] = i + m2[i][j] * round( cos( rand() % n ) + sin( rand() % n ) );
        }
    }
```

### teste8()

```C++
#pragma omp parallel for private(i, j) num_threads(NUM_THREADS) collapse(2)
    for (i = 0; i < linhas; i++){
            for (j = 0; j < colunas; j++){
            m2[i][j] = i + j;
            m1[i][j] = i + m2[i][j] * round(coss[ rand() % n] + seno[ rand() % n]);
        }
    }
```

## Métodos - Escrevendo Novo Código Paralelo

Este código foi contido num único arquivo, `paralel.cpp`.

Inicialmente, na função `main()` foi definido um tamanho arbitrário para os arrays multidimensionais a serem criados, através da variável `tam`.

```C++
int tam = 20000;
```

Já na função `teste1()`, são declarados dois arrays multidiomensionais, `lista[tam][tam]` e `soma[tam][tam]`.

```C++ 
int** lista = new int* [tam];
for (i = 0; i < tam; ++i) {
    lista[i] = new int[tam];
}

int** soma = new int* [tam];
for (i = 0; i < tam; ++i) {
    soma[i] = new int[tam];
}
```

É inicializado, então, o array `lista[][]`:

```C++
// Inicialização do Array
for (i = 0; i < tam; ++i) {
    for (j = 0; j < tam; ++j) {
        lista[i][j] = j;  
    }
}
```

Seguem, do código, duas somas entre o mesmo array `lista` e o cálculo de seus respectivos tempos de operação. A primeira, sequencial, é escrita como:

```C++
t1 = clock();
// Somando os dois arrays
for (i = 0; i < tam; ++i) {
    for (j = 0; j < tam; ++j) {
        soma[i][j] += lista[i][j];
        // cout << soma[i][j] << endl;
    }
}
cout << (float)(clock() - t2)/CLOCKS_PER_SEC << "s" << endl;
```

A segunda, usando o OpenMP, é escrita como:

```C++
t2 = clock();
// Somando dois arrays usando paralelismo
#pragma omp parallel for private(i, j) num_threads(NUM_THREADS) collapse(2)
for (i = 0; i < tam; ++i) {
    for (j = 0; j < tam; ++j) {
        soma[i][j] += lista[i][j];
        // cout << soma[i][j] << endl;
    }
}
cout << (float)(clock() - t2)/CLOCKS_PER_SEC << "s" << endl;
```

<!-- Ademais, a fim de se ter noção a partir de que tamanho quadrado de `lista` começa a fazer sentido usar paralelização, foi colocado a chamada da função `teste1()` dentro de um laço, atualizando o valor de `tam` a cada execução: começando em $250$ e terminando em $10000$, passo $250$. -->

## Resultados e Discussão - Modificações

Quando se aplicou o OpenMP ao primeiro trabalho, *Otimização de Memória Cache*, percebeu-se que houve um aumento nos tempos de execução. Isto se deve ao fato de que a instância usada era pequena e o overhead da criação e gerenciamento de *threads* terminou por atrasar a execução.

A seguir, a comparação entre os tempos de cada teste.

## Resultados e Discussão - Novo Código

Usando um array multidimensional de igual número de linhas e colunas, pode-se ter um noção do ganho de performance conforme aumenta-se o tamanho do array, como pode-se ver descrito na tabela e gráficos abaixo.