#include "modelFuncionarios.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void armazenarDadosFuncionariosModel(struct ListaFuncionarios *lista, int opcaoArmazenamento) {
    FILE *dadosFuncionarios;

    switch (opcaoArmazenamento) {
        case 1:
            dadosFuncionarios = fopen("DadosFuncionarios.txt", "w");

            if (dadosFuncionarios == NULL) {
                printf("Erro ao armazenar funcionários!\n");
                exit(1);
            }

            for (int i = 0; i < lista->qtdFuncionarios;i++) {
                fprintf(dadosFuncionarios, "%d;%s;%s;%s;%.2f;%d\n",
                    lista->listaFuncionarios[i].id,
                    lista->listaFuncionarios[i].nome,
                    lista->listaFuncionarios[i].cpf,
                    lista->listaFuncionarios[i].cargo,
                    lista->listaFuncionarios[i].salario,
                    lista->listaFuncionarios[i].deletado);
            }

        break;
        case 2:
            dadosFuncionarios = fopen("DadosFuncionarios.bin", "wb");

            if (dadosFuncionarios == NULL) {
                printf("Erro ao armazenar funcionários!\n");
                exit(1);
            }

            for (int i = 0; i < lista->qtdFuncionarios;i++) {
                fwrite(&lista->listaFuncionarios[i], sizeof(struct Funcionarios), 1, dadosFuncionarios);
            }
        break;
    }

    fclose(dadosFuncionarios);
    free(lista->listaFuncionarios);
    lista->qtdFuncionarios = 0;
}

void buscarDadosFuncionariosModel(struct ListaFuncionarios *lista, int opcaoArmazenamento) {
    int i = 0;
    FILE *dadosFuncionarios;
    char linha[sizeof(struct Funcionarios)];

    switch(opcaoArmazenamento) {
        case 1:
            dadosFuncionarios = fopen("DadosFuncionarios.txt", "r");

            if (dadosFuncionarios == NULL) {
                printf("Nenhum funcionário armazenado!\n");
                return;
            }

            while (fgets(linha, sizeof(linha), dadosFuncionarios)) {
                lista->qtdFuncionarios++;
            }

            if (lista->qtdFuncionarios > 0) {
                lista->listaFuncionarios = malloc(lista->qtdFuncionarios * sizeof(struct Funcionarios));
            } else {
                return;
            }

            if (lista->listaFuncionarios == NULL) {
                printf("Erro ao alocar memória!\n");
                exit(1);
            }

            fseek(dadosFuncionarios, 0, SEEK_SET);

            while (fgets(linha, sizeof(linha), dadosFuncionarios)) {

            char *token = strtok(linha, ";");

            if (token != NULL) {
                lista->listaFuncionarios[i].id = atoi(token);
                token = strtok(NULL, ";");
            }
            if (token != NULL) {
                strcpy(lista->listaFuncionarios[i].nome, token);
                token = strtok(NULL, ";");
            }
            if (token != NULL) {
                strcpy(lista->listaFuncionarios[i].cpf, token);
                token = strtok(NULL, ";");
            }
            if (token != NULL) {
                strcpy(lista->listaFuncionarios[i].cargo, token);
                token = strtok(NULL, ";");
            }
            if (token != NULL) {
                lista->listaFuncionarios[i].salario = atof(token);
                token = strtok(NULL, ";");
            }
            if (token != NULL) {
                lista->listaFuncionarios[i].deletado = atoi(token);
            }

            i++;
        }
        break;
        case 2:
            dadosFuncionarios = fopen("DadosFuncionarios.bin", "rb");

            if (dadosFuncionarios == NULL) {
                printf("Nenhum funcionário armazenado!\n");
                return;
            }

            struct Funcionarios linhaFuncionario;

            while (fread(&linhaFuncionario, sizeof(linhaFuncionario), 1, dadosFuncionarios)) {
                lista->qtdFuncionarios++;
            }

            lista->listaFuncionarios = malloc(lista->qtdFuncionarios * sizeof(struct Funcionarios));
            if (lista->listaFuncionarios == NULL) {
                printf("Erro ao alocar memoria!\n");
                exit(1);
            }

            fseek(dadosFuncionarios, 0, SEEK_SET);

            while (fread(&linhaFuncionario, sizeof(linhaFuncionario), 1, dadosFuncionarios)) {
                lista->listaFuncionarios[i] = linhaFuncionario;
                i++;
            }
        break;
    }

    fclose(dadosFuncionarios);
}

void alocarFuncionariosModel(struct ListaFuncionarios *lista) {
    lista->qtdFuncionarios = 1;
    lista->listaFuncionarios = malloc(sizeof(struct  Funcionarios));

    if (lista->listaFuncionarios == NULL) {
        printf("Erro: Memória insuficiente!\n\n");
        exit(1);
    }
}

