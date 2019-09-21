# Parte 1 - Otimização de Memória Cache

## Introdução

A memória Cache é uma pequena quantidade de memória localizada entre a memória principal do computador e a CPU (Unidade Lógica Aritmética).

A Cache tem a função de carregar uma porção dos dados da memória principal para que o processador possa acessa-los de forma mais rápida. 

Quando a CPU necessita de dados, recorre primeiro a Cache, caso não encontre, um bloco de dados é requisitado a memória principal, essa requisição é chamada de **Cache Miss** e quando não há necessidade de acessar a memória principal, obtemos um **Cache Hit**.

Os blocos solitados a memória principal contêm os dados que a CPU necessita no momento, e dados extras, dos quais a CPU pode solicitar em momentos futuros. Esta operação obedece o princípio da localidade, que pode ser **Espacial** ou **Temporal**

O Princípio da Localidade Temporal diz que um dado acessado recentemente tem mais chances de ser usado novamente, do que um dado usado há mais tempo.

Já o Princípio da Localidade Espacial diz que há uma probabilidade de acesso maior para dados e instruções em endereços próximos àqueles acessados recentemente.

## Objetivos

Existem algumas formas de otimizar a Memória Cache, muitas destas melhorias são feitas no memento do projeto, onde será definido o seu tipo de mapeamento, número de blocos, tamanho e etc.

Porém algumas melhorias também podem ser realizadas por meio de software.

A seguir, será analisado um algoritmo que ignora completamente o uso da memória cache e comparar com sua versão otimizada.

## Métodos

Nesta Sessão, serão descritas as etapas e métodos utilizados para a realização e implementação deste trabalho.

Inicialmente foram criadas duas matrizes do tipo inteiro e dimensões definidas pelo usuário.

```C++
    int m1[linhas][colunas];
    int m2[linhas][colunas];
```
As duas matrizes serão somadas e multiplicadas por uma função trigonométricas e o resultado será armazenado na matriz m1.

O tempo de execução final de cada algoritmo é obtido através de uma média, onde o mesmo é executado n vezes e seu tempo de execução é armazenado no vetor tempoTotal[].

```C++
clock_t inicio, fim;
double tempoTotal[n];	//Armazena tempos de execução do algorítmo

for (int k = 0; k < n; k++){
    
    inicio = clock();
   		//... Código
    fim = clock();

    tempoTotal[k] = (double)(fim - inicio);
}
```

### _teste1()_

Esta função contém a versão não otimizada do código. Seu objetivo é desprezar a utilização de Memória Cache, a inicialização das matrizes é feita de forma separada, utilizando 02 laços de repetição e um terceiro para as operações.

A estrutura FOR também está invertida e operando do fim para o começo, esta atitude despreza o princípio da localidade espacial.

```C++
for (int j = colunas - 1; j >= 0; j--)
	for (int i = linhas - 1; i >= 0; i--)
        //m1[i][j] = ...
```

Além disso no loop em que ocorrem as operações com matrizes, há a cada iteração uma operação trigonométrica (possuem um maior custo computacional).

### _teste2()_

Esta função é semelhante a função teste1(), porém, na estrutura de loop FOR as linhas são computadas antes das colunas.

```C++
for (int i = linhas - 1; i >= 0; i--)
     for (int j = colunas - 1; j >= 0; j--)
        //m1[i][j] = ...
```

### _teste3()_

Esta função é semelhante às anteriores e tem o objetivo de analisar se houve ganho de desempenho ao acessar as matrizes de forma ascendente. Esta operação deve aproveitar melhor o princípio da localidade espacial para inicialização das matrizes.

```C++
for (int i = 0; i < linhas; i++)
     for (int j = 0; j < colunas; j++)
        //m1[i][j] = ...
```

### _teste4()_

A função _teste4()_ concatena a inicialização e operações das matrizes em um único loop For

```C++
for (int i = 0; i < linhas; i++){
     for (int j = 0; j < colunas; j++){
        m1[i][j] = i;
        m2[i][j] = i + j;
        m1[i][j] += m2[i][j] * round(cos(i) + sin(j));
    }
}
```

Porém a mesma ainda conta com inicializações desnecessárias e operações trigonométricas.

### _teste5()_

