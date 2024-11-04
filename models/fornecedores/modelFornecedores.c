#include "modelFornecedores.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void armazenarDadosFornecedoresModel(struct ListaFornecedores *lista, int opcaoArmazenamento) {
    FILE *dadosFornecedores;

    switch(opcaoArmazenamento) {
        case 1:
            dadosFornecedores = fopen("DadosFornecedores.txt", "w");

            if (dadosFornecedores == NULL) {
                printf("Erro ao armazenar fornecedores!\n");
                exit(1);
            }

            for (int i = 0; i < lista->qtdFornecedores;i++) {
                fprintf(dadosFornecedores, "%d;%s;%s;%s;%s;%s;%s;%s;%s;%d\n",
                    lista->listaFornecedores[i].id,
                    lista->listaFornecedores[i].nomeFantasia,
                    lista->listaFornecedores[i].razaoSocial,
                    lista->listaFornecedores[i].inscricaoEstadual,
                    lista->listaFornecedores[i].cnpj,
                    lista->listaFornecedores[i].endereco,
                    lista->listaFornecedores[i].ddd,
                    lista->listaFornecedores[i].telefone,
                    lista->listaFornecedores[i].email,
                    lista->listaFornecedores[i].deletado);
            }

        break;
        case 2:
            dadosFornecedores = fopen("DadosFornecedores.bin", "wb");

            if (dadosFornecedores == NULL) {
                printf("Erro ao armazenar fornecedores!\n");
                exit(1);
            }

            for (int i = 0; i < lista->qtdFornecedores;i++) {
                fwrite(&lista->listaFornecedores[i], sizeof(struct Fornecedores), 1, dadosFornecedores);
            }
        break;
    }

    fclose(dadosFornecedores);
    free(lista->listaFornecedores);
    lista->qtdFornecedores = 0;
}

void buscarDadosFornecedoresModel(struct ListaFornecedores *lista, int opcaoArmazenamento) {
    int i = 0;
    FILE *dadosFornecedores;
    char linha[sizeof(struct Fornecedores)];

    switch(opcaoArmazenamento) {
        case 1:
            dadosFornecedores = fopen("DadosFornecedores.txt", "r");

            if (dadosFornecedores == NULL) {
                printf("Nenhum fornecedor armazenado!\n");
                return;
            }

            while (fgets(linha, sizeof(linha), dadosFornecedores)) {
                lista->qtdFornecedores++;
            }

            if (lista->qtdFornecedores > 0) {
                lista->listaFornecedores = malloc(lista->qtdFornecedores * sizeof(struct Fornecedores));
            } else {
                return;
            }

            if (lista->listaFornecedores == NULL) {
                printf("Erro ao alocar memória!\n");
                exit(1);
            }

            fseek(dadosFornecedores, 0, SEEK_SET);

            while (fgets(linha, sizeof(linha), dadosFornecedores)) {

            char *token = strtok(linha, ";");

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
                token = strtok(NULL, ";");
            }
            if (token != NULL) {
                lista->listaFornecedores[i].deletado = atoi(token);
            }

            i++;
        }
        break;
        case 2:
            dadosFornecedores = fopen("DadosFornecedores.bin", "rb");

            if (dadosFornecedores == NULL) {
                printf("Nenhum fornecedor armazenado!\n");
                return;
            }

            struct Fornecedores linhaFornecedor;

            while (fread(&linhaFornecedor, sizeof(linhaFornecedor), 1, dadosFornecedores)) {
                lista->qtdFornecedores++;
            }

            lista->listaFornecedores = malloc(lista->qtdFornecedores * sizeof(struct Fornecedores));
            if (lista->listaFornecedores == NULL) {
                printf("Erro ao alocar memoria!\n");
                exit(1);
            }

            fseek(dadosFornecedores, 0, SEEK_SET);

            while (fread(&linhaFornecedor, sizeof(linhaFornecedor), 1, dadosFornecedores)) {
                lista->listaFornecedores[i] = linhaFornecedor;
                i++;
            }
        break;
    }

    fclose(dadosFornecedores);
}

void alocarFornecedoresModel(struct ListaFornecedores *lista) {
    lista->qtdFornecedores = 1;
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
    lista->listaFornecedores = realloc(lista->listaFornecedores, lista->qtdFornecedores * sizeof(struct Fornecedores));

    if (lista->listaFornecedores == NULL) {
        printf("Erro: Memória insuficiente!\n\n");
        exit(1);
    }
}

