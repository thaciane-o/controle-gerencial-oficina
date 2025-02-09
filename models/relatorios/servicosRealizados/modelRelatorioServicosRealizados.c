#include "modelRelatorioServicosRealizados.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../oficina/modelOficina.h"
#include "../../fornecedores/modelFornecedores.h"
#include "../../funcionarios/modelFuncionarios.h"
#include "../../pagamentoFornecedor/modelPagamentoFornecedor.h"
#include "../../ordensServico/modelOrdensServico.h"
#include "../../agendamentos/modelAgendamentos.h"
#include "../../clientes/modelClientes.h"
#include "../../notasFiscais/modelNotasFiscais.h"
#include "../../pecas/modelPecas.h"
#include "../../pecasNotas/modelPecasNotas.h"
#include "../../pagamentoCliente/modelPagamentoCliente.h"
#include "../../veiculos/modelVeiculos.h"


// Imprime o relatório na tela
void imprimirRelatorioServicosRealizados(struct ListaClientes *listaClientes, struct ListaServicos *listaServicos,
                              struct ListaOrdensServico *listaOrdensServicos,
                              struct ListaAgendamentos *listaAgendamentos,
                              struct ListaFuncionarios *listaFuncionarios,
                              struct ListaVeiculos *listaVeiculos,
                              struct tm dataInicial, struct tm dataFinal, int tipo,
                              int id) {
    // Variavel de verificação de serviços
    int existeServico = 0;

    time_t tInicial;
    time_t tFinal;
    int cliente = 0, funcionario = 0, servico = 0 ;

    int idAgendamento = 0;

    // Filtrando tipo de registro
    switch (tipo){
            case 1:
                servico = id;
            break;
            case 2:
                cliente = id;
                break;
            case 3:
                funcionario = id;
                break;
            case 4:

                tInicial = mktime(&dataInicial);
                tFinal = mktime(&dataFinal);
                break;
            default:
                return;;
    }

    // Verifica se há pelo menos um registro
    if (listaOrdensServicos->qtdOrdensServico > 0) {
        // Exibe todos os registros
        for (int i = 0; i < listaOrdensServicos->qtdOrdensServico; i++) {

            idAgendamento = listaOrdensServicos->listaOrdensServico[i].idAgendamento;
            time_t tOrdemServico;
            struct tm dataOrdemServico;

            // Converter string para struct tm
            if (sscanf(listaOrdensServicos->listaOrdensServico[i].datahoraFinal, "%d/%d/%d %d:%d",
                       &dataOrdemServico.tm_mday, &dataOrdemServico.tm_mon, &dataOrdemServico.tm_year,
                       &dataOrdemServico.tm_hour, &dataOrdemServico.tm_min) != 5) {
                continue;
            }

            dataOrdemServico.tm_mon -= 1;
            dataOrdemServico.tm_year -= 1900;

            tOrdemServico = mktime(&dataOrdemServico);


            // Verificar se não está deletado, se foi finalizado e aplica os filtros
            if (listaOrdensServicos->listaOrdensServico[i].deletado == 0 &&
                (((listaAgendamentos->listaAgendamentos[idAgendamento - 1].idFuncionario == funcionario) ||
                 (listaAgendamentos->listaAgendamentos[idAgendamento - 1].idServico == servico) ||
                 (listaVeiculos->listaVeiculos[
                      listaAgendamentos->listaAgendamentos[idAgendamento - 1].idVeiculo - 1].idProprietario
                  == cliente)) ||
                (tipo == 4 && tOrdemServico >= tInicial && tOrdemServico <= tFinal))) {

                existeServico = 1;
                printf("\n===================\n"
                   "| SERVIÇO %d       |\n"
                   "===================\n"
                   "DESCRIÇÃO: %s\n"
                   "PREÇO: $%.2f\n"
                   "COMISSÃO: $%.2f\n"
                   "CLIENTE: %s\n"
                   "FUNCIONARIO: %s\n"
                   "DATA DA REALIZAÇÃO: %s\n\n",
                   listaServicos->listaServicos[listaAgendamentos->listaAgendamentos[idAgendamento - 1].idServico - 1].id,
                   listaOrdensServicos->listaOrdensServico[i].descricao,
                   listaOrdensServicos->listaOrdensServico[i].valorTotal,
                   listaServicos->listaServicos[listaAgendamentos->listaAgendamentos[idAgendamento - 1].idServico - 1].comissao,
                   listaClientes->listaClientes[listaVeiculos->listaVeiculos[listaAgendamentos->listaAgendamentos[idAgendamento - 1].idVeiculo - 1].idProprietario - 1].nome,
                   listaFuncionarios->listaFuncionarios[listaAgendamentos->listaAgendamentos[idAgendamento - 1].idFuncionario - 1].nome,
                   listaOrdensServicos->listaOrdensServico[i].datahoraFinal);
            }
        }
    }


    // Verifica se não há registros
    if (!existeServico) {
        printf("Nenhum serviço realizado foi encontrado.\n\n");
    }
}

