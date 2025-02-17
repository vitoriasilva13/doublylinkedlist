#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pessoa {
    char nome[51];
    char sexo;
    double salario;
};

struct Node {
    Pessoa pessoa;
    Node* next;
    Node* prev;
};

//Declarando funções
Node* carregaNodes();
Node* criaNode(Pessoa pessoa);
void insereInicio(Node** head, Pessoa pessoa);
void insereFinal(Node** head, Pessoa pessoa);
void insereOrdenandoAlfabeticamente(Node** head, Pessoa pessoa);
void imprime(Node* head);
void imprimeInverso(Node* head);
void estilizaFormatoParaImpressao(Pessoa pessoa);
void trim(char *str);

int main() {
    Node* head = carregaNodes();
    int acao;
    do {
        printf("\n****************************************\n"
               "1 - Mostrar dados em ordem crescente\n"
               "2 - Mostrar dados em ordem decrescente\n"
               "O - Sair\n\n");
        printf("Informe uma opcao: ");
        scanf("%d", &acao);

        switch (acao) {
            case 1:
                imprime(head);
                break;
            case 2:
                imprimeInverso(head);
                break;
            case 0:
                break;
            default:
                printf("Informe uma opcao valida!\n");
                break;
        }
    } while (acao != 0);

    return 0;
}

Node* carregaNodes() {
    Node* head = NULL;

    FILE *file = fopen("entrada", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo\n");
    }

    char registro[200];
    while (fgets(registro, sizeof(registro), file)) {
        Pessoa pessoa = {};
        sscanf(registro, "%50[^\n] %c%lf", pessoa.nome, &pessoa.sexo, &pessoa.salario);
        trim(pessoa.nome);
        insereOrdenandoAlfabeticamente(&head, pessoa);
    }

    fclose(file);
    return head;
}

Node* criaNode(Pessoa pessoa) {
    Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->pessoa = pessoa;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void insereOrdenandoAlfabeticamente(Node** head, Pessoa pessoa) {
    Node* novo = criaNode(pessoa);
    if (*head == NULL) {
        *head = novo;
        return;
    }

    Node* atual = *head;
    if (strcmp(pessoa.nome, atual->pessoa.nome) < 0) {
        novo->next = atual;
        atual->prev = novo;
        *head = novo;
        return;
    }

    while (atual->next != NULL && strcmp(pessoa.nome, atual->next->pessoa.nome) > 0) {
        atual = atual->next;
    }

    novo->next = atual->next;
    novo->prev = atual;
    if (atual->next != NULL) {
        atual->next->prev = novo;
    }
    atual->next = novo;
}

void imprime(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        estilizaFormatoParaImpressao(temp->pessoa);
        temp = temp->next;
    }
}

void imprimeInverso(Node* head) {
    if (head == NULL) return;

    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    while (temp != NULL) {
        estilizaFormatoParaImpressao(temp->pessoa);
        temp = temp->prev;
    }
}

void insereInicio(Node** head, Pessoa pessoa) {
    Node* novo = criaNode(pessoa);
    if (*head != NULL) {
        novo->next = *head;
        (*head)->prev = novo;
    }
    *head = novo;
}

void insereFinal(Node** head, Pessoa pessoa) {
    Node* novo = criaNode(pessoa);
    if (*head == NULL) {
        *head = novo;
        return;
    }

    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = novo;
    novo->prev = temp;
}

void trim(char *str) {
    for (int i = strlen(str) - 1; i >= 0 && str[i] == ' '; i--)
        str[i] = '\0';
}

void estilizaFormatoParaImpressao(Pessoa pessoa) {
    printf("-------------------------------------------------------------\n");
    printf("Nome: %s\n", pessoa.nome);
    printf("Sexo: %c\n", pessoa.sexo);
    printf("Salario: %.2f\n", pessoa.salario);
}