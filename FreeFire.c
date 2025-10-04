#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// Definição da struct Item
typedef struct {
    char nome[50];
    char tipo[20];
    int quantidade;
} Item;

// Protótipos das funções
void cadastrarItem(Item mochila[], int *quantidadeItens);
void removerItem(Item mochila[], int *quantidadeItens);
void listarItens(Item mochila[], int total);
void buscarItem(Item mochila[], int total);

int main() {
    Item mochila[MAX_ITENS];
    int total = 0;
    int opcao;

    do {
        printf("\n===== MENU DA MOCHILA =====\n");
        printf("1 - Cadastrar itens\n");
        printf("2 - Remover itens\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar itens\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpar o buffer do enter

        switch (opcao) {
            case 1:
                cadastrarItem(mochila, &total);
                break;
            case 2:
                removerItem(mochila, &total);
                break;
            case 3:
                listarItens(mochila, total);
                break;
            case 4:
                buscarItem(mochila, total);
                break;
            case 0:
                printf("\nSaindo do sistema. Até mais!\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}

// Função para cadastrar itens
void cadastrarItem(Item mochila[], int *quantidadeItens) {
    if (*quantidadeItens >= MAX_ITENS) {
        printf("Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novoItem;

    printf("Digite o nome do novo item: ");
    fgets(novoItem.nome, sizeof(novoItem.nome), stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = '\0';

    printf("Digite o tipo do item (arma, cura, etc.): ");
    fgets(novoItem.tipo, sizeof(novoItem.tipo), stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = '\0';

    printf("Digite a quantidade: ");
    scanf("%d", &novoItem.quantidade);
    getchar(); // limpar o buffer do enter

    mochila[*quantidadeItens] = novoItem;
    (*quantidadeItens)++;

    printf("Item cadastrado com sucesso!\n");
}

// Função para remover itens
void removerItem(Item mochila[], int *quantidadeItens) {
    if (*quantidadeItens == 0) {
        printf("A mochila está vazia. Nada para remover.\n");
        return;
    }

    char nomeBusca[50];
    printf("Digite o nome do item a ser removido: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < *quantidadeItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            // Desloca os itens seguintes uma posição para trás
            for (int j = i; j < *quantidadeItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*quantidadeItens)--;
            printf("Item removido com sucesso!\n");
            return;
        }
    }

    printf("Item '%s' nao encontrado na mochila.\n", nomeBusca);
}

// Função para listar itens
void listarItens(Item mochila[], int total) {
    if (total == 0) {
        printf("A mochila esta vazia.\n");
        return;
    }

    printf("\nItens na mochila:\n");
    for (int i = 0; i < total; i++) {
        printf("%d) Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// Função de busca sequencial
void buscarItem(Item mochila[], int total) {
    if (total == 0) {
        printf("A mochila está vazia, nada para buscar.\n");
        return;
    }

    char nomeBusca[50];
    printf("Digite o nome do item a ser buscado: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }

    printf("Item '%s' não encontrado na mochila.\n", nomeBusca);
}
