#include "modelRelatorioOrdensServicos.h"

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
void imprimirRelatorioOrdensServicos(struct ListaPecas *listaPecas, struct ListaClientes *listaClientes,
                              struct ListaServicos *listaServicos,
                              struct ListaAgendamentos *listaAgendamentos,
                              struct ListaOrdensServico *listaOrdensServicos,
                              struct ListaFuncionarios *listaFuncionarios,
                              struct ListaVeiculos *listaVeiculos,
                              struct tm dataInicial, struct tm dataFinal, int tipo,
                              int id) {
    // Variavel de verificação de estoque
    int existeEstoque = 0;


    // Verifica se há pelo menos um registro
    if (listaPecas->qtdPecas > 0) {
        existeEstoque = 1;
        switch (tipo) {
            case 1:
            // Listagem baseada nas peças utilizadas no serviço
                for (int i = 0; i < listaPecas->qtdPecas; i++) {
                    for (int j = 0; j < listaOrdensServicos->qtdOrdensServico; j++) {
                        for (int k = 0; k < listaServicos->qtdServicos; k++) {
                            for (int l = 0; l < listaAgendamentos->qtdAgendamentos; l++) {
                                if (listaPecas->listaPecas[i].deletado == 0 && listaServicos->listaServicos[k].id == id &&
                                    listaOrdensServicos->listaOrdensServico[j].idPecas == listaPecas->listaPecas[i].id
                                    && listaAgendamentos->listaAgendamentos[l].id == listaOrdensServicos->listaOrdensServico[j].idAgendamento
                                    && listaAgendamentos->listaAgendamentos[l].idServico == listaServicos->listaServicos[k].id) {
                                    printf("\n====================\n"
                                       "| PEÇA %d           |\n"
                                       "====================\n"
                                       "DESCRIÇÃO: %s\n"
                                       "FABRICANTE: %s\n"
                                       "PREÇO DE CUSTO: $%.2f\n"
                                       "PREÇO DE VENDA: $%.2f\n"
                                       "QUANTIDADE EM ESTOQUE: %d\n"
                                       "QUANTIDADE UTILIZADA: %d\n"
                                       "SERVIÇO: %s\n\n",
                                       listaPecas->listaPecas[i].id,
                                       listaPecas->listaPecas[i].descricao,
                                       listaPecas->listaPecas[i].fabricante,
                                       listaPecas->listaPecas[i].precoCusto,
                                       listaPecas->listaPecas[i].precoVenda,
                                       listaPecas->listaPecas[i].qtdEstoque,
                                       listaOrdensServicos->listaOrdensServico[j].qtdPecas,
                                       listaServicos->listaServicos[k].descricao);
                                    }
                            }
                        }
                    }
                }
            break;
            case 2:
                // Listagem baseada nas peças requisitadas pelo cliente
                for (int i = 0; i < listaPecas->qtdPecas; i++) {
                    for (int j = 0; j < listaOrdensServicos->qtdOrdensServico; j++) {
                        for (int k = 0; k < listaClientes->qtdClientes; k++) {
                            for (int l = 0; l < listaAgendamentos->qtdAgendamentos; l++) {
                                for (int m = 0; m < listaVeiculos->qtdVeiculos; m++) {
                                    if (listaPecas->listaPecas[i].deletado == 0 && listaClientes->listaClientes[k].id == id &&
                                        listaVeiculos->listaVeiculos[m].idProprietario == listaClientes->listaClientes[k].id
                                        && listaAgendamentos->listaAgendamentos[l].idVeiculo == listaVeiculos->listaVeiculos[m].id
                                        && listaOrdensServicos->listaOrdensServico[j].idAgendamento == listaAgendamentos->listaAgendamentos[l].id
                                        && listaOrdensServicos->listaOrdensServico[j].idPecas == listaPecas->listaPecas[i].id) {

                                        printf("\n====================\n"
                                           "| PEÇA %d           |\n"
                                           "====================\n"
                                           "DESCRIÇÃO: %s\n"
                                           "FABRICANTE: %s\n"
                                           "PREÇO DE CUSTO: $%.2f\n"
                                           "PREÇO DE VENDA: $%.2f\n"
                                           "QUANTIDADE EM ESTOQUE: %d\n"
                                           "QUANTIDADE UTILIZADA: %d\n"
                                           "CLIENTE: %s\n\n",
                                           listaPecas->listaPecas[i].id,
                                           listaPecas->listaPecas[i].descricao,
                                           listaPecas->listaPecas[i].fabricante,
                                           listaPecas->listaPecas[i].precoCusto,
                                           listaPecas->listaPecas[i].precoVenda,
                                           listaPecas->listaPecas[i].qtdEstoque,
                                           listaOrdensServicos->listaOrdensServico[j].qtdPecas,
                                           listaClientes->listaClientes[k].nome);
                                        }
                                }
                            }
                        }
                    }
                }
                break;
            case 3:
                // Listagem baseada nas peças utilizadas pelo funcionário
                for (int i = 0; i < listaPecas->qtdPecas; i++) {
                    for (int j = 0; j < listaOrdensServicos->qtdOrdensServico; j++) {
                        for (int k = 0; k < listaFuncionarios->qtdFuncionarios; k++) {
                            for (int l = 0; l < listaAgendamentos->qtdAgendamentos; l++) {
                                if (listaPecas->listaPecas[i].deletado == 0 && listaFuncionarios->listaFuncionarios[k].id == id &&
                                    listaOrdensServicos->listaOrdensServico[j].idPecas == listaPecas->listaPecas[i].id
                                    && listaAgendamentos->listaAgendamentos[l].id == listaOrdensServicos->listaOrdensServico[j].idAgendamento
                                    && listaAgendamentos->listaAgendamentos[l].idFuncionario == listaFuncionarios->listaFuncionarios[k].id) {

                                    printf("\n====================\n"
                                       "| PEÇA %d           |\n"
                                       "====================\n"
                                       "DESCRIÇÃO: %s\n"
                                       "FABRICANTE: %s\n"
                                       "PREÇO DE CUSTO: $%.2f\n"
                                       "PREÇO DE VENDA: $%.2f\n"
                                       "QUANTIDADE EM ESTOQUE: %d\n"
                                       "QUANTIDADE UTILIZADA: %d\n"
                                       "FUNCIONÁRIO: %s\n\n",
                                       listaPecas->listaPecas[i].id,
                                       listaPecas->listaPecas[i].descricao,
                                       listaPecas->listaPecas[i].fabricante,
                                       listaPecas->listaPecas[i].precoCusto,
                                       listaPecas->listaPecas[i].precoVenda,
                                       listaPecas->listaPecas[i].qtdEstoque,
                                       listaOrdensServicos->listaOrdensServico[j].qtdPecas,
                                       listaFuncionarios->listaFuncionarios[k].nome);
                                    }
                            }
                        }
                    }
                }
                break;
            case 4:
                // Listagem baseada nas peças utilizadas em determinado intervalo de datas
                char *token;
                token = malloc (sizeof(listaAgendamentos->listaAgendamentos->datahoraInicial));
                for (int i = 0; i < listaPecas->qtdPecas; i++) {
                    for (int j = 0; j < listaOrdensServicos->qtdOrdensServico; j++) {
                        for (int l = 0; l < listaAgendamentos->qtdAgendamentos; l++) {
                            if (listaPecas->listaPecas[i].deletado == 0 &&
                                listaOrdensServicos->listaOrdensServico[j].idPecas == listaPecas->listaPecas[i].id
                                && listaAgendamentos->listaAgendamentos[l].id == listaOrdensServicos->listaOrdensServico[j].idAgendamento) {
                                int diaVenda, mesVenda, anoVenda;

                                token = strcpy(token, listaAgendamentos->listaAgendamentos[l].datahoraInicial);
                                token = strtok(token, "/");

                                if (token != NULL) {
                                    diaVenda = atoi(token);
                                    token = strtok(NULL, "/");
                                }
                                if (token != NULL) {
                                    mesVenda = atoi(token);
                                    token = strtok(NULL, " ");
                                }
                                if (token != NULL) {
                                    anoVenda = atoi(token);
                                }
                                if (anoVenda > dataInicial.tm_year && anoVenda < dataFinal.tm_year) {
                                    printf("\n====================\n"
                                       "| PEÇA %d           |\n"
                                       "====================\n"
                                       "DESCRIÇÃO: %s\n"
                                       "FABRICANTE: %s\n"
                                       "PREÇO DE CUSTO: $%.2f\n"
                                       "PREÇO DE VENDA: $%.2f\n"
                                       "QUANTIDADE EM ESTOQUE: %d\n"
                                       "ESTOQUE MÍNIMO: %d\n"
                                       "DATA DE USO: %s\n\n",
                                       listaPecas->listaPecas[i].id,
                                       listaPecas->listaPecas[i].descricao,
                                       listaPecas->listaPecas[i].fabricante,
                                       listaPecas->listaPecas[i].precoCusto,
                                       listaPecas->listaPecas[i].precoVenda,
                                       listaPecas->listaPecas[i].qtdEstoque,
                                       listaOrdensServicos->listaOrdensServico[j].qtdPecas,
                                       listaAgendamentos->listaAgendamentos[j].datahoraInicial);
                                }
                                else if (anoVenda == dataInicial.tm_year && mesVenda > dataInicial.tm_mon || anoVenda ==
                                         dataFinal.tm_year && mesVenda < dataFinal.tm_mon) {

                                    printf("\n====================\n"
                                       "| PEÇA %d           |\n"
                                       "====================\n"
                                       "DESCRIÇÃO: %s\n"
                                       "FABRICANTE: %s\n"
                                       "PREÇO DE CUSTO: $%.2f\n"
                                       "PREÇO DE VENDA: $%.2f\n"
                                       "QUANTIDADE EM ESTOQUE: %d\n"
                                       "ESTOQUE MÍNIMO: %d\n"
                                       "DATA DE USO: %s\n\n",
                                       listaPecas->listaPecas[i].id,
                                       listaPecas->listaPecas[i].descricao,
                                       listaPecas->listaPecas[i].fabricante,
                                       listaPecas->listaPecas[i].precoCusto,
                                       listaPecas->listaPecas[i].precoVenda,
                                       listaPecas->listaPecas[i].qtdEstoque,
                                       listaOrdensServicos->listaOrdensServico[j].qtdPecas,
                                       listaAgendamentos->listaAgendamentos[j].datahoraInicial);
                                }
                                else if (anoVenda == dataInicial.tm_year && mesVenda == dataInicial.tm_mon && diaVenda
                                         >= dataInicial.tm_mday || anoVenda == dataFinal.tm_year && mesVenda == dataFinal
                                         .tm_mon && diaVenda <= dataFinal.tm_mday) {
                                    printf("\n====================\n"
                                       "| PEÇA %d           |\n"
                                       "====================\n"
                                       "DESCRIÇÃO: %s\n"
                                       "FABRICANTE: %s\n"
                                       "PREÇO DE CUSTO: $%.2f\n"
                                       "PREÇO DE VENDA: $%.2f\n"
                                       "QUANTIDADE EM ESTOQUE: %d\n"
                                       "ESTOQUE MÍNIMO: %d\n"
                                       "DATA DE USO: %s\n\n",
                                       listaPecas->listaPecas[i].id,
                                       listaPecas->listaPecas[i].descricao,
                                       listaPecas->listaPecas[i].fabricante,
                                       listaPecas->listaPecas[i].precoCusto,
                                       listaPecas->listaPecas[i].precoVenda,
                                       listaPecas->listaPecas[i].qtdEstoque,
                                       listaOrdensServicos->listaOrdensServico[j].qtdPecas,
                                       listaAgendamentos->listaAgendamentos[j].datahoraInicial);

                                }
                            }
                        }
                    }
                }
                token = NULL;
                free(token);

                break;
            case 5:
                // Listagem baseada nas peças abaixo do estoque mínimo
                int temEstoqueMinimo = 1;
                for (int i = 0; i < listaPecas->qtdPecas; i++) {
                    if (listaPecas->listaPecas[i].deletado == 0 && listaPecas->listaPecas[i].qtdEstoque < listaPecas->
                        listaPecas[i].estoqueMinimo) {
                        temEstoqueMinimo = 0;
                        printf("\n====================\n"
                           "| PEÇA %d           |\n"
                           "====================\n"
                           "DESCRIÇÃO: %s\n"
                           "FABRICANTE: %s\n"
                           "PREÇO DE CUSTO: $%.2f\n"
                           "PREÇO DE VENDA: $%.2f\n"
                           "QUANTIDADE EM ESTOQUE: %d\n"
                           "ESTOQUE MÍNIMO: %d\n\n",
                           listaPecas->listaPecas[i].id,
                           listaPecas->listaPecas[i].descricao,
                           listaPecas->listaPecas[i].fabricante,
                           listaPecas->listaPecas[i].precoCusto,
                           listaPecas->listaPecas[i].precoVenda,
                           listaPecas->listaPecas[i].qtdEstoque,
                           listaPecas->listaPecas[i].estoqueMinimo);
                    }
                }
                if (!temEstoqueMinimo) {
                    printf("Nenhuma peça está abaixo do estoque mínimo!\n\n");
                }
                break;
            default:
                break;
        }
    }

    // Verifica se não há registros
    if (!existeEstoque) {
        printf("Nenhuma peça foi cadastrado.\n\n");
    }
}

