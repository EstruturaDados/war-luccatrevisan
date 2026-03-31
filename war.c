//codespaces > alterações > confirmar

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TERRITORIOS 5
#define TAM_STRING 100

struct Territorio {
    char nome[TAM_STRING];
    char corExercito[TAM_STRING];
    int tropas;
};

// Função para limpar o buffer do teclado (essencial após o scanf)
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    struct Territorio mapa[MAX_TERRITORIOS];
    int totalTerritorios = 0;
    int opcao;

    do {
        printf("\n=============================\n");
        printf("   GERENCIADOR DE TERRITÓRIOS\n");
        printf("1 - Cadastrar Territórios\n");
        printf("2 - Listar Territórios\n");
        printf("0 - Sair\n");
        printf("-----------------------------\n");
        printf("Escolha uma opção: ");
        
        if (scanf("%d", &opcao) != 1) {
            limparBufferEntrada();
            continue;
        }
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                printf("\n--- Iniciar Cadastro de Territórios ---\n");
                
                // Loop para cadastrar até o limite máximo
                while (totalTerritorios < MAX_TERRITORIOS) {
                    printf("\nCadastrando território %d de %d:\n", totalTerritorios + 1, MAX_TERRITORIOS);
                    
                    printf("Nome do Território: ");
                    fgets(mapa[totalTerritorios].nome, TAM_STRING, stdin);
                    mapa[totalTerritorios].nome[strcspn(mapa[totalTerritorios].nome, "\n")] = '\0';

                    printf("Cor do Exército: ");
                    fgets(mapa[totalTerritorios].corExercito, TAM_STRING, stdin);
                    mapa[totalTerritorios].corExercito[strcspn(mapa[totalTerritorios].corExercito, "\n")] = '\0';

                    printf("Quantidade de Tropas: ");
                    scanf("%d", &mapa[totalTerritorios].tropas);
                    limparBufferEntrada();

                    totalTerritorios++;
                    printf("Território salvo!\n");
                }
                
                printf("\nTodos os %d territórios foram ocupados!\n", MAX_TERRITORIOS);
                printf("Pressione Enter para voltar ao menu...");
                getchar();
                break;

            case 2:
                printf("\n--- Lista de Dominação Global ---\n");
                
                if (totalTerritorios == 0) {
                    printf("O mapa está vazio. Nenhum território conquistado.\n");
                } else {
                    for (int i = 0; i < totalTerritorios; i++) {
                        printf("---------------------------------\n");
                        printf("ID: %d | Território: %s\n", i + 1, mapa[i].nome);
                        printf("Exército: %s | Tropas: %d\n", mapa[i].corExercito, mapa[i].tropas);
                    }
                    printf("---------------------------------\n");
                }
                
                printf("\nPressione Enter para continuar...");
                getchar();
                break;

            case 0:
                printf("\nEncerrando tática de guerra...\n");
                break;

            default:
                printf("\nOpção inválida!\n");
                break;
        }

    } while (opcao != 0);

    return 0;
}