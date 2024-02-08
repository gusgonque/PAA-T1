#ifndef PAA_T1_FUNCTIONS_H
#define PAA_T1_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef long long int llint;


// -- Matrizes --


// Descrição: Aloca memória para a matriz.
// Pré-Condição: Inteiro com a ordem da matriz quadrada.
// Pós-Condição: Retorna o ponteiro para a memória alocada.
llint **alocar_matriz(int n);

// Descrição: Desaloca memória da matriz.
// Pré-Condição: Ponteiro da matriz com memória alocada, e a ordem da matriz.
// Pós-Condição: A memória que outrora estava alocada para o ponteiro, é desalocada
void desalocar_matriz(llint **matrix, int n);

// Descrição: Carrega as matrizes A e B a partir do arquivo solicitado, e aloca memória para as três matrizes que serão usadas nas multiplicações.
// Pré-Condição: Ordem das matrizes, e os ponteiros delas.
// Pós-Condição: São carregadas as matrizes A e B, alocando memória para as três matrizes que serão usadas nas multiplicações.
void carregar_arquivoMatrizes(int *n, llint ***matrizA, llint ***matrizB, llint ***matrizC);

// Descrição: Multiplicação padrão das matrizes. Será multiplicado as matrizes 'a' e 'b' e o resultado em 'c'.
// Pré-Condição: Duas matrizes já carregadas, a matriz resultante, e a ordem delas.
// Pós-Condição: O resultado da multiplicação é sálvo em 'c'.
void multiplica_matriz_n3(llint **a, llint **b, llint **c, int N);

// Descrição: Imprime a matriz resultante das multiplicações.
// Pré-Condição: Matriz 'c' calculada, e a ordem dela.
// Pós-Condição: É impresso a matriz resultante.
void imprimir_matrizResultante(llint **c, int N);

// Descrição: Soma as duas matrizes passadas como parâmetro.
// Pré-Condição: Duas matrizes quadradas e a ordem delas.
// Pós-Condição: Retorna uma matriz com a soma de 'a' e 'b'.
llint **somar_matrizes(llint **a, llint **b, int n);

// Descrição: Subtrai as duas matrizes passadas como parâmetro.
// Pré-Condição: Duas matrizes quadradas e a ordem delas.
// Pós-Condição: Retorna uma matriz com a subtração de 'a' e 'b'.
llint **subtrair_matrizes(llint **a, llint **b, int n);

// Descrição: Realiza a multiplicação das matrizes 'a' e 'b', usando o algoritmo de Strassen.
// Pré-Condição: Duas matrizes quadradas, e a ordem delas.
// Pós-Condição: É retornada a Matriz resultante.
llint **multiplica_strassen(llint **a, llint **b, int n);


// -- Alg. da Mochila --


// Descrição: Estrutura para representar um item
typedef struct {
    int peso;
    int valor;
} Item;

// Descrição: Função para calcular o máximo entre dois números inteiros.
// Pré-Condição: Dois números inteiros.
// Pós-Condição: Retorna o maior número entre os dois passados como parâmetro.
int maior(int a, int b);

// Descrição: Função para resolver o problema da Mochila Binária.
// Pré-Condição: Capacidade da mochila, os itens, e o total de itens.
// Pós-Condição: É retornado o valor máximo de itens que podem ser colocados na mochila.
int mochilaBinaria(llint capacidade, Item* itens, int totalItens);

// Descrição: Função para carregar arquivo da Mochila Binária.
// Pré-Condição: Ponteiros para a capacidade da mochila, os itens, e o total de itens.
// Pós-Condição: Os ponteiros são carregados com as informações do arquivo.
void carregar_arquivo_mochila(llint *capacidade, int *totalItens, Item** itens);


// -- Medir o Tempo --

// Descrição: Registra o tempo inicial
// Pré-Condição: Nenhum.
// Pós-Condição: Inicia um contador que é retornado.
clock_t tempo_inicio();

// Descrição: Calcula o tempo decorrido em segundos e imprime o tempo decorrido
// Pré-Condição: Uma variável inicializada pela função tempo_inicio().
// Pós-Condição: É impresso na tela o tempo em segundos desde que a função tempo_inicio() foi chamada.
void tempo_fim(clock_t start);

#endif //PAA_T1_FUNCTIONS_H