// Armazena o relatório em arquivo
void armazenarRelatorioServicosRealizados(struct ListaClientes *listaClientes, struct ListaServicos *listaServicos,
                              struct ListaOrdensServico *listaOrdensServicos,
                              struct ListaAgendamentos *listaAgendamentos,
                              struct ListaFuncionarios *listaFuncionarios,
                              struct ListaVeiculos *listaVeiculos,
                              struct tm dataInicial, struct tm dataFinal, int tipo,
                              int id) {
    // Abrindo ou criando arquivo para adicionar dados
    FILE *relatorioOrdensServicos;

    // Abrindo o arquivo de texto para escrita
    relatorioOrdensServicos = fopen("RelatorioOrdensServicos.txt", "w");

    // Verificando se foi possível abrir o arquivo
    if (relatorioOrdensServicos == NULL) {
        printf("Erro: Não foi possível abrir o arquivo de texto.\n\n");
        return;
    }

    int existeServico = 0;

    time_t tInicial;
    time_t tFinal;
    int cliente = 0, funcionario = 0, servico = 0 ;

    int idAgendamento = 0;

    // Filtrando tipo de registro
    switch (tipo){
            case 1:
                servico = id;
            break;
            case 2:
                cliente = id;
                break;
            case 3:
                funcionario = id;
                break;
            case 4:

                tInicial = mktime(&dataInicial);
                tFinal = mktime(&dataFinal);
                break;
            default:
                return;;
    }

    // Verifica se há pelo menos um registro
    if (listaOrdensServicos->qtdOrdensServico > 0) {
        // Exibe todos os registros
        for (int i = 0; i < listaOrdensServicos->qtdOrdensServico; i++) {

            idAgendamento = listaOrdensServicos->listaOrdensServico[i].idAgendamento;
            time_t tOrdemServico;
            struct tm dataOrdemServico;

            // Converter string para struct tm
            if (sscanf(listaOrdensServicos->listaOrdensServico[i].datahoraFinal, "%d/%d/%d %d:%d",
                       &dataOrdemServico.tm_mday, &dataOrdemServico.tm_mon, &dataOrdemServico.tm_year,
                       &dataOrdemServico.tm_hour, &dataOrdemServico.tm_min) != 5) {
                continue;
            }

            dataOrdemServico.tm_mon -= 1;
            dataOrdemServico.tm_year -= 1900;

            tOrdemServico = mktime(&dataOrdemServico);


            // Verificar se não está deletado, se foi finalizado e aplica os filtros
            if (listaOrdensServicos->listaOrdensServico[i].deletado == 0 &&
                strcmp(listaOrdensServicos->listaOrdensServico[i].datahoraFinal, "NF") != 0 &&
                (((listaAgendamentos->listaAgendamentos[idAgendamento - 1].idFuncionario == funcionario) ||
                 (listaAgendamentos->listaAgendamentos[idAgendamento - 1].idServico == servico) ||
                 (listaVeiculos->listaVeiculos[
                      listaAgendamentos->listaAgendamentos[idAgendamento - 1].idVeiculo - 1].idProprietario
                  == cliente)) ||
                (tipo == 4 && tOrdemServico >= tInicial && tOrdemServico <= tFinal))) {

                existeServico = 1;
                fprintf(relatorioOrdensServicos,"%d;%s;%.2f;%.2f;%s;%s;%s\n",
                    listaServicos->listaServicos[listaAgendamentos->listaAgendamentos[idAgendamento - 1].idServico - 1].id,
                    listaOrdensServicos->listaOrdensServico[i].descricao,
                    listaOrdensServicos->listaOrdensServico[i].valorTotal,
                    listaServicos->listaServicos[listaAgendamentos->listaAgendamentos[idAgendamento - 1].idServico - 1].comissao,
                    listaClientes->listaClientes[listaVeiculos->listaVeiculos[listaAgendamentos->listaAgendamentos[idAgendamento - 1].idVeiculo - 1].idProprietario - 1].nome,
                    listaFuncionarios->listaFuncionarios[listaAgendamentos->listaAgendamentos[idAgendamento - 1].idFuncionario - 1].nome,
                    listaOrdensServicos->listaOrdensServico[i].datahoraFinal);
            }
        }
    }


    // Verifica se não há registros
    if (!existeServico) {
        fclose(relatorioOrdensServicos);
        printf("Nenhum serviço realizado foi encontrado.\n\n");
        return;
    }

    printf("Relatório de serviços realizados foi feito com sucesso!\n\n");

    // Fechando o arquivo
    fclose(relatorioOrdensServicos);
}