// Armazena o relatório em arquivo
void armazenarRelatorioOrdensServicos(struct ListaPecas *listaPecas, struct ListaClientes *listaClientes,
                              struct ListaServicos *listaServicos,
                              struct ListaAgendamentos *listaAgendamentos,
                              struct ListaOrdensServico *listaOrdensServicos,
                              struct ListaFuncionarios *listaFuncionarios,
                              struct ListaVeiculos *listaVeiculos,
                              struct tm dataInicial, struct tm dataFinal, int tipo,
                              int id) {
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
            for (int i = 0; i < listaPecas->qtdPecas; i++) {
                for (int j = 0; j < listaOrdensServicos->qtdOrdensServico; j++) {
                    for (int k = 0; k < listaServicos->qtdServicos; k++) {
                        for (int l = 0; l < listaAgendamentos->qtdAgendamentos; l++) {
                            if (listaPecas->listaPecas[i].deletado == 0 && listaServicos->listaServicos[k].id == id &&
                                listaOrdensServicos->listaOrdensServico[j].idPecas == listaPecas->listaPecas[i].id
                                && listaAgendamentos->listaAgendamentos[l].id == listaOrdensServicos->listaOrdensServico[j].idAgendamento
                                && listaAgendamentos->listaAgendamentos[l].idServico == listaServicos->listaServicos[k].id) {

                                fprintf(relatorioEstoque, "%d;%s;%s;%.2f;%.2f;%d;%d;%s\n",
                                    listaPecas->listaPecas[i].id,
                                    listaPecas->listaPecas[i].descricao,
                                    listaPecas->listaPecas[i].fabricante,
                                    listaPecas->listaPecas[i].precoCusto,
                                    listaPecas->listaPecas[i].precoVenda,
                                    listaPecas->listaPecas[i].qtdEstoque,
                                    listaOrdensServicos->listaOrdensServico[j].qtdPecas,
                                    listaServicos->listaServicos[k].descricao);
                                }
                            }
                        }
                    }
                }
        break;
        case 2:

            for (int i = 0; i < listaPecas->qtdPecas; i++) {
                for (int j = 0; j < listaOrdensServicos->qtdOrdensServico; j++) {
                    for (int k = 0; k < listaClientes->qtdClientes; k++) {
                        for (int l = 0; l < listaAgendamentos->qtdAgendamentos; l++) {
                            for (int m = 0; m < listaVeiculos->qtdVeiculos; m++) {
                                if (listaPecas->listaPecas[i].deletado == 0 && listaClientes->listaClientes[k].id == id &&
                                    listaVeiculos->listaVeiculos[m].idProprietario == listaClientes->listaClientes[k].id
                                    && listaAgendamentos->listaAgendamentos[l].idVeiculo == listaVeiculos->listaVeiculos[m].id
                                    && listaOrdensServicos->listaOrdensServico[j].idAgendamento == listaAgendamentos->listaAgendamentos[l].id
                                    && listaOrdensServicos->listaOrdensServico[j].idPecas == listaPecas->listaPecas[i].id) {

                                    fprintf(relatorioEstoque, "%d;%s;%s;%.2f;%.2f;%d;%d;%s\n",
                                        listaPecas->listaPecas[i].id,
                                        listaPecas->listaPecas[i].descricao,
                                        listaPecas->listaPecas[i].fabricante,
                                        listaPecas->listaPecas[i].precoCusto,
                                        listaPecas->listaPecas[i].precoVenda,
                                        listaPecas->listaPecas[i].qtdEstoque,
                                        listaOrdensServicos->listaOrdensServico[j].qtdPecas,
                                        listaClientes->listaClientes[k].nome);
                                    }
                            }
                        }
                    }
                }
            }
            break;
            case 3:

                for (int i = 0; i < listaPecas->qtdPecas; i++) {
                    for (int j = 0; j < listaOrdensServicos->qtdOrdensServico; j++) {
                        for (int k = 0; k < listaFuncionarios->qtdFuncionarios; k++) {
                            for (int l = 0; l < listaAgendamentos->qtdAgendamentos; l++) {
                                if (listaPecas->listaPecas[i].deletado == 0 && listaFuncionarios->listaFuncionarios[k].id == id &&
                                    listaOrdensServicos->listaOrdensServico[j].idPecas == listaPecas->listaPecas[i].id
                                    && listaAgendamentos->listaAgendamentos[l].id == listaOrdensServicos->listaOrdensServico[j].idAgendamento
                                    && listaAgendamentos->listaAgendamentos[l].idFuncionario == listaFuncionarios->listaFuncionarios[k].id) {

                                    fprintf(relatorioEstoque, "%d;%s;%s;%.2f;%.2f;%d;%d;%s\n",
                                        listaPecas->listaPecas[i].id,
                                        listaPecas->listaPecas[i].descricao,
                                        listaPecas->listaPecas[i].fabricante,
                                        listaPecas->listaPecas[i].precoCusto,
                                        listaPecas->listaPecas[i].precoVenda,
                                        listaPecas->listaPecas[i].qtdEstoque,
                                        listaOrdensServicos->listaOrdensServico[j].qtdPecas,
                                        listaFuncionarios->listaFuncionarios[k].nome);
                                    }
                            }
                        }
                    }
                }
                break;
            case 4:
                char *token;
                token = malloc (sizeof(listaAgendamentos->listaAgendamentos->datahoraInicial));

                for (int i = 0; i < listaPecas->qtdPecas; i++) {
                    for (int j = 0; j < listaOrdensServicos->qtdOrdensServico; j++) {
                        for (int l = 0; l < listaAgendamentos->qtdAgendamentos; l++) {
                            if (listaPecas->listaPecas[i].deletado == 0 &&
                                listaOrdensServicos->listaOrdensServico[j].idPecas == listaPecas->listaPecas[i].id
                                && listaAgendamentos->listaAgendamentos[l].id == listaOrdensServicos->listaOrdensServico[j].idAgendamento) {
                                int diaVenda, mesVenda, anoVenda;

                                token = strcpy(token, listaAgendamentos->listaAgendamentos[l].datahoraInicial);
                                token = strtok(token, "/");

                                if (token != NULL) {
                                    diaVenda = atoi(token);
                                    token = strtok(NULL, "/");
                                }
                                if (token != NULL) {
                                    mesVenda = atoi(token);
                                    token = strtok(NULL, " ");
                                }
                                if (token != NULL) {
                                    anoVenda = atoi(token);
                                }

                                if (anoVenda > dataInicial.tm_year && anoVenda < dataFinal.tm_year) {

                                    fprintf(relatorioEstoque, "%d;%s;%s;%.2f;%.2f;%d;%d;%s\n",
                                    listaPecas->listaPecas[i].id,
                                    listaPecas->listaPecas[i].descricao,
                                    listaPecas->listaPecas[i].fabricante,
                                    listaPecas->listaPecas[i].precoCusto,
                                    listaPecas->listaPecas[i].precoVenda,
                                    listaPecas->listaPecas[i].qtdEstoque,
                                    listaOrdensServicos->listaOrdensServico[j].qtdPecas,
                                    listaAgendamentos->listaAgendamentos[l].datahoraInicial);

                                }
                                else if (anoVenda == dataInicial.tm_year && mesVenda > dataInicial.tm_mon || anoVenda ==
                                         dataFinal.tm_year && mesVenda < dataFinal.tm_mon) {

                                    fprintf(relatorioEstoque, "%d;%s;%s;%.2f;%.2f;%d;%d;%s\n",
                                        listaPecas->listaPecas[i].id,
                                        listaPecas->listaPecas[i].descricao,
                                        listaPecas->listaPecas[i].fabricante,
                                        listaPecas->listaPecas[i].precoCusto,
                                        listaPecas->listaPecas[i].precoVenda,
                                        listaPecas->listaPecas[i].qtdEstoque,
                                        listaOrdensServicos->listaOrdensServico[j].qtdPecas,
                                        listaAgendamentos->listaAgendamentos[l].datahoraInicial);

                                }
                                else if (anoVenda == dataInicial.tm_year && mesVenda == dataInicial.tm_mon && diaVenda
                                         >= dataInicial.tm_mday || anoVenda == dataFinal.tm_year && mesVenda == dataFinal
                                         .tm_mon && diaVenda <= dataFinal.tm_mday) {

                                    fprintf(relatorioEstoque, "%d;%s;%s;%.2f;%.2f;%d;%d;%s\n",
                                        listaPecas->listaPecas[i].id,
                                        listaPecas->listaPecas[i].descricao,
                                        listaPecas->listaPecas[i].fabricante,
                                        listaPecas->listaPecas[i].precoCusto,
                                        listaPecas->listaPecas[i].precoVenda,
                                        listaPecas->listaPecas[i].qtdEstoque,
                                        listaOrdensServicos->listaOrdensServico[j].qtdPecas,
                                        listaAgendamentos->listaAgendamentos[l].datahoraInicial);
                                }
                            }
                        }
                    }
                }
                token = NULL;
                free(token);

                break;
            case 5:
                int temEstoqueMinimo = 1;
                for (int i = 0; i < listaPecas->qtdPecas; i++) {
                    if (listaPecas->listaPecas[i].deletado == 0 && listaPecas->listaPecas[i].qtdEstoque < listaPecas->
                        listaPecas[i].estoqueMinimo) {
                        temEstoqueMinimo = 0;
                        fprintf(relatorioEstoque, "%d;%s;%s;%.2f;%.2f;%d;%d\n",
                                    listaPecas->listaPecas[i].id,
                                    listaPecas->listaPecas[i].descricao,
                                    listaPecas->listaPecas[i].fabricante,
                                    listaPecas->listaPecas[i].precoCusto,
                                    listaPecas->listaPecas[i].precoVenda,
                                    listaPecas->listaPecas[i].qtdEstoque,
                                    listaPecas->listaPecas[i].estoqueMinimo);
                    }
                }
                if (!temEstoqueMinimo) {
                    printf("Nenhuma peça está abaixo do estoque mínimo!\n\n");
                }
                break;
            default:
                break;
    }

    printf("Relatório de estoques realizado com sucesso!\n\n");

    // Fechando o arquivo
    fclose(relatorioEstoque);
}
