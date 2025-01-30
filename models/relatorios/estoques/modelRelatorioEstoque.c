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


// Imprime o relatório na tela
void imprimirRelatorioEstoque(struct ListaNotasFiscais *listaNotas, struct ListaPecasNotas *listaPecasNotas,
                              struct ListaPecas *listaPecas, struct ListaClientes *listaClientes,
                              struct ListaServicos *listaServicos,
                              struct ListaAgendamentos *listaAgendamentos,
                              struct ListaOrdensServico *listaOrdensServicos,
                              struct ListaFornecedores *listaFornecedores,
                              struct ListaFuncionarios *listaFuncionarios, struct ListaOficinas *listaOficinas,
                              struct ListaPagamentosFornecedor *listaPagamentosFornecedor,
                              struct ListaPagamentosCliente *listaPagamentosCliente,
                              struct tm dataInicial, struct tm dataFinal, int tipo,
                              int id) {
    int existeEstoque = 0;


    // Verifica se há pelo menos um registro
    if (listaPecas->qtdPecas > 0) {
        existeEstoque = 1;
        switch (tipo) {
            case 1:
            for (int i = 0; i < listaPecas->qtdPecas; i++) {
                for (int j = 0; j < listaAgendamentos->qtdAgendamentos; j++) {
                    if (listaPecas->listaPecas[i].deletado == 0) {
                        printf("\n====================\n"
                           "| PEÇA %d           |\n"
                           "====================\n"
                           "DESCRIÇÃO: %s\n"
                           "FABRICANTE: %s\n"
                           "PREÇO DE CUSTO: $%.2f\n"
                           "PREÇO DE VENDA: $%.2f\n"
                           "QUANTIDADE EM ESTOQUE: %d\n"
                           "ESTOQUE MÍNIMO: %d\n"
                           "FORNECEDOR: %d\n",
                           listaPecas->listaPecas[i].id,
                           listaPecas->listaPecas[i].descricao,
                           listaPecas->listaPecas[i].fabricante,
                           listaPecas->listaPecas[i].precoCusto,
                           listaPecas->listaPecas[i].precoVenda,
                           listaPecas->listaPecas[i].qtdEstoque,
                           listaPecas->listaPecas[i].estoqueMinimo,
                           listaPecas->listaPecas[i].idFornecedor);
                    }
                }
            }
            break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
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
void armazenarRelatorioEstoque(struct ListaNotasFiscais *listaNotas, struct ListaPecasNotas *listaPecasNotas,
                              struct ListaPecas *listaPecas, struct ListaClientes *listaClientes,
                              struct ListaServicos *listaServicos,
                              struct ListaAgendamentos *listaAgendamentos,
                              struct ListaOrdensServico *listaOrdensServicos,
                              struct ListaFornecedores *listaFornecedores,
                              struct ListaFuncionarios *listaFuncionarios, struct ListaOficinas *listaOficinas,
                              struct ListaPagamentosFornecedor *listaPagamentosFornecedor,
                              struct ListaPagamentosCliente *listaPagamentosCliente,
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
                fprintf(relatorioEstoque, "%d;%s;%s;%.2f;%.2f;%d;%d;%d;%d;%d\n",
                        listaPecas->listaPecas[i].id,
                        listaPecas->listaPecas[i].descricao,
                        listaPecas->listaPecas[i].fabricante,
                        listaPecas->listaPecas[i].precoCusto,
                        listaPecas->listaPecas[i].precoVenda,
                        listaPecas->listaPecas[i].qtdEstoque,
                        listaPecas->listaPecas[i].estoqueMinimo,
                        listaPecas->listaPecas[i].idOficina,
                        listaPecas->listaPecas[i].idFornecedor,
                        listaPecas->listaPecas[i].deletado);
            }
        break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        default:
            break;
    }

    printf("Relatório de estoques realizado com sucesso!\n\n");

    // Fechando o arquivo
    fclose(relatorioEstoque);
}
