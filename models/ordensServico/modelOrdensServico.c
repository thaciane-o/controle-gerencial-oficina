#include "modelOrdensServico.h"
#include "../../models/pecas/modelPecas.h"
#include "../../models/agendamentos/modelAgendamentos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Busca os dados de ordens de serviço nos arquivos
void buscarDadosOrdensServicoModel(struct ListaOrdensServico *lista, int opcaoArmazenamento) {
    int i = 0;

    FILE *dadosOrdensServico;

    switch (opcaoArmazenamento) {
        case 1:
            dadosOrdensServico = fopen("DadosOrdensServico.txt", "r");

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
                fclose(dadosOrdensServico);
                return;
            }

            if (lista->listaOrdensServico == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                fclose(dadosOrdensServico);
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
                    lista->listaOrdensServico[i].idPecas = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaOrdensServico[i].qtdPecas = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaOrdensServico[i].idAgendamento = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaOrdensServico[i].valorTotal = atof(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaOrdensServico[i].tempoGasto = atof(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaOrdensServico[i].datahoraFinal, token);
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
                fclose(dadosOrdensServico);
                return;
            }

            if (lista->listaOrdensServico == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                fclose(dadosOrdensServico);
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
                fprintf(dadosOrdensServico, "%s;%d;%d;%d;%.2f;%.2f;%s;%d\n",
                        lista->listaOrdensServico[i].descricao,
                        lista->listaOrdensServico[i].idPecas,
                        lista->listaOrdensServico[i].qtdPecas,
                        lista->listaOrdensServico[i].idAgendamento,
                        lista->listaOrdensServico[i].valorTotal,
                        lista->listaOrdensServico[i].tempoGasto,
                        lista->listaOrdensServico[i].datahoraFinal,
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
    lista->listaOrdensServico = realloc(lista->listaOrdensServico,
                                        lista->qtdOrdensServico * sizeof(struct OrdensServico));

    if (lista->listaOrdensServico == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

// Cadastra uma nova ordem de serviço
void cadastrarOrdensServicoModel(struct ListaOrdensServico *lista, struct OrdensServico *ordensServico, int autoId) {
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
    if (autoId == 1) {
        strcpy(ordensServico->datahoraFinal, "NF");
        ordensServico->tempoGasto = 0;
        ordensServico->deletado = 0;
    }

    lista->listaOrdensServico[lista->qtdOrdensServico - 1] = *ordensServico;
}

// Lista uma ordem de serviço pelo ID
void listarOrdensServicoModel(struct ListaOrdensServico *lista, int id) {
    if (lista->qtdOrdensServico == 0) {
        printf("Nenhuma ordem de serviço foi emitida!\n\n");
        return;
    }

    // Se há um ou mais cadastros, procura pela ordem de serviço com o ID desejado
    for (int i = 0; i < lista->qtdOrdensServico; i++) {
        // Verifica se a ordem de serviço está ou não deletado
        if (lista->listaOrdensServico[i].idAgendamento == id && lista->listaOrdensServico[i].deletado == 0) {
            if (strcmp(lista->listaOrdensServico[i].datahoraFinal, "NF") == 0) {
                printf("====================="
                       "\n| ORDEM DE SERVIÇO  |"
                       "\n====================="
                       "\nDESCRIÇÃO DO SERVIÇO: %s"
                       "\nVALOR TOTAL: %f"
                       "\nAGENDAMENTO: %d"
                       "\nPEÇA: %d"
                       "\nO SERVIÇO AINDA ESTÁ EM ANDAMENTO\n",
                       lista->listaOrdensServico[i].descricao,
                       lista->listaOrdensServico[i].valorTotal,
                       lista->listaOrdensServico[i].idAgendamento,
                       lista->listaOrdensServico[i].idPecas);
            } else {
                printf("====================="
                       "\n| ORDEM DE SERVIÇO  |"
                       "\n====================="
                       "\nDESCRIÇÃO DO SERVIÇO: %s"
                       "\nVALOR TOTAL: %f"
                       "\nAGENDAMENTO: %d"
                       "\nPEÇA: %d"
                       "\nTEMPO GASTO: %.2f hora(s)"
                       "\nDATA E HORA FINALIZADA: %s\n",
                       lista->listaOrdensServico[i].descricao,
                       lista->listaOrdensServico[i].valorTotal,
                       lista->listaOrdensServico[i].idAgendamento,
                       lista->listaOrdensServico[i].idPecas,
                       lista->listaOrdensServico[i].tempoGasto,
                       lista->listaOrdensServico[i].datahoraFinal);
            }
        }
    }
}

// Deleta uma ordem de serviço cadastrada
void deletarOrdensServicoModel(struct ListaOrdensServico *lista, int id) {
    int encontrado = 0;

    // Verifica se há algum cadastro
    if (lista->qtdOrdensServico == 0) {
        printf("Nenhuma ordem de serviço foi emitida!\n\n");
        return;
    }

    // Busca pelo ID para fazer a deleção
    for (int i = 0; i < lista->qtdOrdensServico; i++) {
        if (lista->listaOrdensServico[i].idAgendamento == id && lista->listaOrdensServico[i].deletado == 0) {
            encontrado = 1;

            lista->listaOrdensServico[i].deletado = 1;
        }
    }

    // Se não encontrar o ID para deleção, avisa o usuário
    if (!encontrado) {
        printf("Ordem de serviço não encontrada!\n\n");
    } else {
        printf("Ordem de serviço cancelada com sucesso!\n\n");
    }
}

// Finaliza uma ordem de serviço
void finalizarOrdemServicoModel(struct ListaOrdensServico *lista, struct ListaAgendamentos *listaAgendamentos,
                                int idAgendamento, int idServico) {
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    struct tm tmInicial = {0};
    struct tm tmFinal = {0};
    int ordemEncontrada = 0, qtdOrdensServico = 0, qtdOrdensServicoFim = 0;

    for (int i = 0; i < lista->qtdOrdensServico; i++) {
        if (lista->listaOrdensServico[i].idAgendamento == idAgendamento && lista->listaOrdensServico[i].deletado == 0
            && listaAgendamentos->listaAgendamentos[idAgendamento - 1].idServico == idServico &&
            listaAgendamentos->listaAgendamentos[idAgendamento - 1].finalizado == 0) {
            qtdOrdensServico++;

            // Convertendo data hora em string
            strftime(lista->listaOrdensServico[i].datahoraFinal, sizeof(lista->listaOrdensServico[i].datahoraFinal),
                     "%d/%m/%Y %H:%M", local);

            // Convertendo string em struct tm
            sscanf(listaAgendamentos->listaAgendamentos[idAgendamento - 1].datahoraInicial, "%d/%d/%d %d:%d",
                   &tmInicial.tm_mday, &tmInicial.tm_mon, &tmInicial.tm_year,
                   &tmInicial.tm_hour, &tmInicial.tm_min);
            sscanf(lista->listaOrdensServico[i].datahoraFinal, "%d/%d/%d %d:%d",
                   &tmFinal.tm_mday, &tmFinal.tm_mon, &tmFinal.tm_year,
                   &tmFinal.tm_hour, &tmFinal.tm_min);

            tmInicial.tm_mon -= 1;
            tmInicial.tm_year -= 1900;

            tmFinal.tm_mon -= 1;
            tmFinal.tm_year -= 1900;

            // Convertendo struct tm para time_t
            time_t tempoInicial = mktime(&tmInicial);
            time_t tempoFinal = mktime(&tmFinal);

            if (tempoInicial == -1 || tempoFinal == -1) {
                printf("Erro ao converter a data e hora.\n");
                return;
            }

            // Calculando a diferença em horas
            float tempoGastoAtual = difftime(tempoFinal, tempoInicial) / 3600;

            // Subtraindo o tempo gasto de outras ordens de serviço finalizadas
            for (int j = 0; j < lista->qtdOrdensServico; j++) {
                if (i != j && strcmp(listaAgendamentos->listaAgendamentos[idAgendamento - 1].datahoraInicial,
                                     listaAgendamentos->listaAgendamentos[j].datahoraInicial) == 0 &&
                    lista->listaOrdensServico[j].deletado == 0 &&
                    listaAgendamentos->listaAgendamentos[j].idServico != idServico) {
                    tempoGastoAtual -= lista->listaOrdensServico[j].tempoGasto;
                }
            }

            lista->listaOrdensServico[i].tempoGasto = tempoGastoAtual;
            ordemEncontrada = 1;
        }
    }

    for (int i = 0; i < lista->qtdOrdensServico; i++) {
        if (lista->listaOrdensServico[i].datahoraFinal != NULL && lista->listaOrdensServico[i].idAgendamento ==
            idAgendamento) {
            qtdOrdensServicoFim++;
        }
    }

    if (qtdOrdensServico == qtdOrdensServicoFim) {
        finalizarAgendamentoModel(listaAgendamentos, idAgendamento);
    }

    // Se não encontrar a ordem de serviço
    if (!ordemEncontrada) {
        printf("\nOrdem de serviço não encontrada.\n");
    } else {
        printf("\nOrdem de serviço finalizada com sucesso!\n");
    }
}