A função _teste5()_ analiza se há ganho de desempenho ao inicializar a matriz m1[][] diretamente com o valor final, removendo sua inicialização desnecessária ao transferir o valor de i para a soma com a matriz m2[][].

```C++
for (int i = 0; i < linhas; i++){
     for (int j = 0; j < colunas; j++){
        m2[i][j] = i + j;
        m1[i][j] = i + m2[i][j] * round(cos(i) + sin(j));
    }
}
```

Porém a mesma ainda conta com inicializações desnecessárias e operações trigonométricas.


### _teste6()_

Para evitar o cálculo de funções trigonométricas a cada iteração, na função _teste6()_ foram criados dois vetores, para armazenar os senos e cossenos, respectivamente, desta maneira os valores podem ser carregados diretamente em vez de ter um recálculo a todo instante

```C++
short seno[n], coss[n];  		//valores serão arredondados

for (int k = 0; k < n; k++){
    seno[k] = sin(k);       	/** Inserindo valores trigonométricos em um vetor   **/
    coss[k] = cos(k);       	/** para evitar cálculos a cada iteração            **/
}
```


### _teste7()_

A função deseja calcular senos e cossenos de valores aleatórios, este cálculo é realizado a cada iteração.

```C++
for (int i = 0; i < linhas; i++)
     for (int j = 0; j < colunas; j++)
        //...round(cos( rand() % n) + sin( rand() % n));
```


### _teste8()_

Esta função é semelhante a anterior e objetiva utilizar o Princípio da Localidade Temporal, tendo em vista que o seno ou cosseno de um valor pode ser requisitado mais de uma vez em sequência.	

```C++
short seno[n], coss[n];  		//valores serão arredondados

for (int k = 0; k < n; k++){
    seno[k] = sin(k);       	/** Inserindo valores trigonométricos em um vetor   **/
    coss[k] = cos(k);       	/** para evitar cálculos a cada iteração            **/
}

for (int i = 0; i < linhas; i++)
     for (int j = 0; j < colunas; j++)
     	//...  round(coss[ rand() % n] + seno[ rand() % n])
```

## Resultados
Nesta Seção, serão apresentados os resultados das execucões do algoritmo, assim como os gráficos de execução de cada melhoria feita. 

Em uma análise geral, percebe-se uma melhoria gradativa em cada otimização realizada ao longo dos testes. Sendo o _teste6()_ o que obteve melhor desempenho, tendo em vista que é o algoritmo que melhor utiliza o Princípio da Localidade Espacial.

Perceba que o _teste8()_ também apresenta resultados satisfatórios, uma vez que a cada iteração o mesmo deve obter dois número aleatório para aplicar a uma função seno e cosseno.

![tempoExecucao](https://github.com/FelipeNasci/trabalhoACII/blob/master/Parte%201/img/tempoExecucao.PNG?raw=true)


### Tempos de execução em 100 iterações para cada _teste()_

![tempoExecucaoTeste1](https://github.com/FelipeNasci/trabalhoACII/blob/master/Parte%201/img/tempoExecucaoTeste1.png?raw=true)

![tempoExecucaoTeste2](https://github.com/FelipeNasci/trabalhoACII/blob/master/Parte%201/img/tempoExecucaoTeste2.png?raw=true)

![tempoExecucaoTeste3](https://github.com/FelipeNasci/trabalhoACII/blob/master/Parte%201/img/tempoExecucaoTeste3.png?raw=true)

![tempoExecucaoTeste4](https://github.com/FelipeNasci/trabalhoACII/blob/master/Parte%201/img/tempoExecucaoTeste4.png?raw=true)

![tempoExecucaoTeste5](https://github.com/FelipeNasci/trabalhoACII/blob/master/Parte%201/img/tempoExecucaoTeste5.png?raw=true)

![tempoExecucaoTeste6](https://github.com/FelipeNasci/trabalhoACII/blob/master/Parte%201/img/tempoExecucaoTeste6.png?raw=true)

![tempoExecucaoTeste7](https://github.com/FelipeNasci/trabalhoACII/blob/master/Parte%201/img/tempoExecucaoTeste7.png?raw=true)

![tempoExecucaoTeste8](https://github.com/FelipeNasci/trabalhoACII/blob/master/Parte%201/img/tempoExecucaoTeste8.png?raw=true)

[]()