#include "functions.h"


// Multiplicação de Matrizes (n^3)

llint **alocar_matriz(int n) {
    llint **temp = (llint **) malloc(n * sizeof(llint *));
    for(int i = 0; i < n; i++)
        temp[i] = (llint *) malloc(n * sizeof(llint));

    return temp;
}

void desalocar_matriz(llint **matrix, int n) {
    // Libera a memória alocada
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void carregar_arquivoMatrizes(int *n, llint ***matrizA, llint ***matrizB, llint ***matrizC) {
    char nomeArquivo[100];

    printf("Digite o nome do arquivo: ");
    scanf("%s", nomeArquivo);

    FILE *arquivo = fopen(nomeArquivo, "r");

    printf("\nTentando abrir o arquivo: %s\n", nomeArquivo);

    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo.\n\n");
        return; // Encerra a função sem interromper o programa
    }

    if (fscanf(arquivo, "%d", n) != 1) {
        printf("Erro ao ler o tamanho da matriz.\n\n");
        fclose(arquivo);
        return;
    }

    *matrizA = alocar_matriz(*n);
    *matrizB = alocar_matriz(*n);
    *matrizC = alocar_matriz(*n);

    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            if (fscanf(arquivo, "%lld", &(*matrizA)[i][j]) != 1) {
                printf("Erro ao preencher elementos da matriz A.\n\n");
                fclose(arquivo);
                return;
            }
        }
    }

    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            if (fscanf(arquivo, "%lld", &(*matrizB)[i][j]) != 1) {
                printf("Erro ao preencher elementos da matriz B.\n\n");
                fclose(arquivo);
                return;
            }
        }
    }

    printf("Matrizes carregadas com sucesso.\n\n");
    fclose(arquivo);
}

void multiplica_matriz_n3(llint **a, llint **b, llint **c, int N) {

    clock_t t = tempo_inicio();

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            c[i][j] = 0;
            for (int k = 0; k < N; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    tempo_fim(t);
}

void imprimir_matrizResultante(llint **c, int N) {
    printf("Matriz resultante:\n");

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%lld\t", c[i][j]);
        }
        printf("\n");
    }
}

llint **somar_matrizes(llint **a, llint **b, int n) {
    llint **temp = alocar_matriz(n);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            temp[i][j] = a[i][j] + b[i][j];

    return temp;
}

llint **subtrair_matrizes(llint **a, llint **b, int n) {
    llint **temp = alocar_matriz(n);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            temp[i][j] = a[i][j] + b[i][j];

    return temp;
}

llint **multiplica_strassen(llint **a, llint **b, int n) {

    llint** c = alocar_matriz(n);
    int k = n/2;
    if (n == 1) {
        llint** TEMP = alocar_matriz(1);
        TEMP[0][0] = a[0][0] * b[0][0];
        return TEMP;
    }

    llint **a11 = alocar_matriz(k);
    llint **a12 = alocar_matriz(k);
    llint **a21 = alocar_matriz(k);
    llint **a22 = alocar_matriz(k);
    llint **b11 = alocar_matriz(k);
    llint **b12 = alocar_matriz(k);
    llint **b21 = alocar_matriz(k);
    llint **b22 = alocar_matriz(k);

    for(int i=0; i<k; i++) {
        for(int j=0; j<k; j++) {
            a11[i][j] = a[i][j];
            a12[i][j] = a[i][k + j];
            a21[i][j] = a[k + i][j];
            a22[i][j] = a[k + i][k + j];
            b11[i][j] = b[i][j];
            b12[i][j] = b[i][k + j];
            b21[i][j] = b[k + i][j];
            b22[i][j] = b[k + i][k + j];
        }
    }

    llint** p2 = multiplica_strassen(somar_matrizes(a11, a12, k), b22, k);
    llint** p6 = multiplica_strassen(subtrair_matrizes(a12, a22, k), somar_matrizes(b21, b22, k), k);
    desalocar_matriz(a12, k);
    llint** p1 = multiplica_strassen(a11, subtrair_matrizes(b12, b22, k), k);
    llint** p3 = multiplica_strassen(somar_matrizes(a21, a22, k), b11, k);
    llint** p4 = multiplica_strassen(a22, subtrair_matrizes(b21, b11, k), k);
    desalocar_matriz(b21, k);
    llint** p5 = multiplica_strassen(somar_matrizes(a11, a22, k), somar_matrizes(b11, b22, k), k);
    desalocar_matriz(a22, k);
    desalocar_matriz(b22, k);
    llint** p7 = multiplica_strassen(subtrair_matrizes(a11, a21, k), somar_matrizes(b11, b12, k), k);

    desalocar_matriz(a11, k);
    desalocar_matriz(a21, k);
    desalocar_matriz(b11, k);
    desalocar_matriz(b12, k);


    llint** c12 = somar_matrizes(p1, p2, k);
    llint** c22 = subtrair_matrizes(somar_matrizes(somar_matrizes(p5, p1, k), p3, k), p7, k);
    desalocar_matriz(p1, k);
    desalocar_matriz(p7, k);
    llint** c11 = subtrair_matrizes(somar_matrizes(somar_matrizes(p5, p4, k), p6, k), p2, k);
    desalocar_matriz(p2, k);
    desalocar_matriz(p5, k);
    desalocar_matriz(p6, k);
    llint** c21 = somar_matrizes(p3, p4, k);

    desalocar_matriz(p3, k);
    desalocar_matriz(p4, k);

    for(int i = 0; i < k; i++) {
        for(int j = 0; j < k; j++) {
            c[i][j] = c11[i][j];
            c[i][j + k] = c12[i][j];
            c[k + i][j] = c21[i][j];
            c[k + i][k + j] = c22[i][j];
        }
    }

    desalocar_matriz(c11, k);
    desalocar_matriz(c12, k);
    desalocar_matriz(c21, k);
    desalocar_matriz(c22, k);

    return c;
}

