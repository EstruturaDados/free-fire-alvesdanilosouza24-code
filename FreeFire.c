#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20 // maximo de conponentes a ser cadastrados  (para montagem da torre)

// =========================
// 1. Structs
// =========================

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
}Componente;

// ===================================
// 2. CADASTRANDO COMPONENTES DA TORRE
// ===================================

void cadastrarComponentes(Componente torre[], int *quantidade) {
    int continuar = 1;

    while (*quantidade < MAX_COMPONENTES && continuar) {
        printf("\nCadastro do componente %d:\n", *quantidade + 1);

        printf("Nome do componente: ");
        fgets(torre[*quantidade].nome, sizeof(torre[*quantidade].nome), stdin);
        torre[*quantidade].nome[strcspn(torre[*quantidade].nome, "\n")] = '\0';  // remove o '\n'

        printf("Tipo do componente (ex: controle, suporte, propulsão): ");
        fgets(torre[*quantidade].tipo, sizeof(torre[*quantidade].tipo), stdin);
        torre[*quantidade].tipo[strcspn(torre[*quantidade].tipo, "\n")] = '\0';

        do {
            printf("Prioridade (1 a 10): ");
            scanf("%d", &torre[*quantidade].prioridade);
            getchar(); // limpa o buffer do teclado
        } while (torre[*quantidade].prioridade < 1 || torre[*quantidade].prioridade > 10);

        (*quantidade)++;

        if (*quantidade < MAX_COMPONENTES) {
            printf("Deseja cadastrar outro componente? (1-Sim / 0-Não): ");
            scanf("%d", &continuar);
            getchar(); // limpa o buffer
        } else {
            printf("\nLimite máximo de componentes atingido!\n");
        }
    }
}

// =======================
// ORDENAR (bubble sort) 
// =======================

void ordenarPornome(Componente torre[], int quantidade) {
     Componente temp;  // variável auxiliar para troca

    for (int i = 0; i < quantidade - 1; i++) {
        for (int j = 0; j < quantidade - i - 1; j++) {
            if (strcmp(torre[j].nome, torre[j + 1].nome) > 0) {
                // troca os elementos
                temp = torre[j];
                torre[j] = torre[j + 1];
                torre[j + 1] = temp;
            }
        }
    }

    printf("\nComponentes ordenados por nome (ordem alfabética):\n");
}
// ========================
// ORDENAR (Isertion sort) 
// =========================

void ordenarPorNomeInsertion(Componente torre[], int quantidade) {
    Componente chave;
    int j;

    for (int i = 1; i < quantidade; i++) {
        chave = torre[i];
        j = i - 1;

        while (j >= 0 && strcmp(torre[j].nome, chave.nome) > 0) {
            torre[j + 1] = torre[j];
            j--;
        }

        torre[j + 1] = chave;
    }

    printf("\nComponentes ordenados por nome (Insertion Sort):\n");
}

//===============================
// ORDERNAR (Selection sort)
// ==============================

void ordenarPorNomeSelection(Componente torre[], int quantidade) {
    int indiceMenor;
    Componente temp;

    for (int i = 0; i < quantidade - 1; i++) {
        indiceMenor = i;

        for (int j = i + 1; j < quantidade; j++) {
            if (strcmp(torre[j].nome, torre[indiceMenor].nome) < 0) {
                indiceMenor = j;
            }
        }

        if (indiceMenor != i) {
            temp = torre[i];
            torre[i] = torre[indiceMenor];
            torre[indiceMenor] = temp;
        }
    }

    printf("\nComponentes ordenados por nome (Selection Sort):\n");
}


int buscabinaria(Componente torre[], int nome, int quantidade) {
    int inicio = 0;
    int fim = nome -1;

while (inicio <= fim) {
     int meio = inicio + (fim - inicio) /2
     if (Componente[meio] === quantidade) {
        return meio;

else if (componente[meio] < quanttidade) {
    inicio = meio + -1;

else {
    fim = meio - 1;

    return -1;
}
}
     }
}
