//codespaces > alterações > confirmar

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_STRING 100

// Struct principal conforme solicitado
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// --- PROTÓTIPOS DAS FUNÇÕES ---
void limparBuffer();
void cadastrarTerritorios(Territorio* mapa, int quantidade);
void listarTerritorios(Territorio* mapa, int quantidade);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);

int main() {
    // Inicializa a semente para números aleatórios (Dados de Guerra)
    srand(time(NULL));

    int numTerritorios;
    printf("Bem-vindo ao Simulador de Guerra!\n");
    printf("Quantos territórios deseja gerenciar no mapa? ");
    scanf("%d", &numTerritorios);
    limparBuffer();

    // REQUISITO: Alocação dinâmica utilizando calloc (zera a memória)
    Territorio* mapa = (Territorio*)calloc(numTerritorios, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro crítico: Falha ao alocar memória para o mapa.\n");
        return 1;
    }

    int opcao;
    do {
        printf("\n--- MENU ESTRATÉGICO ---\n");
        printf("1 - Cadastrar todos os territórios\n");
        printf("2 - Listar territórios\n");
        printf("3 - Iniciar Ataque\n");
        printf("0 - Sair do Jogo\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                cadastrarTerritorios(mapa, numTerritorios);
                break;
            case 2:
                listarTerritorios(mapa, numTerritorios);
                break;
            case 3: {
                int atqIdx, defIdx;
                listarTerritorios(mapa, numTerritorios);
                
                printf("\nÍndice do território ATACANTE (1 a %d): ", numTerritorios);
                scanf("%d", &atqIdx);
                printf("Índice do território DEFENSOR (1 a %d): ", numTerritorios);
                scanf("%d", &defIdx);
                limparBuffer();

                // Ajuste para índice de array (0 a N-1)
                atqIdx--; defIdx--;

                // Validação de segurança
                if (atqIdx >= 0 && atqIdx < numTerritorios && defIdx >= 0 && defIdx < numTerritorios) {
                    // REQUISITO: Não atacar a própria cor
                    if (strcmp(mapa[atqIdx].cor, mapa[defIdx].cor) == 0) {
                        printf("\n[ERRO] Você não pode atacar seu próprio exército (%s)!\n", mapa[atqIdx].cor);
                    } else if (mapa[atqIdx].tropas <= 1) {
                        printf("\n[ERRO] Tropas insuficientes para atacar (mínimo 2).\n");
                    } else {
                        // REQUISITO: Uso de ponteiros para manipular os dados
                        atacar(&mapa[atqIdx], &mapa[defIdx]);
                    }
                } else {
                    printf("\nÍndices inválidos!\n");
                }
                break;
            }
            case 0:
                liberarMemoria(mapa);
                printf("Memória liberada. Encerrando...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}

// --- IMPLEMENTAÇÃO DAS FUNÇÕES MODULARIZADAS ---

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Cadastro em loop conforme solicitado
void cadastrarTerritorios(Territorio* mapa, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);
        printf("Nome: ");
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do Exército: ");
        fgets(mapa[i].cor, 10, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Quantidade de Tropas iniciais: ");
        scanf("%d", &mapa[i].tropas);
        limparBuffer();
    }
    printf("\nMapa configurado com sucesso!\n");
}

void listarTerritorios(Territorio* mapa, int quantidade) {
    printf("\n--- ESTADO ATUAL DO MAPA ---\n");
    for (int i = 0; i < quantidade; i++) {
        printf("[%d] %-15s | Cor: %-10s | Tropas: %d\n", 
                i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// REQUISITO: Função de ataque manipulando ponteiros
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\nATAQUE INICIADO: %s (%s) vs %s (%s)\n", 
            atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    // Simulação de dados (1 a 6)
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("Dado Atacante: %d | Dado Defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("VITÓRIA! O território %s foi conquistado por %s!\n", defensor->nome, atacante->cor);
        
        // REQUISITO: Atualização de campos (muda cor e transfere metade das tropas)
        strcpy(defensor->cor, atacante->cor);
        int tropasTransferidas = atacante->tropas / 2;
        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;
        
        printf("Tropas remanescentes no ataque: %d\n", atacante->tropas);
        printf("Tropas de ocupação no defensor: %d\n", defensor->tropas);
    } else {
        printf("DERROTA! O ataque falhou.\n");
        // REQUISITO: Perde uma tropa se perder a batalha
        if (atacante->tropas > 1) {
            atacante->tropas--;
        }
        printf("%s agora tem %d tropas.\n", atacante->nome, atacante->tropas);
    }
};

// REQUISITO: Liberação de memória
void liberarMemoria(Territorio* mapa) {
    if (mapa != NULL) {
        free(mapa);
    }
};