// Alg. da Mochila

// Função para calcular o máximo entre dois números inteiros
int maior(int a, int b) {
    return (a > b) ? a : b;
}

// Função para resolver o problema da Mochila Binária
int mochilaBinaria(llint capacidade, Item* itens, int totalItens) {
    int** tabela;
    tabela = (int **) (int **) malloc((totalItens + 1) * sizeof(int *));

    for (int i = 0; i <= totalItens; i++) {
        tabela[i] = (int *) (int *) malloc((capacidade + 1) * sizeof(int));
    }

    clock_t t = tempo_inicio();

    for (int i = 0; i <= totalItens; i++) {
        for (int w = 0; w <= capacidade; w++) {
            if (i == 0 || w == 0) {
                tabela[i][w] = 0;
            } else if (itens[i - 1].peso <= w) {
                tabela[i][w] = maior(itens[i - 1].valor + tabela[i - 1][w - itens[i - 1].peso], tabela[i - 1][w]);
            } else {
                tabela[i][w] = tabela[i - 1][w];
            }
        }
    }

    tempo_fim(t);

    int resultado = tabela[totalItens][capacidade];

    // Liberar memória
    for (int i = 0; i <= totalItens; i++) {
        free(tabela[i]);
    }
    free(tabela);

    return resultado;
}

// Função para carregar arquivo da Mochila Binária
void carregar_arquivo_mochila(llint *capacidade, int *totalItens, Item** itens) {
    char nome_arquivo[50];
    FILE* arquivo;

    printf("Digite o nome do arquivo para a mochila: ");
    scanf("%s", nome_arquivo);

    arquivo = fopen(nome_arquivo, "r");

    if (arquivo == NULL) {
        printf("Erro: Arquivo '%s' nao encontrado.\n", nome_arquivo);
        return;
    }

    fscanf(arquivo, "%lld", capacidade);
    fscanf(arquivo, "%d", totalItens);

    *itens = (Item*)malloc((*totalItens) * sizeof(Item));

    for (int i = 0; i < *totalItens; i++) {
        fscanf(arquivo, "%d %d", &(*itens)[i].peso, &(*itens)[i].valor);
    }

    printf("Arquivo carregado.\n\n");

    fclose(arquivo);
}


// -- Medir o Tempo --

// Registra o tempo inicial
clock_t tempo_inicio() {
    clock_t start = clock();
    printf("Iniciando timer.\n");
    return start;
}

// Calcula o tempo decorrido em segundos e imprime o tempo decorrido
void tempo_fim(clock_t start) {
    clock_t end = clock();

    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Tempo de execução: %f segundos,\n", cpu_time_used);
}
