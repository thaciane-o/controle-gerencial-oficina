#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "modelRelatorioEstoque.h"
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
void imprimirRelatorioEstoque(struct ListaPecas *listaPecas, struct ListaClientes *listaClientes,
                              struct ListaServicos *listaServicos,
                              struct ListaAgendamentos *listaAgendamentos,
                              struct ListaOrdensServico *listaOrdensServicos,
                              struct ListaFuncionarios *listaFuncionarios,
                              struct ListaVeiculos *listaVeiculos,
                              struct tm dataInicial, struct tm dataFinal, int tipo,
                              int id) {

    // Variavel de verificação de estoque
    int existeEstoque = 0;
    time_t tInicial;
    time_t tFinal;
    int cliente = 0, funcionario = 0, servico = 0 ;

    int idAgendamento = 0;

    // Filtrando tipo de relatorio
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
            case 5:

                break;
            default:
                return;;
    }

    // Verifica se há pelo menos um registro
    if (listaOrdensServicos->qtdOrdensServico > 0) {
        // Exibe todos os registros
        for (int i = 0; i < listaOrdensServicos->qtdOrdensServico; i++) {

            idAgendamento = listaOrdensServicos->listaOrdensServico[i].idAgendamento;
            time_t tAgendamento;
            struct tm dataAgendamento;

            // Converter string para struct tm

            if (sscanf(listaAgendamentos->listaAgendamentos[idAgendamento - 1].datahoraInicial, "%d/%d/%d %d:%d",
                   &dataAgendamento.tm_mday, &dataAgendamento.tm_mon, &dataAgendamento.tm_year,
                   &dataAgendamento.tm_hour, &dataAgendamento.tm_min) != 5) {
                continue;
            }

            dataAgendamento.tm_mon -= 1;
            dataAgendamento.tm_year -= 1900;

            tAgendamento = mktime(&dataAgendamento);

            // Percorre os registros de peças
            for (int j = 0; j < listaPecas->qtdPecas; j++) {

                // Verificar se não está deletado, se foi finalizado e aplica os filtros
                if (listaPecas->listaPecas[j].deletado  == 0 &&
                    listaOrdensServicos->listaOrdensServico[i].deletado == 0 &&
                    listaPecas->listaPecas[j].id == listaOrdensServicos->listaOrdensServico[i].idPecas &&
                    (((listaAgendamentos->listaAgendamentos[idAgendamento - 1].idFuncionario == funcionario) ||
                     (listaAgendamentos->listaAgendamentos[idAgendamento - 1].idServico == servico) ||
                     (listaVeiculos->listaVeiculos[
                          listaAgendamentos->listaAgendamentos[idAgendamento - 1].idVeiculo - 1].idProprietario
                      == cliente)) || (tipo == 5 && listaPecas->listaPecas[j].qtdEstoque < listaPecas->listaPecas[j].estoqueMinimo) ||
                    (tipo == 4 && tAgendamento >= tInicial && tAgendamento <= tFinal))) {
                    existeEstoque = 1;
                    printf("\n====================\n"
                       "| PEÇA %d           |\n"
                       "====================\n"
                       "DESCRIÇÃO: %s\n"
                       "FABRICANTE: %s\n"
                       "PREÇO DE CUSTO: $%.2f\n"
                       "PREÇO DE VENDA: $%.2f\n"
                       "QUANTIDADE EM ESTOQUE: %d\n"
                       "ESTOQUE MÍNIMO: %d\n"
                       "QUANTIDADE UTILIZADA: %d\n"
                       "CLIENTE: %s\n"
                       "FUNCIONARIO: %s\n"
                       "SERVIÇO: %s\n"
                       "DATA DE USO: %s\n\n",
                       listaPecas->listaPecas[j].id,
                       listaPecas->listaPecas[j].descricao,
                       listaPecas->listaPecas[j].fabricante,
                       listaPecas->listaPecas[j].precoCusto,
                       listaPecas->listaPecas[j].precoVenda,
                       listaPecas->listaPecas[j].qtdEstoque,
                       listaPecas->listaPecas[j].estoqueMinimo,
                       listaOrdensServicos->listaOrdensServico[i].qtdPecas,
                       listaClientes->listaClientes[listaVeiculos->listaVeiculos[listaAgendamentos->listaAgendamentos[idAgendamento - 1].idVeiculo - 1].idProprietario - 1].nome,
                       listaFuncionarios->listaFuncionarios[listaAgendamentos->listaAgendamentos[idAgendamento - 1].idFuncionario - 1].nome,
                       listaOrdensServicos->listaOrdensServico[i].descricao,
                       listaAgendamentos->listaAgendamentos[idAgendamento - 1].datahoraInicial);
                    }
            }
        }
    }

    // Verifica se não há registros
    if (!existeEstoque) {
        printf("Nenhuma peça foi cadastrado.\n\n");
        return;
    }
}

