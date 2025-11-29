#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//estrutura para um cômodo (nó da árvore)
typedef struct Comodo {
    char nome[50];
    struct Comodo *esquerda; 
    struct Comodo *direita;  
} Comodo;

//Cria dinamicamente um novo cômodo (sala) com o nome especificado.
Comodo* criarSala(const char* nome) {
    Comodo* novoComodo = (Comodo*)malloc(sizeof(Comodo));
    if (novoComodo == NULL) {
        printf("Erro na alocacao de memoria!\n");
        exit(1);
    }
    strncpy(novoComodo->nome, nome, sizeof(novoComodo->nome) - 1);
    novoComodo->nome[sizeof(novoComodo->nome) - 1] = '\0';
    novoComodo->esquerda = NULL;
    novoComodo->direita = NULL;
    return novoComodo;
}

//Função para Explorar os comodos da mansão
void explorarSalas(Comodo* comodoInicial) {
    Comodo* atual = comodoInicial;
    char escolha;

    printf("Iniciando exploracao da mansao. Bem-vindo!\n");
    printf("Voce pode escolher 'e' (esquerda), 'd' (direita) ou 's' (sair).\n\n");

    while (atual != NULL) {
        printf("Voce esta em: %s\n", atual->nome);

        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Voce alcancou um comodo sem saidas adicionais (um no-folha). Fim da exploracao.\n");
            break; 
        }
        // Menu de opções
        printf("Opcoes de caminho: ");
        if (atual->esquerda != NULL) printf("e (esquerda) ");
        if (atual->direita != NULL) printf("d (direita) ");
        printf("ou s (sair): ");
    
        while ((getchar()) != '\n'); 
        scanf(" %c", &escolha);

        if (escolha == 's' || escolha == 'S') {
            printf("Saindo da exploracao.\n");
            break;
        } else if ((escolha == 'e' || escolha == 'E') && atual->esquerda != NULL) {
            atual = atual->esquerda;
        } else if ((escolha == 'd' || escolha == 'D') && atual->direita != NULL) {
            atual = atual->direita;
        } else {
            printf("Escolha invalida ou caminho inexistente. Tente novamente.\n");
        }
        printf("\n");
    }
}

//Libera a memória alocada para a árvore
void liberarMemoria(Comodo* comodo) {
    if (comodo == NULL) return;
    liberarMemoria(comodo->esquerda);
    liberarMemoria(comodo->direita);
    free(comodo);
}

//Funcao principal que monta o mapa inicial da mansao e inicia a exploracao.
int main() {
    //raíz da mansão (entrada)
    Comodo* raiz = criarSala("Entrada Principal");
    
    // Nível 1
    raiz->esquerda = criarSala("Sala de Estar");
    raiz->direita = criarSala("Cozinha");
    
    // Nível 2 (Filhos da Sala de Estar)
    raiz->esquerda->esquerda = criarSala("Quarto Principal");
    raiz->esquerda->direita = criarSala("Banheiro Social");
    
    // Nível 2 (Filhos da Cozinha)
    raiz->direita->direita = criarSala("Jardim de Inverno");
    
    // Nível 3 (Filhos do Quarto Principal) - Nó folha esperado
    raiz->esquerda->esquerda->esquerda = criarSala("Closet"); 
    
    // 2. Iniciar a navegação
    explorarSalas(raiz);

    // 3. Limpeza de memória
    liberarMemoria(raiz);

    return 0;
}