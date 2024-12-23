#include "modelAgendamentos.h"
#include "../../models/veiculos/modelVeiculos.h"
#include "../../models/funcionarios/modelFuncionarios.h"
#include "../../models/servicos/modelServicos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Busca os dados de agendamentos nos arquivos
void buscarDadosAgendamentosModel(struct ListaAgendamentos *lista, int opcaoArmazenamento) {
    int i = 0;

    FILE *dadosAgendamentos;

    switch (opcaoArmazenamento) {
        case 1:
            dadosAgendamentos = fopen("DadosAgendamentos.txt", "r");

            if (dadosAgendamentos == NULL) {
                return;
            }

            char linha[sizeof(struct Agendamentos)];

            while (fgets(linha, sizeof(linha), dadosAgendamentos)) {
                lista->qtdAgendamentos++;
            }

            if (lista->qtdAgendamentos > 0) {
                lista->listaAgendamentos = malloc(lista->qtdAgendamentos * sizeof(struct Agendamentos));
            } else {
                return;
            }

            if (lista->listaAgendamentos == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                return;
            }

            fseek(dadosAgendamentos, 0, SEEK_SET);

            while (fgets(linha, sizeof(linha), dadosAgendamentos)) {
                char *token = strtok(linha, ";");

                if (token != NULL) {
                    lista->listaAgendamentos[i].id = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaAgendamentos[i].data, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaAgendamentos[i].hora, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaAgendamentos[i].idFuncionario = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaAgendamentos[i].idServico = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaAgendamentos[i].idVeiculo = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaAgendamentos[i].deletado = atoi(token);
                }

                i++;
            }
            break;
        case 2:
            dadosAgendamentos = fopen("DadosAgendamentos.bin", "rb");

            if (dadosAgendamentos == NULL) {
                return;
            }

            struct Agendamentos linhaAgendamento;

            while (fread(&linhaAgendamento, sizeof(linhaAgendamento), 1, dadosAgendamentos)) {
                lista->qtdAgendamentos++;
            }

            if (lista->qtdAgendamentos > 0) {
                lista->listaAgendamentos = malloc(lista->qtdAgendamentos * sizeof(struct Agendamentos));
            } else {
                return;
            }

            if (lista->listaAgendamentos == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                return;
            }

            fseek(dadosAgendamentos, 0, SEEK_SET);

            while (fread(&linhaAgendamento, sizeof(linhaAgendamento), 1, dadosAgendamentos)) {
                lista->listaAgendamentos[i] = linhaAgendamento;
                i++;
            }

            break;
    }
    fclose(dadosAgendamentos);
}

// Armazena os dados de agendamentos nos arquivos
void armazenarDadosAgendamentosModel(struct ListaAgendamentos *lista, int opcaoArmazenamento) {
    //Abrindo ou criando arquivo para adicionar cadastros
    FILE *dadosAgendamentos;

    switch (opcaoArmazenamento) {
        case 1:
            dadosAgendamentos = fopen("DadosAgendamentos.txt", "w");

        if (dadosAgendamentos == NULL) {
            printf("Erro: Não foi possível abrir o arquivo de texto.\n\n");
            return;
        }

        for (int i = 0; i < lista->qtdAgendamentos; i++) {
            fprintf(dadosAgendamentos, "%d;%s;%s;%s;%s;%s;%s;%d;%d\n",
                    lista->listaAgendamentos[i].id,
                    lista->listaAgendamentos[i].data,
                    lista->listaAgendamentos[i].hora,
                    lista->listaAgendamentos[i].idFuncionario,
                    lista->listaAgendamentos[i].idServico,
                    lista->listaAgendamentos[i].idVeiculo,
                    lista->listaAgendamentos[i].deletado);
        }
        break;
        case 2:
            dadosAgendamentos = fopen("DadosAgendamentos.bin", "wb");

        if (dadosAgendamentos == NULL) {
            printf("Erro: Não foi possível abrir o arquivo binário.\n\n");
            return;
        }

        for (int i = 0; i < lista->qtdAgendamentos; i++) {
            fwrite(&lista->listaAgendamentos[i], sizeof(struct Agendamentos), 1, dadosAgendamentos);
        }
        break;
    }
    fclose(dadosAgendamentos);

    free(lista->listaAgendamentos);
    lista->listaAgendamentos = NULL;

    lista->qtdAgendamentos = 0;
}

// Aloca memória inicial na lista de agendamentos
int alocarAgendamentosModel(struct ListaAgendamentos *lista) {
    lista->qtdAgendamentos = 1;
    lista->listaAgendamentos = malloc(sizeof(struct Agendamentos));

    if (lista->listaAgendamentos == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

// Realoca memória na lista de agendamentos conforme a necessidade em qtdAlocada
int realocarAgendamentosModel(struct ListaAgendamentos *lista, int qtdAlocada) {
    if (qtdAlocada == 0) {
        printf("Nenhum registro salvo.\n\n");
        return 0;
    }

    lista->qtdAgendamentos += qtdAlocada;
    lista->listaAgendamentos = realloc(lista->listaAgendamentos, lista->qtdAgendamentos * sizeof(struct Agendamentos));

    if (lista->listaAgendamentos == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

// Cadastra um novo agendamento
void cadastrarAgendamentosModel(struct ListaAgendamentos *lista, struct Agendamentos *agendamento) {
    int resultAlocacao = 0;

    if (lista->qtdAgendamentos == 0) {
        lista->qtdAgendamentos++;
        resultAlocacao = alocarAgendamentosModel(lista);
    } else {
        resultAlocacao = realocarAgendamentosModel(lista, 1);
    }

    if (resultAlocacao == 0) {
        printf("Erro: Não foi possível realizar o Agendamento.\n\n");
        return;
    }

    //Cadastrando cliente na memória
    agendamento->id = lista->qtdAgendamentos;
    agendamento->deletado = 0;

    lista->listaAgendamentos[lista->qtdAgendamentos - 1] = *agendamento;

    printf("Agendamento realizado com sucesso!\n\n");
}