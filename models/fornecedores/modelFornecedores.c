#include "modelFornecedores.h"
#include <stdio.h>
#include <stdlib.h>

int gerarIdUnico() {
    static int id = 0;
    return ++id;
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
        lista->listaFornecedores[lista->qtdFornecedores-1] = *fornecedor;
    } else {
        realocarFornecedoresModel(lista, 1);
        lista->listaFornecedores[lista->qtdFornecedores-1] = *fornecedor;
    }

    printf("Fornecedor cadastrada com sucesso!\n\n");
}

struct Fornecedores atualizarFornecedosModel(struct ListaFornecedores *lista, int id) {
    int encontrado = 0;
    if (lista->qtdFornecedores == 0) {
        printf("Nenhum fornecedor foi cadastrado!\n\n");
        return;
    }

    for (int i = 0; i < lista->qtdFornecedores; i++) {
        if (lista->listaFornecedores[i].id == id) {
            encontrado = 1;

            return lista->listaFornecedores[i];
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

            for (int j = i; j < lista->qtdFornecedores; j++) {
                lista->listaFornecedores[j] = lista->listaFornecedores[j + 1];
            }
            lista->qtdFornecedores--;
            realocarFornecedoresModel(lista, -1);
            printf("Fornecedor deletado com sucesso!\n\n");

            break;
        }
    }

    if (!encontrado) {
        printf("Fornecedor não encontrado!\n\n");
    }
}