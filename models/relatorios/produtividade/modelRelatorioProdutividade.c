#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../ordensServico/modelOrdensServico.h"
#include "../../agendamentos/modelAgendamentos.h"
#include "../../funcionarios/modelFuncionarios.h"

// Imprime o relatório na tela
void imprimirRelatorioProdutividade(struct ListaOrdensServico *listaOrdensServicos,
                                    struct ListaAgendamentos *listaAgendamentos,
                                    struct ListaFuncionarios *listaFuncionarios, int funcionario, int servico,
                                    struct tm dataHoraInicial,
                                    struct tm dataHoraFinal) {
    int existeOrdemServico = 0, idMenor = 0, idMaior = 0, idAgendamento = 0;
    float maior = FLT_MIN, menor = FLT_MAX;
    time_t tInicial = mktime(&dataHoraInicial);
    time_t tFinal = mktime(&dataHoraFinal);
    struct tm dataOS = {0};
    struct tm dataAgendamento = {0};

    // Verifica se há pelo menos um registro
    if (listaOrdensServicos->qtdOrdensServico > 0) {
        // Exibe todos os registros
        for (int i = 0; i < listaOrdensServicos->qtdOrdensServico; i++) {
            idAgendamento = listaOrdensServicos->listaOrdensServico[i].idAgendamento;

            // Converter string para struct tm
            if (sscanf(listaOrdensServicos->listaOrdensServico[i].datahoraFinal, "%d/%d/%d %d:%d",
                       &dataOS.tm_mday, &dataOS.tm_mon, &dataOS.tm_year,
                       &dataOS.tm_hour, &dataOS.tm_min) != 5 ||
                sscanf(listaAgendamentos->listaAgendamentos[idAgendamento - 1].datahoraInicial, "%d/%d/%d %d:%d",
                       &dataAgendamento.tm_mday, &dataAgendamento.tm_mon, &dataAgendamento.tm_year,
                       &dataAgendamento.tm_hour, &dataAgendamento.tm_min) != 5) {
                continue;
            }

            dataOS.tm_year -= 1900;
            dataOS.tm_mon -= 1;

            dataAgendamento.tm_year -= 1900;
            dataAgendamento.tm_mon -= 1;

            // Converter para time_t
            time_t tOS = mktime(&dataOS);
            time_t tAgendamento = mktime(&dataAgendamento);

            // Verificar se não está deletado, se foi finalizado e aplica os filtros
            if (listaOrdensServicos->listaOrdensServico[i].deletado == 0 &&
                (strcmp(listaOrdensServicos->listaOrdensServico[i].datahoraFinal, "NF") != 0) &&
                ((listaAgendamentos->listaAgendamentos[idAgendamento - 1].idFuncionario == funcionario) ||
                 (listaAgendamentos->listaAgendamentos[idAgendamento - 1].idServico == servico)) ||
                ((tAgendamento >= tInicial && tOS <= tFinal))) {
                // Pega o menor tempo gasto
                if (listaOrdensServicos->listaOrdensServico[i].tempoGasto < menor) {
                    menor = listaOrdensServicos->listaOrdensServico[i].tempoGasto;
                    idMenor = idAgendamento;
                }

                // Pega o maior tempo gasto
                if (listaOrdensServicos->listaOrdensServico[i].tempoGasto > maior) {
                    maior = listaOrdensServicos->listaOrdensServico[i].tempoGasto;
                    idMaior = idAgendamento;
                }
            }
        }

        // Exibe todos os registros
        for (int i = 0; i < listaOrdensServicos->qtdOrdensServico; i++) {
            // Aplica os filtros
            idAgendamento = listaOrdensServicos->listaOrdensServico[i].idAgendamento;
            if (((idAgendamento == idMaior) || (idAgendamento == idMenor))) {
                existeOrdemServico = 1;
                printf("\n====================\n"
                       "| PRODUTIVIDADE    |\n"
                       "====================\n"
                       "SERVIÇO: %s\n"
                       "FUNCIONÁRIO: %s\n"
                       "TEMPO GASTO: %.2f\n"
                       "DATA INICIAL: %s\n"
                       "DATA FINAL: %s\n",
                       listaOrdensServicos->listaOrdensServico[i].descricao,
                       listaFuncionarios->listaFuncionarios[listaAgendamentos->listaAgendamentos[
                           listaOrdensServicos->listaOrdensServico[i].idAgendamento - 1].idFuncionario].nome,
                       listaOrdensServicos->listaOrdensServico[i].tempoGasto,
                       listaAgendamentos->listaAgendamentos[
                           listaOrdensServicos->listaOrdensServico[i].idAgendamento - 1].datahoraInicial,
                       listaOrdensServicos->listaOrdensServico[i].datahoraFinal);
            }
        }
    }

    // Verifica se não há registros
    if (!existeOrdemServico) {
        printf("Nenhuma ordem de serviço foi encontrada.\n\n");
    }
}

