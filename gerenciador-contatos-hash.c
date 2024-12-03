#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define TABLE_SIZE 10 // Tamanho da tabela hash
#define MAX_NAME 50   // Tamanho máximo do nome

typedef struct Contato {
    char nome[MAX_NAME];
    char telefone[15];
    struct Contato *proximo; // Para lidar com colisões (encadeamento)
} Contato;

Contato *tabela[TABLE_SIZE]; // Tabela hash

// Função hash djb2 para maior eficiência
unsigned long hash(char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash % TABLE_SIZE;
}

// Função para validar o telefone
int validarTelefone(const char *telefone) {
    int countDigits = 0;
    for (int i = 0; telefone[i] != '\0'; i++) {
        if (isdigit(telefone[i])) {
            countDigits++;
        } else if (!isspace(telefone[i])) {
            return 0; // Apenas números e espaços são permitidos
        }
    }
    return (countDigits == 11); // Deve ter 11 dígitos numéricos (incluindo o DDD e o número completo)
}

// Função para formatar telefone para exibição (ex.: 41 98888 8899 -> (41) 98888-8899)
void formatarTelefone(const char *telefone, char *formatado) {
    int len = strlen(telefone);
    if (len >= 13) {
        sprintf(formatado, "(%c%c) %c%c%c%c%c-%c%c%c%c",
                telefone[0], telefone[1], // DDD
                telefone[3], telefone[4], telefone[5], telefone[6], telefone[7], // Prefixo
                telefone[9], telefone[10], telefone[11], telefone[12]); // Sufixo
    } else {
        strcpy(formatado, telefone);
    }
}

// Adicionar contato
void adicionarContato() {
    char nome[MAX_NAME], telefone[15];
    printf("Nome: ");
    scanf(" %[^\n]s", nome);

    do {
        printf("Telefone (exemplo: 41 98888 8899): ");
        scanf(" %[^\n]s", telefone);
        if (!validarTelefone(telefone)) {
            printf("Erro: Formato de telefone inválido! Tente novamente.\n");
        }
    } while (!validarTelefone(telefone));

    int indice = hash(nome);
    Contato *atual = tabela[indice];

    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            printf("Erro: Já existe um contato com o nome '%s'.\n", nome);
            return;
        }
        atual = atual->proximo;
    }

    Contato *novo = (Contato *)malloc(sizeof(Contato));
    if (!novo) {
        printf("Erro ao alocar memória.\n");
        return;
    }
    strcpy(novo->nome, nome);
    strcpy(novo->telefone, telefone);
    novo->proximo = tabela[indice];
    tabela[indice] = novo;

    printf("Contato adicionado com sucesso.\n");
}

// Buscar contato
void buscarContato() {
    char nome[MAX_NAME];
    printf("Nome: ");
    scanf(" %[^\n]s", nome);

    int indice = hash(nome);
    Contato *atual = tabela[indice];

    clock_t inicio = clock();

    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            clock_t fim = clock();
            double tempoBusca = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
            char telefoneFormatado[20];
            formatarTelefone(atual->telefone, telefoneFormatado);
            printf("Telefone de %s: %s (tempo de busca: %.2f ms)\n", nome, telefoneFormatado, tempoBusca);
            return;
        }
        atual = atual->proximo;
    }
    printf("Contato não encontrado.\n");
}

// Remover contato
void removerContato() {
    char nome[MAX_NAME];
    printf("Nome: ");
    scanf(" %[^\n]s", nome);

    int indice = hash(nome);
    Contato *atual = tabela[indice];
    Contato *anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            if (anterior == NULL) {
                tabela[indice] = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            printf("Contato removido com sucesso.\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Contato não encontrado.\n");
}

// Exibir todos os contatos
void exibirContatos() {
    printf("\n--- Lista de Contatos ---\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        Contato *atual = tabela[i];
        if (atual != NULL) {
            printf("Índice %d:\n", i);
            while (atual != NULL) {
                char telefoneFormatado[20];
                formatarTelefone(atual->telefone, telefoneFormatado);
                printf("  Nome: %s, Telefone: %s\n", atual->nome, telefoneFormatado);
                atual = atual->proximo;
            }
        }
    }
    printf("-------------------------\n");
}

int main() {
    int opcao;

    for (int i = 0; i < TABLE_SIZE; i++) {
        tabela[i] = NULL;
    }

    do {
        printf("\nEscolha uma opção:\n");
        printf("1 - Adicionar contato\n");
        printf("2 - Buscar contato por nome\n");
        printf("3 - Remover contato\n");
        printf("4 - Exibir todos os contatos\n");
        printf("0 - Sair\n");
        printf("Digite uma opção: ");

        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarContato();
                break;
            case 2:
                buscarContato();
                break;
            case 3:
                removerContato();
                break;
            case 4:
                exibirContatos();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
