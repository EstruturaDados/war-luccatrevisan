//codespaces > alterações > confirmar

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_STRING 100
#define NUM_MISSOES 5

// Estrutura do Território
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
void atribuirMissao(char* destino, const char* missoes[], int total);
int verificarMissao(char* missao, Territorio* mapa, int quantidade, char* corJogador);
void liberarTudo(Territorio* mapa, char* missao);

int main() {
    srand(time(NULL));

    // 1. Definição das Missões (Vetor de Strings)
    const char* listaMissoes[NUM_MISSOES] = {
        "Conquistar 2 territorios",
        "Conquistar 3 territorios",
        "Dominar o mapa (4 territorios)",
        "Eliminar tropas inimigas",
        "Expandir exercito para 5 territorios"
    };

    int numTerritorios;
    printf("--- WAR: DESAFIO FINAL ---\n");
    printf("Quantos territorios teremos no jogo? ");
    scanf("%d", &numTerritorios);
    limparBuffer();

    // 2. Alocação Dinâmica
    Territorio* mapa = (Territorio*)calloc(numTerritorios, sizeof(Territorio));
    char* missaoJogador = (char*)malloc(TAM_STRING * sizeof(char));

    if (mapa == NULL || missaoJogador == NULL) {
        printf("Erro de alocacao.\n");
        return 1;
    }

    // 3. Setup Inicial
    cadastrarTerritorios(mapa, numTerritorios);
    
    char corDoJogador[10];
    printf("\nQual a SUA cor de exercito? ");
    fgets(corDoJogador, 10, stdin);
    corDoJogador[strcspn(corDoJogador, "\n")] = '\0';

    // REQUISITO: Atribuição de missão por referência
    atribuirMissao(missaoJogador, listaMissoes, NUM_MISSOES);
    printf("\n[CONFIDENCIAL] Sua missao sorteada: %s\n", missaoJogador);

    int opcao;
    int vitoria = 0;

    // 4. Loop Principal de Jogo
    do {
        printf("\n--- TURNO DE GUERRA ---\n");
        printf("1 - Atacar\n2 - Ver Mapa\n0 - Desistir\nEscolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        if (opcao == 1) {
            int atq, def;
            listarTerritorios(mapa, numTerritorios);
            printf("Atacante (ID): "); scanf("%d", &atq);
            printf("Defensor (ID): "); scanf("%d", &def);
            limparBuffer();

            atq--; def--; // Ajuste de índice

            if (atq >= 0 && def >= 0 && atq < numTerritorios && def < numTerritorios) {
                // Validação: Atacar apenas inimigos
                if (strcmp(mapa[atq].cor, mapa[def].cor) != 0) {
                    atacar(&mapa[atq], &mapa[def]);
                } else {
                    printf("Voce nao pode atacar a si mesmo!\n");
                }
            }
        } else if (opcao == 2) {
            listarTerritorios(mapa, numTerritorios);
        }

        // REQUISITO: Verificação silenciosa de vitória após cada turno
        vitoria = verificarMissao(missaoJogador, mapa, numTerritorios, corDoJogador);

        if (vitoria) {
            printf("\n************************************\n");
            printf("   VITORIA! MISSAO CUMPRIDA: \n   %s\n", missaoJogador);
            printf("************************************\n");
            listarTerritorios(mapa, numTerritorios);
            break;
        }

    } while (opcao != 0);

    // 5. REQUISITO: Limpeza total
    liberarTudo(mapa, missaoJogador);
    return 0;
}

// --- IMPLEMENTAÇÃO DAS REGRAS ---

void atribuirMissao(char* destino, const char* missoes[], int total) {
    int sorteio = rand() % total;
    // REQUISITO: Passagem por referência usando strcpy
    strcpy(destino, missoes[sorteio]);
}

void atacar(Territorio* atacante, Territorio* defensor) {
    int dAtq = (rand() % 6) + 1;
    int dDef = (rand() % 6) + 1;

    printf("\nDados -> Atq: %d | Def: %d\n", dAtq, dDef);

    if (dAtq > dDef) {
        printf("Sucesso! %s agora e de %s.\n", defensor->nome, atacante->cor);
        strcpy(defensor->cor, atacante->cor);
        int transferencia = atacante->tropas / 2;
        defensor->tropas = transferencia;
        atacante->tropas -= transferencia;
    } else {
        printf("Falha no ataque! O defensor resistiu.\n");
        if (atacante->tropas > 1) atacante->tropas--;
    }
}

int verificarMissao(char* missao, Territorio* mapa, int tamanho, char* corJogador) {
    int contagem = 0;
    for (int i = 0; i < tamanho; i++) {
        if (strcmp(mapa[i].cor, corJogador) == 0) {
            contagem++;
        }
    }

    // Lógica simplificada de vitória baseada na string sorteada
    if (strstr(missao, "2 territorios") && contagem >= 2) return 1;
    if (strstr(missao, "3 territorios") && contagem >= 3) return 1;
    if (strstr(missao, "4 territorios") && contagem >= 4) return 1;
    if (strstr(missao, "5 territorios") && contagem >= 5) return 1;
    if (strstr(missao, "Eliminar") && contagem == tamanho) return 1;

    return 0;
}

void cadastrarTerritorios(Territorio* mapa, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("Nome do Territorio %d: ", i + 1);
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';
        printf("Cor do Exercito: ");
        fgets(mapa[i].cor, 10, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';
        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
        limparBuffer();
    }
}

void listarTerritorios(Territorio* mapa, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("[%d] %s (%s) - Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void liberarTudo(Territorio* mapa, char* missao) {
    free(mapa);
    free(missao);
}