void cadastrarFornecedoresModel(struct ListaFornecedores *lista, struct Fornecedores *fornecedor) {
    if (lista->qtdFornecedores == 0) {
        lista->qtdFornecedores++;
        alocarFornecedoresModel(lista);
    } else {
        realocarFornecedoresModel(lista, 1);
    }

    fornecedor->id = lista->qtdFornecedores;
    fornecedor->deletado = 0;


    lista->listaFornecedores[lista->qtdFornecedores-1] = *fornecedor;

    printf("Fornecedor cadastrado com sucesso!\n\n");
}

int verificarIDFornecedoresModel(struct ListaFornecedores *lista, int id) {
    if (lista->qtdFornecedores > 0) {
        for (int i = 0; i < lista->qtdFornecedores; i++) {
            if (lista->listaFornecedores[i].id == id && lista->listaFornecedores[i].deletado == 0) {
                return 1;
            }
        }
    } else {
        printf("Nenhuma fornecedor foi cadastrado!\n\n");
        return 0;
    }

    printf("Fornecedor não encontrado.\n\n");
    return 0;
}

void atualizarFornecedoresModel(struct ListaFornecedores *lista, int id, struct Fornecedores *fornecedor) {
    int encontrado = 0;

    if (lista->qtdFornecedores == 0) {
        printf("Nenhum fornecedor foi cadastrado!\n\n");
        return;
    }

    for (int i = 0; i < lista->qtdFornecedores; i++) {
        if (lista->listaFornecedores[i].id == id && lista->listaFornecedores[i].deletado == 0) {
            encontrado = 1;
            lista->listaFornecedores[i] = *fornecedor;
            lista->listaFornecedores[i].id = id;
            lista->listaFornecedores[i].deletado = 0;

            break;
        }
    }

    if (!encontrado) {
        printf("Fornecedor não encontrado!\n\n");
    }
}

void listarTodosFornecedoresModel(struct ListaFornecedores *lista) {
    if (lista->qtdFornecedores > 0) {
        for (int i = 0; i < lista->qtdFornecedores; i++) {
            if (lista->listaFornecedores[i].deletado == 0) {
                printf("ID: %d"
                       "\nNOME FANTASIA: %s"
                       "\nRAZÃO SOCIAL: %s"
                       "\nINSCRIÇÃO ESTADUAL: %s"
                       "\nCNPJ: %s"
                       "\nENDEREÇO COMPLETO: %s"
                       "\nTELEFONE: (%s)%s"
                       "\nEMAIL: %s\n\n",
                       lista->listaFornecedores[i].id,
                       lista->listaFornecedores[i].nomeFantasia,
                       lista->listaFornecedores[i].razaoSocial,
                       lista->listaFornecedores[i].inscricaoEstadual,
                       lista->listaFornecedores[i].cnpj,
                       lista->listaFornecedores[i].endereco,
                       lista->listaFornecedores[i].ddd,
                       lista->listaFornecedores[i].telefone,
                       lista->listaFornecedores[i].email);
            }
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
        if (lista->listaFornecedores[i].id == id && lista->listaFornecedores[i].deletado == 0) {
            encontrado = 1;
            if (lista->listaFornecedores[i].deletado == 0) {
                printf("ID: %d"
                     "\nNOME FANTASIA: %s"
                     "\nRAZÃO SOCIAL: %s"
                     "\nINSCRIÇÃO ESTADUAL: %s"
                     "\nCNPJ: %s"
                     "\nENDEREÇO COMPLETO: %s"
                     "\nTELEFONE: (%s)%s"
                     "\nEMAIL: %s\n\n",
                     lista->listaFornecedores[i].id,
                     lista->listaFornecedores[i].nomeFantasia,
                     lista->listaFornecedores[i].razaoSocial,
                     lista->listaFornecedores[i].inscricaoEstadual,
                     lista->listaFornecedores[i].cnpj,
                     lista->listaFornecedores[i].endereco,
                     lista->listaFornecedores[i].ddd,
                     lista->listaFornecedores[i].telefone,
                     lista->listaFornecedores[i].email);
                break;
            }
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
        if (lista->listaFornecedores[i].id == id && lista->listaFornecedores[i].deletado == 0) {
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