#include "./modelRelatorioFinanceiro.h"
#include "../../oficina/modelOficina.h"
#include "../../clientes/modelClientes.h"
#include "../../fornecedores/modelFornecedores.h"
#include "../../pagamentoCliente/modelPagamentoCliente.h"
#include "../../pagamentoFornecedor/modelPagamentoFornecedor.h"
#include "../../caixas/modelCaixa.h"

#include <float.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


// Imprime o relatório na tela
void imprimirRelatorioFinanceiro(struct ListaCaixas *listaCaixas, struct ListaOficinas *listaOficinas,
                                 struct ListaPagamentosCliente *listaPagamentosCliente,
                                 struct ListaPagamentosFornecedor *listaPagamentosFornecedor,
                                 struct ListaClientes *listaClientes,
                                 struct ListaFornecedores *listaFornecedores, int id, int tipoConta, int tipoFiltro,
                                 struct tm dataHoraInicial,
                                 struct tm dataHoraFinal) {

    int existePagamento = 0, cliente = 0, fornecedor = 0;
    time_t tInicial = 0;
    time_t tFinal = 0;
    struct tm dataPagamento = {0};


    // Filtrando o relatório
    switch (tipoFiltro) {
        case 1:
            cliente = id;

            // Verifica se há pelo menos um registro
            if (listaCaixas->qtdCaixas > 0) {
                // Exibe todos os registros
                for (int i = 0; i < listaPagamentosCliente->qtdPagamentosCliente; i++) {

                    // Verificar se não está deletado, se foi finalizado e aplica os filtros
                    if (listaPagamentosCliente->listaPagamentosCliente[i].deletado == 0 &&
                        (strcmp(listaPagamentosCliente->listaPagamentosCliente[i].dataRecebimento, "Não pago") == 0) &&
                        listaCaixas->listaCaixas[listaPagamentosCliente->listaPagamentosCliente[i].idCaixa - 1].deletado == 0 &&
                        ((listaPagamentosCliente->listaPagamentosCliente[i].idCliente == cliente))) {
                        existePagamento = 1;
                        printf("\n=====================\n"
                               "| CONTA A RECEBER %d |\n"
                               "=====================\n"
                               "VALOR: R$%.2f\n"
                               "CLIENTE: %s\n"
                               "OFICINA: %s\n"
                               "DATA A RECEBER: %s\n\n",
                               listaPagamentosCliente->listaPagamentosCliente[i].id,
                               listaPagamentosCliente->listaPagamentosCliente[i].valor,
                               listaClientes->listaClientes[listaPagamentosCliente->listaPagamentosCliente[i].idCliente - 1].nome,
                               listaOficinas->listaOficinas[listaCaixas->listaCaixas[
                                       listaPagamentosCliente->listaPagamentosCliente[i].idCaixa - 1].idOficina - 1].
                               nome,
                               listaPagamentosCliente->listaPagamentosCliente[i].dataAReceber);
                        }
                }

                // Verifica se não há registros
                if (!existePagamento) {
                    printf("Nenhum recebimento pendente.\n\n");
                }
            }
        break;
        case 2:
            fornecedor = id;

            // Verifica se há pelo menos um registro
            if (listaCaixas->qtdCaixas > 0) {

                // Recebendo data e hora atual da maquina
                time_t tAtual = time(NULL);
                struct tm dataAtual = *localtime(&tAtual);
                tAtual = mktime(&dataAtual);

                // Exibe todos os registros
                for (int i = 0; i < listaPagamentosFornecedor->qtdPagamentosFornecedor; i++) {

                    // Converter string para struct tm
                    if (sscanf(listaPagamentosFornecedor->listaPagamentosFornecedor[i].dataPagamento, "%d/%d/%d",
                               &dataPagamento.tm_mday, &dataPagamento.tm_mon, &dataPagamento.tm_year) != 3) {
                        continue;
                               }

                    dataPagamento.tm_year -= 1900;
                    dataPagamento.tm_mon -= 1;

                    // Converter para time_t
                    time_t tPagamento = mktime(&dataPagamento);

                    // Verificar se não está deletado, se foi finalizado e aplica os filtros
                    if (listaPagamentosFornecedor->listaPagamentosFornecedor[i].deletado == 0 &&
                        tPagamento > tAtual &&
                        listaCaixas->listaCaixas[listaPagamentosFornecedor->listaPagamentosFornecedor[i].idCaixa - 1].deletado == 0 &&
                        ((listaPagamentosFornecedor->listaPagamentosFornecedor[i].idFornecedor == fornecedor))) {
                        existePagamento = 1;
                        printf("\n====================\n"
                               "| CONTA A PAGAR %d  |\n"
                               "====================\n"
                               "VALOR: R$%.2f\n"
                               "FORNECEDOR: %s\n"
                               "OFICINA: %s\n"
                               "DATA A PAGAR: %s\n\n",
                               listaPagamentosFornecedor->listaPagamentosFornecedor[i].id,
                               listaPagamentosFornecedor->listaPagamentosFornecedor[i].valor,
                               listaFornecedores->listaFornecedores[listaPagamentosFornecedor->listaPagamentosFornecedor[i].idFornecedor - 1].nomeFantasia,
                               listaOficinas->listaOficinas[listaCaixas->listaCaixas[
                                       listaPagamentosFornecedor->listaPagamentosFornecedor[i].idCaixa - 1].idOficina - 1].
                               nome,
                               listaPagamentosFornecedor->listaPagamentosFornecedor[i].dataPagamento);
                        }
                }

                // Verifica se não há registros
                if (!existePagamento) {
                    printf("Nenhum pagamento pendente.\n\n");
                }
            }
        break;
        case 3:
            tInicial = mktime(&dataHoraInicial);
            tFinal = mktime(&dataHoraFinal);

                // Verifica se há pelo menos um registro
                if (listaCaixas->qtdCaixas > 0) {

                // Filtrando o tipo de conta do relatório
                switch (tipoConta) {
                    case 1:

                        // Exibe todos os registros
                        for (int i = 0; i < listaPagamentosCliente->qtdPagamentosCliente; i++) {

                            // Converter string para struct tm
                            if (sscanf(listaPagamentosCliente->listaPagamentosCliente[i].dataAReceber, "%d/%d/%d",
                                       &dataPagamento.tm_mday, &dataPagamento.tm_mon, &dataPagamento.tm_year) != 3) {
                                continue;
                                       }

                            dataPagamento.tm_year -= 1900;
                            dataPagamento.tm_mon -= 1;

                            // Converter para time_t
                            time_t tPagamento = mktime(&dataPagamento);

                            // Verificar se não está deletado, se foi finalizado e aplica os filtros
                            if (listaPagamentosCliente->listaPagamentosCliente[i].deletado == 0 &&
                                listaCaixas->listaCaixas[listaPagamentosCliente->listaPagamentosCliente[i].idCaixa - 1].deletado == 0 &&
                                (tPagamento >= tInicial && tPagamento <= tFinal)) {
                                existePagamento = 1;
                                printf("\n=====================\n"
                                       "| CONTA A RECEBER %d |\n"
                                       "=====================\n"
                                       "VALOR: R$%.2f\n"
                                       "CLIENTE: %s\n"
                                       "OFICINA: %s\n"
                                       "DATA A RECEBER: %s\n\n",
                                       listaPagamentosCliente->listaPagamentosCliente[i].id,
                                       listaPagamentosCliente->listaPagamentosCliente[i].valor,
                                       listaClientes->listaClientes[listaPagamentosCliente->listaPagamentosCliente[i].idCliente - 1].nome,
                                       listaOficinas->listaOficinas[listaCaixas->listaCaixas[
                                               listaPagamentosCliente->listaPagamentosCliente[i].idCaixa - 1].idOficina - 1].
                                       nome,
                                       listaPagamentosCliente->listaPagamentosCliente[i].dataAReceber);
                                }
                        }

                        // Verifica se não há registros
                        if (!existePagamento) {
                            printf("Nenhum recebimento pendente.\n\n");
                        }
                    break;
                    case 2:

                        // Exibe todos os registros
                        for (int i = 0; i < listaPagamentosFornecedor->qtdPagamentosFornecedor; i++) {

                            // Converter string para struct tm
                            if (sscanf(listaPagamentosFornecedor->listaPagamentosFornecedor[i].dataPagamento, "%d/%d/%d",
                                       &dataPagamento.tm_mday, &dataPagamento.tm_mon, &dataPagamento.tm_year) != 3) {
                                continue;
                                       }

                            dataPagamento.tm_year -= 1900;
                            dataPagamento.tm_mon -= 1;

                            // Converter para time_t
                            time_t tPagamento = mktime(&dataPagamento);

                            // Verificar se não está deletado, se foi finalizado e aplica os filtros
                            if (listaPagamentosFornecedor->listaPagamentosFornecedor[i].deletado == 0 &&
                                listaCaixas->listaCaixas[listaPagamentosFornecedor->listaPagamentosFornecedor[i].idCaixa - 1].deletado == 0 &&
                                (tPagamento >= tInicial && tPagamento <= tFinal)) {
                                existePagamento = 1;
                                printf("\n====================\n"
                                       "| CONTA A PAGAR %d  |\n"
                                       "====================\n"
                                       "VALOR: R$%.2f\n"
                                       "FORNECEDOR: %s\n"
                                       "OFICINA: %s\n"
                                       "DATA A PAGAR: %s\n\n",
                                       listaPagamentosFornecedor->listaPagamentosFornecedor[i].id,
                                       listaPagamentosFornecedor->listaPagamentosFornecedor[i].valor,
                                       listaFornecedores->listaFornecedores[listaPagamentosFornecedor->listaPagamentosFornecedor[i].idFornecedor - 1].nomeFantasia,
                                       listaOficinas->listaOficinas[listaCaixas->listaCaixas[
                                               listaPagamentosFornecedor->listaPagamentosFornecedor[i].idCaixa - 1].idOficina - 1].
                                       nome,
                                       listaPagamentosFornecedor->listaPagamentosFornecedor[i].dataPagamento);
                                }
                        }

                        // Verifica se não há registros
                        if (!existePagamento) {
                            printf("Nenhum pagamento pendente.\n\n");
                        }
                        break;
                    default:
                        break;
                }
            }
        break;
        default:

        break;

    }

}

