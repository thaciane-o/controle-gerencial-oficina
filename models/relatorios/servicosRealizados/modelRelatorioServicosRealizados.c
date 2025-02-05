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
void imprimirRelatorioServicosRealizados(struct ListaClientes *listaClientes,
                              struct ListaServicos *listaServicos,
                              struct ListaAgendamentos *listaAgendamentos,
                              struct ListaFuncionarios *listaFuncionarios,
                              struct ListaVeiculos *listaVeiculos,
                              struct tm dataInicial, struct tm dataFinal, int tipo,
                              int id) {
    // Variavel de verificação de estoque
    int existeServico = 0;


    // Verifica se há pelo menos um registro
    if (listaServicos->qtdServicos > 0) {
        existeServico = 1;
        switch (tipo) {
            case 1:
            // Listagem baseada nas peças utilizadas no serviço
                for (int i = 0; i < listaServicos->qtdServicos; i++) {
                    for (int j = 0; j < listaFuncionarios->qtdFuncionarios; j++) {
                        for (int k = 0; k < listaVeiculos->qtdVeiculos; k++) {
                            for (int l = 0; l < listaAgendamentos->qtdAgendamentos; l++) {
                                for (int m = 0; m < listaClientes->qtdClientes; m++) {
                                    if (listaServicos->listaServicos[i].deletado == 0 && listaServicos->listaServicos[i].id == id &&
                                        listaAgendamentos->listaAgendamentos[l].idFuncionario == listaFuncionarios->listaFuncionarios[j].id &&
                                        listaAgendamentos->listaAgendamentos[l].idVeiculo == listaVeiculos->listaVeiculos[k].id &&
                                        listaVeiculos->listaVeiculos[k].idProprietario == listaClientes->listaClientes[m].id &&
                                        listaAgendamentos->listaAgendamentos[l].idServico == listaServicos->listaServicos[i].id) {
                                        printf("\n====================\n"
                                           "| SERVIÇO REALIZADO %d |\n"
                                           "====================\n"
                                           "DESCRIÇÃO: %s\n"
                                           "PREÇO: $%.2f\n"
                                           "COMISSÃO: $%.2f\n"
                                           "CLIENTE: %s\n"
                                           "FUNCIONARIO: %s\n"
                                           "DATA: %s\n",
                                           listaServicos->listaServicos[i].id,
                                           listaServicos->listaServicos[i].descricao,
                                           listaServicos->listaServicos[i].preco,
                                           listaServicos->listaServicos[i].comissao,
                                           listaClientes->listaClientes[m].nome,
                                           listaFuncionarios->listaFuncionarios[j].nome,
                                           listaAgendamentos->listaAgendamentos[l].datahoraInicial);
                                        }
                                }
                            }
                        }
                    }
                }
            break;
            case 2:
                // Listagem baseada nas peças requisitadas pelo cliente
                for (int i = 0; i < listaServicos->qtdServicos; i++) {
                    for (int j = 0; j < listaFuncionarios->qtdFuncionarios; j++) {
                        for (int k = 0; k < listaVeiculos->qtdVeiculos; k++) {
                            for (int l = 0; l < listaAgendamentos->qtdAgendamentos; l++) {
                                for (int m = 0; m < listaClientes->qtdClientes; m++) {
                                    if (listaServicos->listaServicos[i].deletado == 0 && listaClientes->listaClientes[m].id == id &&
                                        listaAgendamentos->listaAgendamentos[l].idFuncionario == listaFuncionarios->listaFuncionarios[j].id &&
                                        listaAgendamentos->listaAgendamentos[l].idVeiculo == listaVeiculos->listaVeiculos[k].id &&
                                        listaVeiculos->listaVeiculos[k].idProprietario == listaClientes->listaClientes[m].id &&
                                        listaAgendamentos->listaAgendamentos[l].idServico == listaServicos->listaServicos[i].id) {
                                        printf("\n====================\n"
                                           "| SERVIÇO REALIZADO %d |\n"
                                           "====================\n"
                                           "DESCRIÇÃO: %s\n"
                                           "PREÇO: $%.2f\n"
                                           "COMISSÃO: $%.2f\n"
                                           "CLIENTE: %s\n"
                                           "FUNCIONARIO: %s\n"
                                           "DATA: %s\n",
                                           listaServicos->listaServicos[i].id,
                                           listaServicos->listaServicos[i].descricao,
                                           listaServicos->listaServicos[i].preco,
                                           listaServicos->listaServicos[i].comissao,
                                           listaClientes->listaClientes[m].nome,
                                           listaFuncionarios->listaFuncionarios[j].nome,
                                           listaAgendamentos->listaAgendamentos[l].datahoraInicial);
                                        }
                                }
                            }
                        }
                    }
                }
                break;
            case 3:
                // Listagem baseada nas peças utilizadas pelo funcionário
                for (int i = 0; i < listaServicos->qtdServicos; i++) {
                    for (int j = 0; j < listaFuncionarios->qtdFuncionarios; j++) {
                        for (int k = 0; k < listaVeiculos->qtdVeiculos; k++) {
                            for (int l = 0; l < listaAgendamentos->qtdAgendamentos; l++) {
                                for (int m = 0; m < listaClientes->qtdClientes; m++) {
                                    if (listaServicos->listaServicos[i].deletado == 0 && listaFuncionarios->listaFuncionarios[j].id == id &&
                                        listaAgendamentos->listaAgendamentos[l].idFuncionario == listaFuncionarios->listaFuncionarios[j].id &&
                                        listaAgendamentos->listaAgendamentos[l].idVeiculo == listaVeiculos->listaVeiculos[k].id &&
                                        listaVeiculos->listaVeiculos[k].idProprietario == listaClientes->listaClientes[m].id &&
                                        listaAgendamentos->listaAgendamentos[l].idServico == listaServicos->listaServicos[i].id) {
                                        printf("\n====================\n"
                                           "| SERVIÇO REALIZADO %d |\n"
                                           "====================\n"
                                           "DESCRIÇÃO: %s\n"
                                           "PREÇO: $%.2f\n"
                                           "COMISSÃO: $%.2f\n"
                                           "CLIENTE: %s\n"
                                           "FUNCIONARIO: %s\n"
                                           "DATA: %s\n",
                                           listaServicos->listaServicos[i].id,
                                           listaServicos->listaServicos[i].descricao,
                                           listaServicos->listaServicos[i].preco,
                                           listaServicos->listaServicos[i].comissao,
                                           listaClientes->listaClientes[m].nome,
                                           listaFuncionarios->listaFuncionarios[j].nome,
                                           listaAgendamentos->listaAgendamentos[l].datahoraInicial);
                                        }
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
                for (int i = 0; i < listaServicos->qtdServicos; i++) {
                    for (int j = 0; j < listaFuncionarios->qtdFuncionarios; j++) {
                        for (int k = 0; k < listaVeiculos->qtdVeiculos; k++) {
                            for (int l = 0; l < listaAgendamentos->qtdAgendamentos; l++) {
                                for (int m = 0; m < listaClientes->qtdClientes; m++) {
                                    if (listaServicos->listaServicos[i].deletado == 0 &&
                                        listaAgendamentos->listaAgendamentos[l].idFuncionario == listaFuncionarios->listaFuncionarios[j].id &&
                                        listaAgendamentos->listaAgendamentos[l].idVeiculo == listaVeiculos->listaVeiculos[k].id &&
                                        listaVeiculos->listaVeiculos[k].idProprietario == listaClientes->listaClientes[m].id &&
                                        listaAgendamentos->listaAgendamentos[l].idServico == listaServicos->listaServicos[i].id) {
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
                                                   "| SERVIÇO REALIZADO %d |\n"
                                                   "====================\n"
                                                   "DESCRIÇÃO: %s\n"
                                                   "PREÇO: $%.2f\n"
                                                   "COMISSÃO: $%.2f\n"
                                                   "CLIENTE: %s\n"
                                                   "FUNCIONARIO: %s\n"
                                                   "DATA: %s\n",
                                                   listaServicos->listaServicos[i].id,
                                                   listaServicos->listaServicos[i].descricao,
                                                   listaServicos->listaServicos[i].preco,
                                                   listaServicos->listaServicos[i].comissao,
                                                   listaClientes->listaClientes[m].nome,
                                                   listaFuncionarios->listaFuncionarios[j].nome,
                                                   listaAgendamentos->listaAgendamentos[l].datahoraInicial);
                                        }
                                        else if (anoVenda == dataInicial.tm_year && mesVenda > dataInicial.tm_mon || anoVenda ==
                                                 dataFinal.tm_year && mesVenda < dataFinal.tm_mon) {

                                            printf("\n====================\n"
                                                   "| SERVIÇO REALIZADO %d |\n"
                                                   "====================\n"
                                                   "DESCRIÇÃO: %s\n"
                                                   "PREÇO: $%.2f\n"
                                                   "COMISSÃO: $%.2f\n"
                                                   "CLIENTE: %s\n"
                                                   "FUNCIONARIO: %s\n"
                                                   "DATA: %s\n",
                                                   listaServicos->listaServicos[i].id,
                                                   listaServicos->listaServicos[i].descricao,
                                                   listaServicos->listaServicos[i].preco,
                                                   listaServicos->listaServicos[i].comissao,
                                                   listaClientes->listaClientes[m].nome,
                                                   listaFuncionarios->listaFuncionarios[j].nome,
                                                   listaAgendamentos->listaAgendamentos[l].datahoraInicial);
                                                 }
                                        else if (anoVenda == dataInicial.tm_year && mesVenda == dataInicial.tm_mon && diaVenda
                                                 >= dataInicial.tm_mday || anoVenda == dataFinal.tm_year && mesVenda == dataFinal
                                                 .tm_mon && diaVenda <= dataFinal.tm_mday) {

                                            printf("\n====================\n"
                                                   "| SERVIÇO REALIZADO %d |\n"
                                                   "====================\n"
                                                   "DESCRIÇÃO: %s\n"
                                                   "PREÇO: $%.2f\n"
                                                   "COMISSÃO: $%.2f\n"
                                                   "CLIENTE: %s\n"
                                                   "FUNCIONARIO: %s\n"
                                                   "DATA: %s\n",
                                                   listaServicos->listaServicos[i].id,
                                                   listaServicos->listaServicos[i].descricao,
                                                   listaServicos->listaServicos[i].preco,
                                                   listaServicos->listaServicos[i].comissao,
                                                   listaClientes->listaClientes[m].nome,
                                                   listaFuncionarios->listaFuncionarios[j].nome,
                                                   listaAgendamentos->listaAgendamentos[l].datahoraInicial);
                                                 }
                                        }
                                }
                            }
                        }
                    }
                }
                token = NULL;
                free(token);

                break;
            default:
                break;
        }
    }

    // Verifica se não há registros
    if (!existeServico) {
        printf("Nenhuma peça foi cadastrado.\n\n");
    }
}

// Armazena o relatório em arquivo
void armazenarRelatorioServicosRealizados(struct ListaClientes *listaClientes,
                              struct ListaServicos *listaServicos,
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

    // Inserindo os dados no arquivo de relatório
    switch (tipo){
        case 1:
            // Listagem baseada nas peças utilizadas no serviço
                for (int i = 0; i < listaServicos->qtdServicos; i++) {
                    for (int j = 0; j < listaFuncionarios->qtdFuncionarios; j++) {
                        for (int k = 0; k < listaVeiculos->qtdVeiculos; k++) {
                            for (int l = 0; l < listaAgendamentos->qtdAgendamentos; l++) {
                                for (int m = 0; m < listaClientes->qtdClientes; m++) {
                                    if (listaServicos->listaServicos[i].deletado == 0 && listaServicos->listaServicos[i].id == id &&
                                        listaAgendamentos->listaAgendamentos[l].idFuncionario == listaFuncionarios->listaFuncionarios[j].id &&
                                        listaAgendamentos->listaAgendamentos[l].idVeiculo == listaVeiculos->listaVeiculos[k].id &&
                                        listaVeiculos->listaVeiculos[k].idProprietario == listaClientes->listaClientes[m].id &&
                                        listaAgendamentos->listaAgendamentos[l].idServico == listaServicos->listaServicos[i].id) {
                                        fprintf(relatorioOrdensServicos, "%d;%s;%.2f;%.2f;%s;%s;%s\n",
                                           listaServicos->listaServicos[i].id,
                                           listaServicos->listaServicos[i].descricao,
                                           listaServicos->listaServicos[i].preco,
                                           listaServicos->listaServicos[i].comissao,
                                           listaClientes->listaClientes[m].nome,
                                           listaFuncionarios->listaFuncionarios[j].nome,
                                           listaAgendamentos->listaAgendamentos[l].datahoraInicial);
                                        }
                                }
                            }
                        }
                    }
                }
            break;
            case 2:
                // Listagem baseada nas peças requisitadas pelo cliente
                for (int i = 0; i < listaServicos->qtdServicos; i++) {
                    for (int j = 0; j < listaFuncionarios->qtdFuncionarios; j++) {
                        for (int k = 0; k < listaVeiculos->qtdVeiculos; k++) {
                            for (int l = 0; l < listaAgendamentos->qtdAgendamentos; l++) {
                                for (int m = 0; m < listaClientes->qtdClientes; m++) {
                                    if (listaServicos->listaServicos[i].deletado == 0 && listaClientes->listaClientes[m].id == id &&
                                        listaAgendamentos->listaAgendamentos[l].idFuncionario == listaFuncionarios->listaFuncionarios[j].id &&
                                        listaAgendamentos->listaAgendamentos[l].idVeiculo == listaVeiculos->listaVeiculos[k].id &&
                                        listaVeiculos->listaVeiculos[k].idProprietario == listaClientes->listaClientes[m].id &&
                                        listaAgendamentos->listaAgendamentos[l].idServico == listaServicos->listaServicos[i].id) {
                                        fprintf(relatorioOrdensServicos, "%d;%s;%.2f;%.2f;%s;%s;%s\n",
                                           listaServicos->listaServicos[i].id,
                                           listaServicos->listaServicos[i].descricao,
                                           listaServicos->listaServicos[i].preco,
                                           listaServicos->listaServicos[i].comissao,
                                           listaClientes->listaClientes[m].nome,
                                           listaFuncionarios->listaFuncionarios[j].nome,
                                           listaAgendamentos->listaAgendamentos[l].datahoraInicial);
                                        }
                                }
                            }
                        }
                    }
                }
                break;
            case 3:
                // Listagem baseada nas peças utilizadas pelo funcionário
                for (int i = 0; i < listaServicos->qtdServicos; i++) {
                    for (int j = 0; j < listaFuncionarios->qtdFuncionarios; j++) {
                        for (int k = 0; k < listaVeiculos->qtdVeiculos; k++) {
                            for (int l = 0; l < listaAgendamentos->qtdAgendamentos; l++) {
                                for (int m = 0; m < listaClientes->qtdClientes; m++) {
                                    if (listaServicos->listaServicos[i].deletado == 0 && listaFuncionarios->listaFuncionarios[j].id == id &&
                                        listaAgendamentos->listaAgendamentos[l].idFuncionario == listaFuncionarios->listaFuncionarios[j].id &&
                                        listaAgendamentos->listaAgendamentos[l].idVeiculo == listaVeiculos->listaVeiculos[k].id &&
                                        listaVeiculos->listaVeiculos[k].idProprietario == listaClientes->listaClientes[m].id &&
                                        listaAgendamentos->listaAgendamentos[l].idServico == listaServicos->listaServicos[i].id) {
                                        fprintf(relatorioOrdensServicos, "%d;%s;%.2f;%.2f;%s;%s;%s\n",
                                           listaServicos->listaServicos[i].id,
                                           listaServicos->listaServicos[i].descricao,
                                           listaServicos->listaServicos[i].preco,
                                           listaServicos->listaServicos[i].comissao,
                                           listaClientes->listaClientes[m].nome,
                                           listaFuncionarios->listaFuncionarios[j].nome,
                                           listaAgendamentos->listaAgendamentos[l].datahoraInicial);
                                        }
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
                for (int i = 0; i < listaServicos->qtdServicos; i++) {
                    for (int j = 0; j < listaFuncionarios->qtdFuncionarios; j++) {
                        for (int k = 0; k < listaVeiculos->qtdVeiculos; k++) {
                            for (int l = 0; l < listaAgendamentos->qtdAgendamentos; l++) {
                                for (int m = 0; m < listaClientes->qtdClientes; m++) {
                                    if (listaServicos->listaServicos[i].deletado == 0 &&
                                        listaAgendamentos->listaAgendamentos[l].idFuncionario == listaFuncionarios->listaFuncionarios[j].id &&
                                        listaAgendamentos->listaAgendamentos[l].idVeiculo == listaVeiculos->listaVeiculos[k].id &&
                                        listaVeiculos->listaVeiculos[k].idProprietario == listaClientes->listaClientes[m].id &&
                                        listaAgendamentos->listaAgendamentos[l].idServico == listaServicos->listaServicos[i].id) {

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

                                            fprintf(relatorioOrdensServicos, "%d;%s;%.2f;%.2f;%s;%s;%s\n",
                                               listaServicos->listaServicos[i].id,
                                               listaServicos->listaServicos[i].descricao,
                                               listaServicos->listaServicos[i].preco,
                                               listaServicos->listaServicos[i].comissao,
                                               listaClientes->listaClientes[m].nome,
                                               listaFuncionarios->listaFuncionarios[j].nome,
                                               listaAgendamentos->listaAgendamentos[l].datahoraInicial);
                                        }
                                        else if (anoVenda == dataInicial.tm_year && mesVenda > dataInicial.tm_mon || anoVenda ==
                                                 dataFinal.tm_year && mesVenda < dataFinal.tm_mon) {

                                            fprintf(relatorioOrdensServicos, "%d;%s;%.2f;%.2f;%s;%s;%s\n",
                                               listaServicos->listaServicos[i].id,
                                               listaServicos->listaServicos[i].descricao,
                                               listaServicos->listaServicos[i].preco,
                                               listaServicos->listaServicos[i].comissao,
                                               listaClientes->listaClientes[m].nome,
                                               listaFuncionarios->listaFuncionarios[j].nome,
                                               listaAgendamentos->listaAgendamentos[l].datahoraInicial);
                                        }
                                        else if (anoVenda == dataInicial.tm_year && mesVenda == dataInicial.tm_mon && diaVenda
                                                 >= dataInicial.tm_mday || anoVenda == dataFinal.tm_year && mesVenda == dataFinal
                                                 .tm_mon && diaVenda <= dataFinal.tm_mday) {

                                            fprintf(relatorioOrdensServicos, "%d;%s;%.2f;%.2f;%s;%s;%s\n",
                                               listaServicos->listaServicos[i].id,
                                               listaServicos->listaServicos[i].descricao,
                                               listaServicos->listaServicos[i].preco,
                                               listaServicos->listaServicos[i].comissao,
                                               listaClientes->listaClientes[m].nome,
                                               listaFuncionarios->listaFuncionarios[j].nome,
                                               listaAgendamentos->listaAgendamentos[l].datahoraInicial);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                break;
            default:
                break;
    }
    fclose(relatorioOrdensServicos);

    printf("Relatório de estoques realizado com sucesso!\n\n");

    // Fechando o arquivo
    fclose(relatorioOrdensServicos);
}
