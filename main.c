#include "functions.h"

int menu() {
    int x;

    printf("1 - Multiplicação de matrizes.\n");
    printf("2 - Algoritmo de Strassen.\n");
    printf("3 - Mostrar a matriz resultante da multiplicação.\n");
    printf("4 - Algoritmo da mochila.\n");
    printf("5 - Carregar arquivo para matrizes.\n");
    printf("6 - Carregar arquivo para mochila.\n");
    printf("7 - Desalocar memória das 3 matrizes.\n");
    printf("0 - Encerrar o programa.\n");
    printf("Selecione uma opção: ");
    scanf("%d", &x);
    printf("\n");
    return x;
}

void menu_principal(llint ***a, llint ***b, llint ***c, int *n, llint *capacidade, int *totalItens, Item **itens) {
    int sel;
    clock_t t;

    while (1) {
        sel = menu();

        switch (sel) {
            case 1:
                multiplica_matriz_n3(*a, *b, *c, *n);
                break;

            case 2:
                t = tempo_inicio();
                *c = multiplica_strassen(*a, *b, *n);
                tempo_fim(t);
                break;

            case 3:
                imprimir_matrizResultante(*c, *n);
                break;

            case 4:
                printf("O valor máximo que pode ser colocado na mochila eh: %d\n\n", mochilaBinaria(*capacidade, *itens, *totalItens));
                break;

            case 5:
                carregar_arquivoMatrizes(n, a, b, c);
                break;

            case 6:
                carregar_arquivo_mochila(capacidade, totalItens, itens);
                break;

            case 7:
                desalocar_matriz(*a, *n);
                desalocar_matriz(*b, *n);
                desalocar_matriz(*c, *n);
                printf("Memória das matrizes desalocada.\n");
                break;

            case 0:
                return;

            default:
                printf("Opção inválida.\n");
        }
    }
}

int main() {
    int n;
    llint **a, **b, **c;
    llint capacidade;
    int totalItens;
    Item *itens = NULL;

    menu_principal(&a, &b, &c, &n, &capacidade, &totalItens, &itens);

    return 0;
}