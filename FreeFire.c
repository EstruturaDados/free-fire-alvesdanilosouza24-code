#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 100

// =========================
// 1. Structs
// =========================

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// =========================
// 2. Mochila com vetor
// =========================

typedef struct {
    Item itens[MAX_ITENS];
    int tamanho;
} MochilaVetor;

// =========================
// Funções para vetor
// =========================

// Inserir item na mochila (vetor)
void inserirVetor(MochilaVetor* mochila, Item novo) {
    if (mochila->tamanho >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }
    mochila->itens[mochila->tamanho++] = novo;
}

// Remover item por nome
void removerVetor(MochilaVetor* mochila, char nome[]) {
    for (int i = 0; i < mochila->tamanho; i++) {
        if (strcmp(mochila->itens[i].nome, nome) == 0) {
            for (int j = i; j < mochila->tamanho - 1; j++) {
                mochila->itens[j] = mochila->itens[j + 1];
            }
            mochila->tamanho--;
            printf("Item '%s' removido!\n", nome);
            return;
        }
    }
    printf("Item nao encontrado!\n");
}

// Listar itens
void listarVetor(MochilaVetor* mochila) {
    printf("\n--- Itens na mochila (vetor) ---\n");
    for (int i = 0; i < mochila->tamanho; i++) {
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               mochila->itens[i].nome,
               mochila->itens[i].tipo,
               mochila->itens[i].quantidade);
    }
    printf("-------------------------------\n");
}

// Busca sequencial
Item* buscaSequencialVetor(MochilaVetor* mochila, char nome[], int* comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < mochila->tamanho; i++) {
        (*comparacoes)++;
        if (strcmp(mochila->itens[i].nome, nome) == 0) {
            return &mochila->itens[i];
        }
    }
    return NULL;
}

// Ordenar (Bubble Sort)
void ordenarVetor(MochilaVetor* mochila) {
    for (int i = 0; i < mochila->tamanho - 1; i++) {
        for (int j = 0; j < mochila->tamanho - i - 1; j++) {
            if (strcmp(mochila->itens[j].nome, mochila->itens[j + 1].nome) > 0) {
                Item temp = mochila->itens[j];
                mochila->itens[j] = mochila->itens[j + 1];
                mochila->itens[j + 1] = temp;
            }
        }
    }
    printf("Itens ordenados por nome!\n");
}

// Busca binária
Item* buscaBinariaVetor(MochilaVetor* mochila, char nome[], int* comparacoes) {
    int inicio = 0, fim = mochila->tamanho - 1;
    *comparacoes = 0;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(nome, mochila->itens[meio].nome);
        if (cmp == 0) return &mochila->itens[meio];
        else if (cmp < 0) fim = meio - 1;
        else inicio = meio + 1;
    }
    return NULL;
}

// =========================
// 3. Mochila com lista encadeada
// =========================

// Inserir item
void inserirLista(No** inicio, Item novo) {
    No* novoNo = (No*) malloc(sizeof(No));
    novoNo->dados = novo;
    novoNo->proximo = *inicio;
    *inicio = novoNo;
}

// Remover item
void removerLista(No** inicio, char nome[]) {
    No* atual = *inicio;
    No* anterior = NULL;

    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Item nao encontrado!\n");
        return;
    }

    if (anterior == NULL) *inicio = atual->proximo;
    else anterior->proximo = atual->proximo;

    free(atual);
    printf("Item '%s' removido da lista!\n", nome);
}

// Listar itens
void listarLista(No* inicio) {
    printf("\n--- Itens na mochila (lista encadeada) ---\n");
    No* atual = inicio;
    while (atual != NULL) {
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
    printf("------------------------------------------\n");
}

// Busca sequencial na lista
Item* buscaSequencialLista(No* inicio, char nome[], int* comparacoes) {
    *comparacoes = 0;
    while (inicio != NULL) {
        (*comparacoes)++;
        if (strcmp(inicio->dados.nome, nome) == 0) {
            return &inicio->dados;
        }
        inicio = inicio->proximo;
    }
    return NULL;
}

// =========================
// 4. Programa principal
// =========================

int main() {
    MochilaVetor mochilaV = { .tamanho = 0 };
    No* mochilaL = NULL;

    int opcao;
    char nome[30];
    Item novo;
    int comparacoes;

    do {
        printf("\n====== MENU ======\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar (sequencial)\n");
        printf("5 - Ordenar vetor\n");
        printf("6 - Buscar (binaria - vetor)\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
        case 1:
            printf("Nome: ");
            fgets(novo.nome, 30, stdin);
            novo.nome[strcspn(novo.nome, "\n")] = 0;

            printf("Tipo: ");
            fgets(novo.tipo, 20, stdin);
            novo.tipo[strcspn(novo.tipo, "\n")] = 0;

            printf("Quantidade: ");
            scanf("%d", &novo.quantidade);
            getchar();

            inserirVetor(&mochilaV, novo);
            inserirLista(&mochilaL, novo);
            break;

        case 2:
            printf("Nome do item a remover: ");
            fgets(nome, 30, stdin);
            nome[strcspn(nome, "\n")] = 0;
            removerVetor(&mochilaV, nome);
            removerLista(&mochilaL, nome);
            break;

        case 3:
            listarVetor(&mochilaV);
            listarLista(mochilaL);
            break;

        case 4:
            printf("Nome para buscar: ");
            fgets(nome, 30, stdin);
            nome[strcspn(nome, "\n")] = 0;
            Item* encontrado = buscaSequencialVetor(&mochilaV, nome, &comparacoes);
            if (encontrado)
                printf("Encontrado (vetor)! Quantidade: %d | Comparacoes: %d\n", encontrado->quantidade, comparacoes);
            else
                printf("Nao encontrado (vetor)! Comparacoes: %d\n", comparacoes);

            encontrado = buscaSequencialLista(mochilaL, nome, &comparacoes);
            if (encontrado)
                printf("Encontrado (lista)! Quantidade: %d | Comparacoes: %d\n", encontrado->quantidade, comparacoes);
            else
                printf("Nao encontrado (lista)! Comparacoes: %d\n", comparacoes);
            break;

        case 5:
            ordenarVetor(&mochilaV);
            break;

        case 6:
            printf("Nome para buscar (binaria): ");
            fgets(nome, 30, stdin);
            nome[strcspn(nome, "\n")] = 0;
            encontrado = buscaBinariaVetor(&mochilaV, nome, &comparacoes);
            if (encontrado)
                printf("Encontrado! Quantidade: %d | Comparacoes: %d\n", encontrado->quantidade, comparacoes);
            else
                printf("Nao encontrado! Comparacoes: %d\n", comparacoes);
            break;

        case 0:
            printf("Encerrando...\n");
            break;

        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}



