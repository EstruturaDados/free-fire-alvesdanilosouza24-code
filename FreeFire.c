#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

// =========================
// 1. Struct
// =========================
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// ===================================
// 2. Cadastro de componentes
// ===================================
void cadastrarComponentes(Componente torre[], int *quantidade) {
    int continuar = 1;

    while (*quantidade < MAX_COMPONENTES && continuar) {
        printf("\nCadastro do componente %d:\n", *quantidade + 1);

        printf("Nome do componente: ");
        fgets(torre[*quantidade].nome, sizeof(torre[*quantidade].nome), stdin);
        torre[*quantidade].nome[strcspn(torre[*quantidade].nome, "\n")] = '\0';

        printf("Tipo do componente (ex: controle, suporte, propulsão): ");
        fgets(torre[*quantidade].tipo, sizeof(torre[*quantidade].tipo), stdin);
        torre[*quantidade].tipo[strcspn(torre[*quantidade].tipo, "\n")] = '\0';

        do {
            printf("Prioridade (1 a 10): ");
            scanf("%d", &torre[*quantidade].prioridade);
            getchar();
        } while (torre[*quantidade].prioridade < 1 || torre[*quantidade].prioridade > 10);

        (*quantidade)++;

        if (*quantidade < MAX_COMPONENTES) {
            printf("Deseja cadastrar outro componente? (1-Sim / 0-Não): ");
            scanf("%d", &continuar);
            getchar();
        } else {
            printf("\nLimite máximo de componentes atingido!\n");
        }
    }
}

// ==========================
// 3. Ordenações
// ==========================

// Bubble Sort (por nome)
int ordenarPorNomeBubble(Componente torre[], int quantidade) {
    int comparacoes = 0;
    Componente temp;

    for (int i = 0; i < quantidade - 1; i++) {
        for (int j = 0; j < quantidade - i - 1; j++) {
            comparacoes++;
            if (strcmp(torre[j].nome, torre[j + 1].nome) > 0) {
                temp = torre[j];
                torre[j] = torre[j + 1];
                torre[j + 1] = temp;
            }
        }
    }
    printf("\nComponentes ordenados por nome (Bubble Sort)\n");
    return comparacoes;
}

// Insertion Sort (por tipo)
int ordenarPorTipoInsertion(Componente torre[], int quantidade) {
    int comparacoes = 0;
    Componente chave;
    int j;

    for (int i = 1; i < quantidade; i++) {
        chave = torre[i];
        j = i - 1;
        while (j >= 0 && strcmp(torre[j].tipo, chave.tipo) > 0) {
            torre[j + 1] = torre[j];
            j--;
            comparacoes++;
        }
        torre[j + 1] = chave;
    }
    printf("\nComponentes ordenados por tipo (Insertion Sort)\n");
    return comparacoes;
}

// Selection Sort (por prioridade)
int ordenarPorPrioridadeSelection(Componente torre[], int quantidade) {
    int comparacoes = 0;
    Componente temp;
    int min;

    for (int i = 0; i < quantidade - 1; i++) {
        min = i;
        for (int j = i + 1; j < quantidade; j++) {
            comparacoes++;
            if (torre[j].prioridade < torre[min].prioridade) {
                min = j;
            }
        }
        if (min != i) {
            temp = torre[i];
            torre[i] = torre[min];
            torre[min] = temp;
        }
    }
    printf("\nComponentes ordenados por prioridade (Selection Sort)\n");
    return comparacoes;
}

// ==========================
// 4. Busca binária
// ==========================
int buscaBinaria(Componente torre[], int quantidade, char nomeBuscado[]) {
    int inicio = 0, fim = quantidade - 1, meio;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        int comparacao = strcmp(torre[meio].nome, nomeBuscado);

        if (comparacao == 0)
            return meio;
        else if (comparacao < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

// ==========================
// 5. Exibir Componentes
// ==========================
void exibirComponentes(Componente torre[], int n) {
    printf("\n--- Lista de Componentes ---\n");
    for (int i = 0; i < n; i++) {
        printf("%d. Nome: %s | Tipo: %s | Prioridade: %d\n",
               i + 1, torre[i].nome, torre[i].tipo, torre[i].prioridade);
    }
}

// ==========================
// 6. Função principal
// ==========================
int main() {
    Componente torre[MAX_COMPONENTES];
    int n = 0, comparacoes = 0;
    clock_t inicio, fim;
    double tempo;

    cadastrarComponentes(torre, &n);

    int opcao;
    printf("\nEscolha a ordenação:\n");
    printf("1 - Bubble Sort (por nome)\n");
    printf("2 - Insertion Sort (por tipo)\n");
    printf("3 - Selection Sort (por prioridade)\n");
    printf("Opção: ");
    scanf("%d", &opcao);

    inicio = clock();
    switch (opcao) {
        case 1:
            comparacoes = ordenarPorNomeBubble(torre, n);
            break;
        case 2:
            comparacoes = ordenarPorTipoInsertion(torre, n);
            break;
        case 3:
            comparacoes = ordenarPorPrioridadeSelection(torre, n);
            break;
        default:
            printf("Opção inválida!\n");
            return 0;
    }
    fim = clock();

    tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    exibirComponentes(torre, n);
    printf("\nComparações: %d\n", comparacoes);
    printf("Tempo de execução: %.6f segundos\n", tempo);

    if (opcao == 1) {
        char chave[30];
        getchar();
        printf("\nDigite o nome do componente-chave para busca binária: ");
        fgets(chave, sizeof(chave), stdin);
        chave[strcspn(chave, "\n")] = '\0';

        int pos = buscaBinaria(torre, n, chave);
        if (pos != -1)
            printf("\n✅ Componente '%s' encontrado na posição %d.\n", chave, pos + 1);
        else
            printf("\n❌ Componente '%s' não encontrado.\n", chave);
    }

    return 0;
}