void realocarFuncionariosModel(struct ListaFuncionarios *lista, int qtdAlocada) {
    if (qtdAlocada == 0) {
        printf("Nenhum registro salvo.\n\n");
        return;
    }

    lista->qtdFuncionarios += qtdAlocada;
    lista->listaFuncionarios = realloc(lista->listaFuncionarios, lista->qtdFuncionarios * sizeof(struct Funcionarios));

    if (lista->listaFuncionarios == NULL) {
        printf("Erro: Memória insuficiente!\n\n");
        exit(1);
    }
}

void cadastrarFuncionariosModel(struct ListaFuncionarios *lista, struct Funcionarios *funcionario) {
    if (lista->qtdFuncionarios == 0) {
        lista->qtdFuncionarios++;
        alocarFuncionariosModel(lista);
    } else {
        realocarFuncionariosModel(lista, 1);
    }

    funcionario->id = lista->qtdFuncionarios;
    funcionario->deletado = 0;


    lista->listaFuncionarios[lista->qtdFuncionarios-1] = *funcionario;

    printf("Funcionário cadastrado com sucesso!\n\n");
}

int verificarIDFuncionariosModel(struct ListaFuncionarios *lista, int id) {
    if (lista->qtdFuncionarios > 0) {
        for (int i = 0; i < lista->qtdFuncionarios; i++) {
            if (lista->listaFuncionarios[i].id == id && lista->listaFuncionarios[i].deletado == 0) {
                return 1;
            }
        }
    } else {
        printf("Nenhuma funcionário foi cadastrado!\n\n");
        return 0;
    }

    printf("Funcionário não encontrado.\n\n");
    return 0;
}

void atualizarFuncionariosModel(struct ListaFuncionarios *lista, int id, struct Funcionarios *funcionario) {
    int encontrado = 0;

    if (lista->qtdFuncionarios == 0) {
        printf("Nenhum funcionário foi cadastrado!\n\n");
        return;
    }

    for (int i = 0; i < lista->qtdFuncionarios; i++) {
        if (lista->listaFuncionarios[i].id == id && lista->listaFuncionarios[i].deletado == 0) {
            encontrado = 1;
            lista->listaFuncionarios[i] = *funcionario;
            lista->listaFuncionarios[i].id = id;
            lista->listaFuncionarios[i].deletado = 0;

            break;
        }
    }

    if (!encontrado) {
        printf("Funcionário não encontrado!\n\n");
    }
}

void listarTodosFuncionariosModel(struct ListaFuncionarios *lista) {
    if (lista->qtdFuncionarios > 0) {
        for (int i = 0; i < lista->qtdFuncionarios; i++) {
            if (lista->listaFuncionarios[i].deletado == 0) {
                printf("ID: %d"
                       "\nNOME: %s"
                       "\nCPF: %s"
                       "\nCARGO: %s"
                       "\nSALÁRIO: %.2f\n\n",
                       lista->listaFuncionarios[i].id,
                       lista->listaFuncionarios[i].nome,
                       lista->listaFuncionarios[i].cpf,
                       lista->listaFuncionarios[i].cargo,
                       lista->listaFuncionarios[i].salario);
            }
        }
    } else {
        printf("Nenhum funcionário foi cadastrado!\n\n");
    }
}

void listarFuncionariosModel(struct ListaFuncionarios *lista, int id) {
    int encontrado = 0;

    if (lista->qtdFuncionarios == 0) {
        printf("Nenhum funcionário foi cadastrado!\n\n");
        return;
    }

    for (int i = 0; i < lista->qtdFuncionarios; i++) {
        if (lista->listaFuncionarios[i].id == id && lista->listaFuncionarios[i].deletado == 0) {
            encontrado = 1;
            if (lista->listaFuncionarios[i].deletado == 0) {
                printf("ID: %d"
                       "\nNOME: %s"
                       "\nCPF: %s"
                       "\nCARGO: %s"
                       "\nSALÁRIO: %.2f\n\n",
                       lista->listaFuncionarios[i].id,
                       lista->listaFuncionarios[i].nome,
                       lista->listaFuncionarios[i].cpf,
                       lista->listaFuncionarios[i].cargo,
                       lista->listaFuncionarios[i].salario);
                break;
            }
        }
    }

    if (!encontrado) {
        printf("Funcionário não encontrado!\n\n");
    }
}

void deletarFuncionariosModel(struct ListaFuncionarios *lista, int id) {
    int encontrado = 0;

    if (lista->qtdFuncionarios == 0) {
        printf("Nenhum funcionário foi cadastrado!\n\n");
        return;
    }

    for (int i = 0; i < lista->qtdFuncionarios; i++) {
        if (lista->listaFuncionarios[i].id == id && lista->listaFuncionarios[i].deletado == 0) {
            encontrado = 1;
            lista->listaFuncionarios[i].deletado = 1;
            printf("Funcionário deletado com sucesso!\n\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Funcionário não encontrado!\n\n");
    }
}