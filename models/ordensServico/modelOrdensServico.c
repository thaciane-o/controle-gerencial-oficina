#include "modelOrdensServico.h"
#include "../../models/pecas/modelPecas.h"
#include "../../models/agendamentos/modelAgendamentos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Busca os dados de ordens de serviço nos arquivos
void buscarDadosOrdensServicoModel(struct ListaOrdensServico *lista, int opcaoArmazenamento) {
    int i = 0;

    FILE *dadosOrdensServico;

    switch (opcaoArmazenamento) {
        case 1:
            dadosOrdensServico = fopen("DadosOrdensServiço.txt", "r");

            if (dadosOrdensServico == NULL) {
                return;
            }

            char linha[sizeof(struct OrdensServico)];

            while (fgets(linha, sizeof(linha), dadosOrdensServico)) {
                lista->qtdOrdensServico++;
            }

            if (lista->qtdOrdensServico > 0) {
                lista->listaOrdensServico = malloc(lista->qtdOrdensServico * sizeof(struct OrdensServico));
            } else {
                return;
            }

            if (lista->listaOrdensServico == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                return;
            }

            fseek(dadosOrdensServico, 0, SEEK_SET);

            while (fgets(linha, sizeof(linha), dadosOrdensServico)) {
                char *token = strtok(linha, ";");

                if (token != NULL) {
                    strcpy(lista->listaOrdensServico[i].descricao, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaOrdensServico[i].idAgendamentos = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaOrdensServico[i].idPecas = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaOrdensServico[i].valorTotal = atof(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaOrdensServico[i].deletado = atoi(token);
                }

                i++;
            }
            break;
        case 2:
            dadosOrdensServico = fopen("DadosOrdensServico.bin", "rb");

            if (dadosOrdensServico == NULL) {
                return;
            }

            struct OrdensServico linhaOrdensServico;

            while (fread(&linhaOrdensServico, sizeof(linhaOrdensServico), 1, dadosOrdensServico)) {
                lista->qtdOrdensServico++;
            }

            if (lista->qtdOrdensServico > 0) {
                lista->listaOrdensServico = malloc(lista->qtdOrdensServico * sizeof(struct OrdensServico));
            } else {
                return;
            }

            if (lista->listaOrdensServico == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                return;
            }

            fseek(dadosOrdensServico, 0, SEEK_SET);

            while (fread(&linhaOrdensServico, sizeof(linhaOrdensServico), 1, dadosOrdensServico)) {
                lista->listaOrdensServico[i] = linhaOrdensServico;
                i++;
            }

            break;
    }
    fclose(dadosOrdensServico);
}

// Armazena os dados de ordens de serviço nos arquivos
void armazenarDadosOrdensServicoModel(struct ListaOrdensServico *lista, int opcaoArmazenamento) {
    //Abrindo ou criando arquivo para adicionar cadastros
    FILE *dadosOrdensServico;

    switch (opcaoArmazenamento) {
        case 1:
            dadosOrdensServico = fopen("DadosOrdensServico.txt", "w");

        if (dadosOrdensServico == NULL) {
            printf("Erro: Não foi possível abrir o arquivo de texto.\n\n");
            return;
        }

        for (int i = 0; i < lista->qtdOrdensServico; i++) {
            fprintf(dadosOrdensServico, "%s;%d;%d;%f;%d\n",
                    lista->listaOrdensServico[i].descricao,
                    lista->listaOrdensServico[i].idPecas,
                    lista->listaOrdensServico[i].idAgendamentos,
                    lista->listaOrdensServico[i].valorTotal,
                    lista->listaOrdensServico[i].deletado);
        }
        break;
        case 2:
            dadosOrdensServico = fopen("DadosOrdensServico.bin", "wb");

        if (dadosOrdensServico == NULL) {
            printf("Erro: Não foi possível abrir o arquivo binário.\n\n");
            return;
        }

        for (int i = 0; i < lista->qtdOrdensServico; i++) {
            fwrite(&lista->listaOrdensServico[i], sizeof(struct OrdensServico), 1, dadosOrdensServico);
        }
        break;
    }
    fclose(dadosOrdensServico);

    free(lista->listaOrdensServico);
    lista->listaOrdensServico = NULL;

    lista->qtdOrdensServico = 0;
}

// Aloca memória inicial na lista de ordens de serviço
int alocarOrdensServicoModel(struct ListaOrdensServico *lista) {
    lista->qtdOrdensServico = 1;
    lista->listaOrdensServico = malloc(sizeof(struct OrdensServico));

    if (lista->listaOrdensServico == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

// Realoca memória na lista de ordens de serviço conforme a necessidade em qtdAlocada
int realocarOrdensServicoModel(struct ListaOrdensServico *lista, int qtdAlocada) {
    if (qtdAlocada == 0) {
        printf("Nenhum registro salvo.\n\n");
        return 0;
    }

    lista->qtdOrdensServico += qtdAlocada;
    lista->listaOrdensServico = realloc(lista->listaOrdensServico, lista->qtdOrdensServico * sizeof(struct OrdensServico));

    if (lista->listaOrdensServico == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

// Cadastra uma nova ordem de servico
void cadastrarOrdensServicoModel(struct ListaOrdensServico *lista, struct OrdensServico *ordensServico) {
    int resultAlocacao = 0;

    if (lista->qtdOrdensServico == 0) {
        lista->qtdOrdensServico++;
        resultAlocacao = alocarOrdensServicoModel(lista);
    } else {
        resultAlocacao = realocarOrdensServicoModel(lista, 1);
    }

    if (resultAlocacao == 0) {
        printf("Erro: Não foi possível emitir uma ordem do serviço agendado.\n\n");
        return;
    }

    // Cadastrando ordem de serviço na memória
    lista->qtdOrdensServico++;
    ordensServico->deletado = 0;

    lista->listaOrdensServico[lista->qtdOrdensServico - 1] = *ordensServico;
}

