#include <stdio.h>
#include <string.h>
#include <stdlib.h> // biblioteca necessaria para funções de string (strcpy, strcmp)

#define MAX_ITENS 10


struct Aluno {
    char nome[50];
    char tipo[20];
    int quantidade;

}; Item;

int main() {
    Item inventario[MAX_ITENS];
    int totalItens = 0;

    printf("=== Cadastro de Itens ===\n");

    while (totalItens < MAX_ITENS) {
        printf("\nItem %d:\n", totalItens + 1);

        // Leitura do nome
        printf("Nome: ");
        fgets(inventario[totalItens].nome, sizeof(inventario[totalItens].nome), stdin);
        inventario[totalItens].nome[strcspn(inventario[totalItens].nome, "\n")] = '\0';

        // Leitura do tipo
        printf("Tipo (arma, municao, cura): ");
        fgets(inventario[totalItens].tipo, sizeof(inventario[totalItens].tipo), stdin);
        inventario[totalItens].tipo[strcspn(inventario[totalItens].tipo, "\n")] = '\0';

        // Leitura da quantidade
        printf("Quantidade: ");
        scanf("%d", &inventario[totalItens].quantidade);

        // Limpa o buffer do teclado
        while(getchar() != '\n');

        totalItens++;

        // Verifica se o usuário quer continuar
        if (totalItens < MAX_ITENS) {
            char opcao;
            printf("Deseja cadastrar outro item? (s/n): ");
            scanf("%c", &opcao);
            while(getchar() != '\n'); // limpa buffer

            if (opcao != 's' && opcao != 'S') {
                break;
            }
        }
    }

    // Exibe os itens cadastrados
    printf("\n=== Itens Cadastrados ===\n");
    for (int i = 0; i < totalItens; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1,
               inventario[i].nome,
               inventario[i].tipo,
               inventario[i].quantidade);
    }

    