// Armazena o relatório em arquivo
void armazenarRelatorioProdutividade(struct ListaOrdensServico *listaOrdensServicos,
                                     struct ListaAgendamentos *listaAgendamentos,
                                     struct ListaFuncionarios *listaFuncionarios, int funcionario, int servico,
                                     struct tm dataHoraInicial,
                                     struct tm dataHoraFinal) {
    // Abrindo ou criando arquivo para adicionar dados
    FILE *relatorioProdutividade;
    int idMenor = 0, idMaior = 0, idAgendamento = 0;
    float maior = FLT_MIN, menor = FLT_MAX;
    time_t tInicial = mktime(&dataHoraInicial);
    time_t tFinal = mktime(&dataHoraFinal);
    struct tm dataOS = {0};
    struct tm dataAgendamento = {0};

    // Abrindo o arquivo de texto para escrita
    relatorioProdutividade = fopen("RelatorioProdutividade.txt", "w");

    // Verificando se foi possível abrir o arquivo
    if (relatorioProdutividade == NULL) {
        printf("Erro: Não foi possível abrir o arquivo de texto.\n\n");
        return;
    }

    // Verifica se há pelo menos um registro
    if (listaOrdensServicos->qtdOrdensServico > 0) {
        // Exibe todos os registros
        for (int i = 0; i < listaOrdensServicos->qtdOrdensServico; i++) {
            idAgendamento = listaOrdensServicos->listaOrdensServico[i].idAgendamento;

            // Converter string para struct tm
            if (sscanf(listaOrdensServicos->listaOrdensServico[i].datahoraFinal, "%d/%d/%d %d:%d",
                       &dataOS.tm_mday, &dataOS.tm_mon, &dataOS.tm_year,
                       &dataOS.tm_hour, &dataOS.tm_min) != 5 ||
                sscanf(listaAgendamentos->listaAgendamentos[idAgendamento - 1].datahoraInicial, "%d/%d/%d %d:%d",
                       &dataAgendamento.tm_mday, &dataAgendamento.tm_mon, &dataAgendamento.tm_year,
                       &dataAgendamento.tm_hour, &dataAgendamento.tm_min) != 5) {
                continue;
            }

            dataOS.tm_year -= 1900;
            dataOS.tm_mon -= 1;

            dataAgendamento.tm_year -= 1900;
            dataAgendamento.tm_mon -= 1;

            // Converter para time_t
            time_t tOS = mktime(&dataOS);
            time_t tAgendamento = mktime(&dataAgendamento);

            // Verificar se não está deletado, se foi finalizado e aplica os filtros
            if (listaOrdensServicos->listaOrdensServico[i].deletado == 0 &&
                (strcmp(listaOrdensServicos->listaOrdensServico[i].datahoraFinal, "NF") != 0) &&
                ((listaAgendamentos->listaAgendamentos[idAgendamento - 1].idFuncionario == funcionario) ||
                 (listaAgendamentos->listaAgendamentos[idAgendamento - 1].idServico == servico)) ||
                ((tAgendamento >= tInicial && tOS <= tFinal))) {
                // Pega o menor tempo gasto
                if (listaOrdensServicos->listaOrdensServico[i].tempoGasto < menor) {
                    idMenor = listaOrdensServicos->listaOrdensServico[i].idAgendamento;
                }

                // Pega o menor tempo gasto
                if (listaOrdensServicos->listaOrdensServico[i].tempoGasto > maior) {
                    idMaior = listaOrdensServicos->listaOrdensServico[i].idAgendamento;
                }
            }
        }

        // Inserindo os dados no arquivo de relatório
        for (int i = 0; i < listaOrdensServicos->qtdOrdensServico; i++) {
            // Aplica os filtros
            idAgendamento = listaOrdensServicos->listaOrdensServico[i].idAgendamento;
            if (((idAgendamento == idMaior) || (idAgendamento == idMenor))) {
                fprintf(relatorioProdutividade, "%s;%s;%.2f;%s;%s\n",
                        listaOrdensServicos->listaOrdensServico[i].descricao,
                        listaFuncionarios->listaFuncionarios[listaAgendamentos->listaAgendamentos[
                            listaOrdensServicos->listaOrdensServico[i].idAgendamento - 1].idFuncionario].nome,
                        listaOrdensServicos->listaOrdensServico[i].tempoGasto,
                        listaAgendamentos->listaAgendamentos[
                            listaOrdensServicos->listaOrdensServico[i].idAgendamento - 1].datahoraInicial,
                        listaOrdensServicos->listaOrdensServico[i].datahoraFinal);
            }
        }

        printf("Relatório de produtividade realizado com sucesso!\n\n");
    } else {
        printf("Nenhuma ordem de serviço foi encontrada.\n\n");
    }

    // Fechando o arquivo
    fclose(relatorioProdutividade);
}
