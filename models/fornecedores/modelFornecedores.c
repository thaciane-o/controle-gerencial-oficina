#include "modelFornecedores.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void armazenarDadosFornecedoresModel(struct ListaFornecedores *lista) {
    FILE *dadosFornecedores;
    dadosFornecedores = fopen("DadosFornecedores.txt", "w");

    if (dadosFornecedores == NULL) {
        printf("Erro ao armazenar fornecedores!\n");
        exit(1);
    }

    for (int i = 0; i < lista->qtdFornecedores;i++) {
        fprintf(dadosFornecedores, "%d;%d;%s;%s;%s;%s;%s;%s;%s;%s",
            lista->listaFornecedores[i].id, lista->listaFornecedores[i].deletado,
            lista->listaFornecedores[i].nomeFantasia, lista->listaFornecedores[i].razaoSocial,
            lista->listaFornecedores[i].inscricaoEstadual, lista->listaFornecedores[i].cnpj,
            lista->listaFornecedores[i].endereco, lista->listaFornecedores[i].ddd,
            lista->listaFornecedores[i].telefone, lista->listaFornecedores[i].email);
    }

    fclose(dadosFornecedores);
    free(lista->listaFornecedores);
}

void buscarDadosFornecedoresModel(struct ListaFornecedores *lista) {
    int i = 0;
    char linha[sizeof(struct Fornecedores)];

    FILE *dadosFornecedores;
    dadosFornecedores = fopen("DadosFornecedores.txt", "r");

    if (dadosFornecedores == NULL) {
        printf("Nenhum fornecedor armazenado!\n");
        return;
    }


    while (fgets(linha, sizeof(linha), dadosFornecedores)) {
        lista->qtdFornecedores++;
    }

    lista->listaFornecedores = malloc(lista->qtdFornecedores * sizeof(struct Fornecedores));

    if (lista->listaFornecedores == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    fseek(dadosFornecedores, 0, SEEK_SET);

    while (fgets(linha, sizeof(linha), dadosFornecedores)) {

        char *token = strtok(linha, ";");

        if (token != NULL) {
            lista->listaFornecedores[i].deletado = atoi(token);
            token = strtok(NULL, ";");
        }
        if (token != NULL) {
            lista->listaFornecedores[i].id = atoi(token);
            token = strtok(NULL, ";");
        }
        if (token != NULL) {
            strcpy(lista->listaFornecedores[i].nomeFantasia, token);
            token = strtok(NULL, ";");
        }
        if (token != NULL) {
            strcpy(lista->listaFornecedores[i].razaoSocial, token);
            token = strtok(NULL, ";");
        }
        if (token != NULL) {
            strcpy(lista->listaFornecedores[i].inscricaoEstadual, token);
            token = strtok(NULL, ";");
        }
        if (token != NULL) {
            strcpy(lista->listaFornecedores[i].cnpj, token);
            token = strtok(NULL, ";");
        }
        if (token != NULL) {
            strcpy(lista->listaFornecedores[i].endereco, token);
            token = strtok(NULL, ";");
        }
        if (token != NULL) {
            strcpy(lista->listaFornecedores[i].ddd, token);
            token = strtok(NULL, ";");
        }
        if (token != NULL) {
            strcpy(lista->listaFornecedores[i].telefone, token);
            token = strtok(NULL, ";");
        }
        if (token != NULL) {
            strcpy(lista->listaFornecedores[i].email, token);
        }

        i++;
    }

    fclose(dadosFornecedores);
}

void alocarFornecedoresModel(struct ListaFornecedores *lista) {
    lista->listaFornecedores = malloc(sizeof(struct  Fornecedores));

    if (lista->listaFornecedores == NULL) {
        printf("Erro: Memória insuficiente!\n\n");
        exit(1);
    }
}

void realocarFornecedoresModel(struct ListaFornecedores *lista, int qtdAlocada) {
    if (qtdAlocada == 0) {
        printf("Nenhum registro salvo.\n\n");
        return;
    }

    lista->qtdFornecedores += qtdAlocada;

    if (lista->qtdFornecedores == 0) {
        free(lista->listaFornecedores);
    } else {
        lista->listaFornecedores = realloc(lista->listaFornecedores, lista->qtdFornecedores * sizeof(struct Fornecedores));

        if (lista->listaFornecedores == NULL) {
            printf("Erro: Memória insuficiente!\n\n");
            exit(1);
        }
    }
}

void cadastrarFornecedoresModel(struct ListaFornecedores *lista, struct Fornecedores *fornecedor) {
    if (lista->qtdFornecedores == 0) {
        lista->qtdFornecedores++;
        alocarFornecedoresModel(lista);
    } else {
        realocarFornecedoresModel(lista, 1);
    }

    lista->listaFornecedores[lista->qtdFornecedores-1] = *fornecedor;
    lista->listaFornecedores[lista->qtdFornecedores-1].deletado = 0;

    int temp = 0;
    for (int i = 0; i < lista->qtdFornecedores; i++) {
        if (lista->listaFornecedores[i].id > lista->listaFornecedores[i-1].id) {
            temp = lista->listaFornecedores[i].id;
        }
    }

    lista->listaFornecedores[lista->qtdFornecedores-1].id = temp+1;

    printf("Fornecedor cadastrada com sucesso!\n\n");
}

struct Fornecedores atualizarFornecedoresModel(struct ListaFornecedores *lista, int id, struct Fornecedores *fornecedor) {
    int encontrado = 0;
    if (lista->qtdFornecedores == 0) {
        printf("Nenhum fornecedor foi cadastrado!\n\n");
        return;
    }

    for (int i = 0; i < lista->qtdFornecedores; i++) {
        if (lista->listaFornecedores[i].id == id && lista->listaFornecedores[i].deletado == 0) {
            encontrado = 1;
            fornecedor->id = lista->listaFornecedores[i].id;
            fornecedor->deletado = lista->listaFornecedores[i].deletado;

            lista->listaFornecedores[i] = *fornecedor;
        }
    }

    if (!encontrado) {
        printf("Fornecedor não encontrado!\n\n");
    }
}

void listarTodosFornecedoresModel(struct ListaFornecedores *lista) {
    if (lista->qtdFornecedores > 0) {
        for (int i = 0; i < lista->qtdFornecedores; i++) {
            printf("ID: %d"
                   "\nNOME FANTASIA: %s"
                   "\nRAZÃO SOCIAL: %s"
                   "\nINSCRIÇÃO ESTADUAL: %s"
                   "\nCNPJ: %s"
                   "\nENDEREÇO COMPLETO: %s"
                   "\nTELEFONE: (%s)%s"
                   "\nEMAIL: %s"
                   "\nRELATÓRIO: %s\n\n",
                   lista->listaFornecedores[i].id, lista->listaFornecedores[i].nomeFantasia,
                   lista->listaFornecedores[i].inscricaoEstadual, lista->listaFornecedores[i].cnpj,
                   lista->listaFornecedores[i].endereco, lista->listaFornecedores[i].ddd,
                   lista->listaFornecedores[i].telefone, lista->listaFornecedores[i].email);
        }
    } else {
        printf("Nenhum fornecedor foi cadastrado!\n\n");
    }
}

void listarFornecedoresModel(struct ListaFornecedores *lista, int id) {
    int encontrado = 0;

    if (lista->qtdFornecedores == 0) {
        printf("Nenhum fornecedor foi cadastrado!\n\n");
        return;
    }

    for (int i = 0; i < lista->qtdFornecedores; i++) {
        if (lista->listaFornecedores[i].id == id) {
            encontrado = 1;

            printf("ID: %d"
                 "\nNOME FANTASIA: %s"
                 "\nRAZÃO SOCIAL: %s"
                 "\nINSCRIÇÃO ESTADUAL: %s"
                 "\nCNPJ: %s"
                 "\nENDEREÇO COMPLETO: %s"
                 "\nTELEFONE: (%s)%s"
                 "\nEMAIL: %s"
                 "\nRELATÓRIO: %s\n\n",
                 lista->listaFornecedores[i].id, lista->listaFornecedores->nomeFantasia,
                 lista->listaFornecedores[i].inscricaoEstadual, lista->listaFornecedores->cnpj,
                 lista->listaFornecedores[i].endereco, lista->listaFornecedores->ddd,
                 lista->listaFornecedores[i].telefone, lista->listaFornecedores->email);
            break;
        }
    }

    if (!encontrado) {
        printf("Fornecedor não encontrado!\n\n");
    }
}

void deletarFornecedoresModel(struct ListaFornecedores *lista, int id) {
    int encontrado = 0;

    if (lista->qtdFornecedores == 0) {
        printf("Nenhum fornecedor foi cadastrado!\n\n");
        return;
    }

    for (int i = 0; i < lista->qtdFornecedores; i++) {
        if (lista->listaFornecedores[i].id == id) {
            encontrado = 1;

            lista->listaFornecedores[i].deletado = 1;

            printf("Fornecedor deletado com sucesso!\n\n");

            break;
        }
    }

    if (!encontrado) {
        printf("Fornecedor não encontrado!\n\n");
    }
}