// Armazena o relatório em arquivo
void armazenarRelatorioFinanceiro(struct ListaCaixas *listaCaixas, struct ListaOficinas *listaOficinas,
                                 struct ListaPagamentosCliente *listaPagamentosCliente,
                                 struct ListaPagamentosFornecedor *listaPagamentosFornecedor,
                                 struct ListaClientes *listaClientes,
                                 struct ListaFornecedores *listaFornecedores, int id, int tipoConta, int tipoFiltro,
                                 struct tm dataHoraInicial,
                                 struct tm dataHoraFinal) {

    // Abrindo ou criando arquivo para adicionar dados
    FILE *relatorioProdutividade;

    int existePagamento = 0, cliente = 0, fornecedor = 0;
    time_t tInicial = 0;
    time_t tFinal = 0;
    struct tm dataPagamento = {0};

    // Abrindo o arquivo de texto para escrita
    relatorioProdutividade = fopen("RelatorioFinanceiro.txt", "w");

    // Verificando se foi possível abrir o arquivo
    if (relatorioProdutividade == NULL) {
        printf("Erro: Não foi possível abrir o arquivo de texto.\n\n");
        return;
    }

    // Filtrando o relatório
    switch (tipoFiltro) {
        case 1:
            cliente = id;

        // Verifica se há pelo menos um registro
        if (listaCaixas->qtdCaixas > 0) {

            // Busca todos os registros
            for (int i = 0; i < listaPagamentosCliente->qtdPagamentosCliente; i++) {

                // Converter string para struct tm
                if (sscanf(listaPagamentosCliente->listaPagamentosCliente[i].dataAReceber, "%d/%d/%d",
                           &dataPagamento.tm_mday, &dataPagamento.tm_mon, &dataPagamento.tm_year) != 3) {
                    continue;
                           }

                dataPagamento.tm_year -= 1900;
                dataPagamento.tm_mon -= 1;

                // Converter para time_t
                time_t tPagamento = mktime(&dataPagamento);

                // Verificar se não está deletado, se foi finalizado e aplica os filtros
                if (listaPagamentosCliente->listaPagamentosCliente[i].deletado == 0 &&
                    (strcmp(listaPagamentosCliente->listaPagamentosCliente[i].dataRecebimento, "Não pago") == 0) &&
                    listaCaixas->listaCaixas[listaPagamentosCliente->listaPagamentosCliente[i].idCaixa - 1].deletado == 0 &&
                    ((listaPagamentosCliente->listaPagamentosCliente[i].idCliente == cliente))) {

                    existePagamento = 1;
                    fprintf(relatorioProdutividade,"%d;%.2f;%s;%s;%s\n",
                           listaPagamentosCliente->listaPagamentosCliente[i].id,
                           listaPagamentosCliente->listaPagamentosCliente[i].valor,
                           listaClientes->listaClientes[listaPagamentosCliente->listaPagamentosCliente[i].idCliente - 1].nome,
                           listaOficinas->listaOficinas[listaCaixas->listaCaixas[
                                   listaPagamentosCliente->listaPagamentosCliente[i].idCaixa - 1].idOficina - 1].nome,
                           listaPagamentosCliente->listaPagamentosCliente[i].dataAReceber);
                    }
            }

            // Verifica se não há registros
            if (!existePagamento) {
                printf("Nenhum recebimento pendente.\n\n");
            }
        }
        break;
        case 2:
            fornecedor = id;

        // Verifica se há pelo menos um registro
        if (listaCaixas->qtdCaixas > 0) {

            // Recebendo data e hora atual da maquina
            time_t tAtual = time(NULL);
            struct tm dataAtual = *localtime(&tAtual);
            tAtual = mktime(&dataAtual);

            // Busca todos os registros
            for (int i = 0; i < listaPagamentosFornecedor->qtdPagamentosFornecedor; i++) {

                // Converter string para struct tm
                if (sscanf(listaPagamentosFornecedor->listaPagamentosFornecedor[i].dataPagamento, "%d/%d/%d",
                           &dataPagamento.tm_mday, &dataPagamento.tm_mon, &dataPagamento.tm_year) != 3) {
                    continue;
                           }

                dataPagamento.tm_year -= 1900;
                dataPagamento.tm_mon -= 1;

                // Converter para time_t
                time_t tPagamento = mktime(&dataPagamento);

                // Verificar se não está deletado, se foi finalizado e aplica os filtros
                if (listaPagamentosFornecedor->listaPagamentosFornecedor[i].deletado == 0 &&
                    tPagamento > tAtual &&
                    listaCaixas->listaCaixas[listaPagamentosFornecedor->listaPagamentosFornecedor[i].idCaixa - 1].deletado == 0 &&
                    ((listaPagamentosFornecedor->listaPagamentosFornecedor[i].idFornecedor == fornecedor))) {

                    existePagamento = 1;
                    fprintf(relatorioProdutividade,"%d;%.2f;%s;%s;%s\n",
                           listaPagamentosFornecedor->listaPagamentosFornecedor[i].id,
                           listaPagamentosFornecedor->listaPagamentosFornecedor[i].valor,
                           listaFornecedores->listaFornecedores[listaPagamentosFornecedor->listaPagamentosFornecedor[i].idFornecedor - 1].nomeFantasia,
                           listaOficinas->listaOficinas[listaCaixas->listaCaixas[
                                   listaPagamentosFornecedor->listaPagamentosFornecedor[i].idCaixa - 1].idOficina - 1].nome,
                           listaPagamentosFornecedor->listaPagamentosFornecedor[i].dataPagamento);
                    }
            }

            // Verifica se não há registros
            if (!existePagamento) {
                printf("Nenhum pagamento pendente.\n\n");
            }
        }
        break;
        case 3:
            tInicial = mktime(&dataHoraInicial);
            tFinal = mktime(&dataHoraFinal);

            // Verifica se há pelo menos um registro
            if (listaCaixas->qtdCaixas > 0) {
                switch (tipoConta) {

                    case 1:
                        // Busca todos os registros
                        for (int i = 0; i < listaPagamentosCliente->qtdPagamentosCliente; i++) {

                            if (sscanf(listaPagamentosCliente->listaPagamentosCliente[i].dataAReceber, "%d/%d/%d",
                                       &dataPagamento.tm_mday, &dataPagamento.tm_mon, &dataPagamento.tm_year) != 3) {
                                continue;
                                       }

                            dataPagamento.tm_year -= 1900;
                            dataPagamento.tm_mon -= 1;

                            // Converter para time_t
                            time_t tPagamento = mktime(&dataPagamento);

                            // Verificar se não está deletado, se foi finalizado e aplica os filtros
                            if (listaPagamentosCliente->listaPagamentosCliente[i].deletado == 0 &&
                                listaCaixas->listaCaixas[listaPagamentosCliente->listaPagamentosCliente[i].idCaixa - 1].deletado == 0 &&
                                (tPagamento >= tInicial && tPagamento <= tFinal))  {

                                existePagamento = 1;
                                fprintf(relatorioProdutividade,"%d;%.2f;%s;%s;%s\n",
                                       listaPagamentosCliente->listaPagamentosCliente[i].id,
                                       listaPagamentosCliente->listaPagamentosCliente[i].valor,
                                       listaClientes->listaClientes[listaPagamentosCliente->listaPagamentosCliente[i].idCliente - 1].nome,
                                       listaOficinas->listaOficinas[listaCaixas->listaCaixas[
                                               listaPagamentosCliente->listaPagamentosCliente[i].idCaixa - 1].idOficina - 1].
                                       nome,
                                       listaPagamentosCliente->listaPagamentosCliente[i].dataAReceber);
                                }
                        }

                        // Verifica se não há registros
                        if (!existePagamento) {
                            printf("Nenhum recebimento pendente.\n\n");
                        }
                    break;
                    case 2:

                        for (int i = 0; i < listaPagamentosFornecedor->qtdPagamentosFornecedor; i++) {

                            // Converter string para struct tm
                            if (sscanf(listaPagamentosFornecedor->listaPagamentosFornecedor[i].dataPagamento, "%d/%d/%d",
                                       &dataPagamento.tm_mday, &dataPagamento.tm_mon, &dataPagamento.tm_year) != 3) {
                                continue;
                                       }

                            dataPagamento.tm_year -= 1900;
                            dataPagamento.tm_mon -= 1;

                            // Converter para time_t
                            time_t tPagamento = mktime(&dataPagamento);

                            // Verificar se não está deletado, se foi finalizado e aplica os filtros
                            if (listaPagamentosFornecedor->listaPagamentosFornecedor[i].deletado == 0 &&
                                listaCaixas->listaCaixas[listaPagamentosFornecedor->listaPagamentosFornecedor[i].idCaixa - 1].deletado == 0 &&
                                (tPagamento >= tInicial && tPagamento <= tFinal)) {

                                existePagamento = 1;
                                fprintf(relatorioProdutividade, "%d;%.2f;%s;%s;%s\n",
                                       listaPagamentosFornecedor->listaPagamentosFornecedor[i].id,
                                       listaPagamentosFornecedor->listaPagamentosFornecedor[i].valor,
                                       listaFornecedores->listaFornecedores[listaPagamentosFornecedor->listaPagamentosFornecedor[i].idFornecedor - 1].nomeFantasia,
                                       listaOficinas->listaOficinas[listaCaixas->listaCaixas[
                                               listaPagamentosFornecedor->listaPagamentosFornecedor[i].idCaixa - 1].idOficina - 1].
                                       nome,
                                       listaPagamentosFornecedor->listaPagamentosFornecedor[i].dataPagamento);
                                }
                        }

                        // Verifica se não há registros
                        if (!existePagamento) {
                            printf("Nenhum pagamento pendente.\n\n");
                        }
                        break;
                    default:
                        break;
                }
            }
        break;
        default:

        break;

    }

    if (existePagamento) {
        printf("Relatório armazenado com sucesso.\n\n");
    }

    // Fechando o arquivo
    fclose(relatorioProdutividade);
}