// Armazena o relatório em arquivo
void armazenarRelatorioEstoque(struct ListaPecas *listaPecas, struct ListaClientes *listaClientes,
                              struct ListaServicos *listaServicos,
                              struct ListaAgendamentos *listaAgendamentos,
                              struct ListaOrdensServico *listaOrdensServicos,
                              struct ListaFuncionarios *listaFuncionarios,
                              struct ListaVeiculos *listaVeiculos,
                              struct tm dataInicial, struct tm dataFinal, int tipo,
                              int id) {
    int existeEstoque = 0;
    time_t tInicial;
    time_t tFinal;
    int cliente = 0, funcionario = 0, servico = 0 ;

    int idAgendamento = 0;

    // Abrindo ou criando arquivo para adicionar dados
    FILE *relatorioEstoque;

    // Abrindo o arquivo de texto para escrita
    relatorioEstoque = fopen("RelatorioEstoque.txt", "w");

    // Verificando se foi possível abrir o arquivo
    if (relatorioEstoque == NULL) {
        printf("Erro: Não foi possível abrir o arquivo de texto.\n\n");
        return;
    }

    // Inserindo os dados no arquivo de relatório
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
            case 5:

                break;
            default:
                fclose(relatorioEstoque);
                return;;
    }

    // Verifica se há pelo menos um registro
    if (listaOrdensServicos->qtdOrdensServico > 0) {
        // Exibe todos os registros
        for (int i = 0; i < listaOrdensServicos->qtdOrdensServico; i++) {
            idAgendamento = listaOrdensServicos->listaOrdensServico[i].idAgendamento;
            time_t tAgendamento;
            struct tm dataAgendamento;

            // Converter string para struct tm
            if (sscanf(listaAgendamentos->listaAgendamentos[idAgendamento - 1].datahoraInicial, "%d/%d/%d %d:%d",
                       &dataAgendamento.tm_mday, &dataAgendamento.tm_mon, &dataAgendamento.tm_year,
                       &dataAgendamento.tm_hour, &dataAgendamento.tm_min) != 5) {
                continue;
                       }

            dataAgendamento.tm_mon -= 1;
            dataAgendamento.tm_year -= 1900;

            tAgendamento = mktime(&dataAgendamento);


            // Percorre os registros de peças
            for (int j = 0; j < listaPecas->qtdPecas; j++) {
                // Verificar se não está deletado, se foi finalizado e aplica os filtros
                if (listaPecas->listaPecas[j].deletado  == 0 &&
                    listaOrdensServicos->listaOrdensServico[i].deletado == 0 &&
                    listaPecas->listaPecas[j].id == listaOrdensServicos->listaOrdensServico[i].idPecas &&
                    (((listaAgendamentos->listaAgendamentos[idAgendamento - 1].idFuncionario == funcionario) ||
                     (listaAgendamentos->listaAgendamentos[idAgendamento - 1].idServico == servico) ||
                     (listaVeiculos->listaVeiculos[
                          listaAgendamentos->listaAgendamentos[idAgendamento - 1].idVeiculo - 1].idProprietario
                      == cliente)) || (tipo == 5 && listaPecas->listaPecas[j].qtdEstoque < listaPecas->listaPecas[j].estoqueMinimo) ||
                    (tipo == 4 && tAgendamento >= tInicial && tAgendamento <= tFinal))) {

                    existeEstoque = 1;
                    fprintf(relatorioEstoque, "%d;%s;%s;%.2f;%.2f;%d;%d;%d;%s;%s;%s;%s\n",
                       listaPecas->listaPecas[j].id,
                       listaPecas->listaPecas[j].descricao,
                       listaPecas->listaPecas[j].fabricante,
                       listaPecas->listaPecas[j].precoCusto,
                       listaPecas->listaPecas[j].precoVenda,
                       listaPecas->listaPecas[j].qtdEstoque,
                       listaPecas->listaPecas[j].estoqueMinimo,
                       listaOrdensServicos->listaOrdensServico[i].qtdPecas,
                       listaClientes->listaClientes[listaVeiculos->listaVeiculos[listaAgendamentos->listaAgendamentos[idAgendamento - 1].idVeiculo - 1].idProprietario - 1].nome,
                       listaFuncionarios->listaFuncionarios[listaAgendamentos->listaAgendamentos[idAgendamento - 1].idFuncionario - 1].nome,
                       listaOrdensServicos->listaOrdensServico[i].descricao,
                       listaAgendamentos->listaAgendamentos[idAgendamento - 1].datahoraInicial);
                    }
            }
        }
    }

    // Verifica se não há registros
    if (!existeEstoque) {
        printf("Nenhuma peça foi cadastrado.\n\n");
        return;
    }

    printf("Relatório de estoques realizado com sucesso!\n\n");

    // Fechando o arquivo
    fclose(relatorioEstoque);
}


