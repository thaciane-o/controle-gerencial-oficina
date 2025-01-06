#include "viewFinanceiro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../models/caixas/modelCaixa.h"
#include "../../models/oficina/modelOficina.h"
#include "../../models/pagamentoCliente/modelPagamentoCliente.h"
#include "../../models/pagamentoFornecedor/modelPagamentoFornecedor.h"
#include "../../models/fornecedores/modelFornecedores.h"

// Menu de funcionalidades do módulo financeiro
void gerenciarFinanceiro(struct ListaCaixas *listaCaixas, struct ListaOficinas *listaOficinas,
                         struct ListaClientes *listaClientes, struct ListaPagamentosCliente *listaPagamentosCliente,
                         struct ListaPagamentosFornecedor *listaPagamentosFornecedor,
                         struct ListaFornecedores *listaFornecedor,
                         int opcaoArmazenamento) {
    int opcaoSubmenus;

    //Verifica se o programa esta rodando apenas em memória
    if (opcaoArmazenamento != 3) {
        // Busca os dados armazenados em arquivos
        if (listaCaixas->qtdCaixas == 0) {
            buscarDadosCaixasModel(listaCaixas, opcaoArmazenamento);
        }
        // Busca os dados em arquivos das tabelas relacionadas
        if (listaOficinas->qtdOficinas == 0) {
            buscarDadosOficinaModel(listaOficinas, opcaoArmazenamento);
        }
        if (listaClientes->qtdClientes == 0) {
            buscarDadosClientesModel(listaClientes, opcaoArmazenamento);
        }
        if (listaFornecedor->qtdFornecedores == 0) {
            buscarDadosFornecedoresModel(listaFornecedor, opcaoArmazenamento);
        }
        if (listaCaixas->qtdCaixas > 0) {
            buscarDadosPagamentosClienteModel(listaPagamentosCliente, opcaoArmazenamento);
            buscarDadosPagamentosFornecedorModel(listaPagamentosFornecedor, opcaoArmazenamento);
        }
    }

    do {
        printf("\n==========================================\n"
            "|               FINANCEIRO               |\n"
            "==========================================\n"
            "|  1  | Consultar valor de caixa         |\n"
            "|  2  | Consultar contas a receber       |\n"
            "|  3  | Consultar contas a pagar         |\n"
            "|  4  | Registrar recebimento de cliente |\n"
            "|  5  | Efetuar pagamento a fornecedor   |\n"
            "|  6  | Voltar                           |\n"
            "==========================================\n"
            "Escolha uma opção: ");
        scanf("%d", &opcaoSubmenus);

        switch (opcaoSubmenus) {
            case 1:
                consultarValorCaixa(listaCaixas, listaPagamentosCliente);
                break;
            case 2:
                consultarContasAReceber(listaPagamentosCliente, listaCaixas);
                break;
            case 3:
                consultarContasAPagar(listaPagamentosFornecedor, listaCaixas);
                break;
            case 4:
                registrarRecebimentoCliente(listaClientes, listaCaixas, listaPagamentosCliente);
                break;
            case 5:
                efetuarPagamentoFornecedor(listaPagamentosFornecedor, listaFornecedor, listaCaixas);
                break;
            case 6:
                if (opcaoArmazenamento != 3) {
                    if (listaCaixas->qtdCaixas > 0 && listaCaixas->listaCaixas != NULL) {
                        armazenarDadosCaixasModel(listaCaixas, opcaoArmazenamento);
                    }
                    if (listaPagamentosCliente->qtdPagamentosCliente > 0 && listaPagamentosCliente->
                        listaPagamentosCliente != NULL) {
                        armazenarDadosPagamentosClienteModel(listaPagamentosCliente, opcaoArmazenamento);
                    }
                    if (listaPagamentosFornecedor->qtdPagamentosFornecedor > 0 && listaPagamentosFornecedor->
                        listaPagamentosFornecedor != NULL) {
                        armazenarDadosPagamentosFornecedorModel(listaPagamentosFornecedor, opcaoArmazenamento);
                    }

                    if (listaOficinas->qtdOficinas > 0) {
                        free(listaOficinas->listaOficinas);
                        listaOficinas->listaOficinas = NULL;
                        listaOficinas->qtdOficinas = 0;
                    }
                    if (listaClientes->qtdClientes > 0) {
                        free(listaClientes->listaClientes);
                        listaClientes->listaClientes = NULL;
                        listaClientes->qtdClientes = 0;
                    }
                    if (listaFornecedor->qtdFornecedores > 0) {
                        free(listaFornecedor->listaFornecedores);
                        listaFornecedor->listaFornecedores = NULL;
                        listaFornecedor->qtdFornecedores = 0;
                    }
                }
                return;
            default:
                printf("Opção inválida!\n\n");
                break;
        }
    } while (opcaoSubmenus != 6);
}

// Busca de valor de caixa de oficina
void consultarValorCaixa(struct ListaCaixas *lista, struct ListaPagamentosCliente *listaPagamentosCliente) {
    int idOficina;

    printf("\n======================================\n"
        "|     CONSULTA DE VALOR DE CAIXA     |\n"
        "======================================\n");

    printf("Insira o ID da oficina que deseja consultar: ");
    setbuf(stdin, NULL);
    scanf("%d", &idOficina);

    mostrarCaixasModel(lista, idOficina, listaPagamentosCliente);
}

// Busca por contas a receber
void consultarContasAReceber(struct ListaPagamentosCliente *listaPagamentosCliente, struct ListaCaixas *listaCaixas) {
    int opcaoSubmenu;
    int id;

    printf("\n==================================================\n"
        "|          CONSULTA DE CONTAS A RECEBER          |\n"
        "==================================================\n"
        "|  1  | Buscar contas por cliente                |\n"
        "|  2  | Buscar contas por oficina                |\n"
        "|  3  | Buscar contas recebidas por oficina      |\n"
        "|  4  | Listar contas não recebidas por oficina  |\n"
        "|  5  | Voltar                                   |\n"
        "==================================================\n"
        "Escolha uma opção: ");
    scanf("%d", &opcaoSubmenu);

    switch (opcaoSubmenu) {
        case 1:
            printf("\n====================================\n"
                "|     LISTAR CONTAS DE CLIENTE     |\n"
                "====================================\n");
            printf("Insira o ID do cliente que deseja consultar: ");
            setbuf(stdin, NULL);
            scanf("%d", &id);
            listarPagamentosDeClienteModel(listaPagamentosCliente, id);
            break;

        case 2:
            printf("\n====================================\n"
                "|     LISTAR CONTAS DE OFICINA     |\n"
                "====================================\n");
            printf("Insira o ID da oficina que deseja consultar: ");
            setbuf(stdin, NULL);
            scanf("%d", &id);
            listarTodosPagamentosClienteDeOficinaModel(listaPagamentosCliente, listaCaixas, id);
            break;

        case 3:
            printf("\n===================================\n"
                "|     LISTAR CONTAS RECEBIDAS     |\n"
                "===================================\n");
            printf("Insira o ID da oficina que deseja consultar: ");
            setbuf(stdin, NULL);
            scanf("%d", &id);
            listaPagamentosRecebidosClienteModel(listaPagamentosCliente, listaCaixas, id);
            break;

        case 4:
            printf("\n=======================================\n"
                "|     LISTAR CONTAS NÃO RECEBIDAS     |\n"
                "=======================================\n");
            printf("Insira o ID da oficina que deseja consultar: ");
            setbuf(stdin, NULL);
            scanf("%d", &id);
            listaPagamentosNaoRecebidosClienteModel(listaPagamentosCliente, listaCaixas, id);
            break;

        case 5:
            // Volta ao menu anterior
            break;

        default:
            printf("Opção inválida, voltando ao menu anterior.");
            break;
    }
}

// Busca por contas a pagar
void consultarContasAPagar(struct ListaPagamentosFornecedor *listaPagamentosFornecedor,
                           struct ListaCaixas *listaCaixas) {
    int opcaoSubmenu;
    int id;

    printf("\n========================================\n"
        "|      CONSULTA DE CONTAS A PAGAR      |\n"
        "========================================\n"
        "|  1  | Buscar contas por oficina      |\n"
        "|  2  | Buscar contas por fornecedor   |\n"
        "|  3  | Voltar                         |\n"
        "========================================\n"
        "Escolha uma opção: ");
    scanf("%d", &opcaoSubmenu);

    switch (opcaoSubmenu) {
        case 1:
            printf("\n=====================================\n"
                "|     LISTAR CONTAS POR OFICINA     |\n"
                "=====================================\n");
            printf("Insira o ID da oficina que deseja consultar: ");
            setbuf(stdin, NULL);
            scanf("%d", &id);
            listaPagamentosFornecedorPorOficinaModel(listaPagamentosFornecedor, listaCaixas, id);
            break;

        case 2:
            printf("\n========================================\n"
                "|     LISTAR CONTAS POR FORNECEDOR     |\n"
                "========================================\n");
            printf("Insira o ID do fornecedor que deseja consultar: ");
            setbuf(stdin, NULL);
            scanf("%d", &id);
            listaPagamentosFornecedorPorFornecedorModel(listaPagamentosFornecedor, listaCaixas, id);
            break;

        case 3:
            // Volta ao menu anterior
            break;

        default:
            printf("Opção inválida, voltando ao menu anterior.");
            break;
    }
}

// Registra recebimento de cliente (Cliente paga a oficina)
void registrarRecebimentoCliente(struct ListaClientes *listaClientes, struct ListaCaixas *listaCaixas,
                                 struct ListaPagamentosCliente *listaPagamentosCliente) {
    struct PagamentosCliente pagamento;
    int idCliente;
    int idOficina;
    int idCaixa;
    int tipoPagamento = 0;

    printf("\n==========================================\n"
        "|     REGISTRAR PAGAMENTO DE CLIENTE     |\n"
        "==========================================\n");

    printf("Insira o ID do cliente que está fazendo o pagamento: ");
    setbuf(stdin, NULL);
    scanf("%d", &idCliente);

    // Verificando existência de cliente
    if (verificarIDClienteModel(listaClientes, idCliente) == 0) {
        return;
    }
    pagamento.idCliente = idCliente;

    // Busca ID da oficina que atende esse cliente
    idOficina = getIdOficinaClientesModel(listaClientes, idCliente);
    if (idOficina == -1) {
        return;
    }

    // Busca ID do caixa da oficina que atende o cliente
    idCaixa = getIdCaixaPorOficinaModel(listaCaixas, idOficina);
    if (idCaixa == -1) {
        return;
    }
    pagamento.idCaixa = idCaixa;

    do {
        printf("\n========================="
            "\n| 1 | Dinheiro          |"
            "\n| 2 | Cartão de crédito |"
            "\n| 3 | Cartão de débito  |"
            "\n=========================");
        printf("\nInsira tipo de pagamento: ");
        setbuf(stdin, NULL);
        scanf("%d", &tipoPagamento);
    } while (tipoPagamento < 1 || tipoPagamento > 3);
    pagamento.tipoPagamento = tipoPagamento;

    printf("Insira o valor do pagamento: R$");
    setbuf(stdin, NULL);
    scanf("%f", &pagamento.valor);

    printf("Insira a data do pagamento (DD/MM/AAAA): ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", pagamento.dataPagamento);

    if (pagamento.tipoPagamento == 1) {
        strcpy(pagamento.dataAReceber, pagamento.dataPagamento);
        strcpy(pagamento.dataRecebimento, pagamento.dataPagamento);
    } else {
        printf("Insira a data de vencimento do cartão (DD/MM/AAAA): ");
        setbuf(stdin, NULL);
        scanf(" %[^\n]", &pagamento.dataAReceber);

        // Realiza as verificações de data
        struct tm dataAReceber = {0};
        sscanf(pagamento.dataAReceber, "%d/%d/%d",
           &dataAReceber.tm_mday, &dataAReceber.tm_mon, &dataAReceber.tm_year);
        dataAReceber.tm_year -= 1900;
        dataAReceber.tm_mon -= 1;
        time_t tempoDataReceber = mktime(&dataAReceber);

        if (tempoDataReceber == -1) {
            printf("Erro ao converter a data e hora.\n");
            return;
        }

        time_t tempoAgora = time(NULL);

        if (tempoDataReceber <= tempoAgora) {
            strftime(pagamento.dataRecebimento, sizeof(pagamento.dataRecebimento), "%d/%m/%Y", localtime(&tempoAgora));
        } else {
            strcpy(pagamento.dataRecebimento, "Não pago");
        }
    }

    cadastrarPagamentosClienteModel(listaPagamentosCliente, &pagamento, listaCaixas);
}

// Efeuta pagamento a fornecedor (Oficina paga ao fornecedor)
void efetuarPagamentoFornecedor(struct ListaPagamentosFornecedor *listaPagamentosFornecedor,
                                struct ListaFornecedores *listaFornecedores, struct ListaCaixas *listaCaixas) {
    struct PagamentosFornecedor pagamento;
    int idFornecedor;
    int idOficina;
    int idCaixa;
    int tipoPagamento = 0;

    printf("\n============================================\n"
        "|     REGISTRAR PAGAMENTO A FORNECEDOR     |\n"
        "============================================\n");

    printf("Insira o ID do fornecedor que receberá o pagamento: ");
    setbuf(stdin, NULL);
    scanf("%d", &idFornecedor);

    if (verificarIDFornecedoresModel(listaFornecedores, idFornecedor) == 0) {
        return;
    }
    pagamento.idFornecedor = idFornecedor;

    printf("Insira o ID da oficina que realiza o pagamento: ");
    setbuf(stdin, NULL);
    scanf("%d", &idOficina);

    // Busca ID do caixa da oficina que está efetuando o pagamento
    idCaixa = getIdCaixaPorOficinaModel(listaCaixas, idOficina);
    if (idCaixa == -1) {
        return;
    }
    pagamento.idCaixa = idCaixa;

    do {
        printf("\n========================="
            "\n| 1 | Dinheiro          |"
            "\n| 2 | Cartão de crédito |"
            "\n| 3 | Cartão de débito  |"
            "\n=========================");
        printf("\nInsira tipo de pagamento: ");
        setbuf(stdin, NULL);
        scanf("%d", &tipoPagamento);
    } while (tipoPagamento < 1 || tipoPagamento > 3);
    pagamento.tipoPagamento = tipoPagamento;

    printf("Insira o valor do pagamento: R$");
    setbuf(stdin, NULL);
    scanf("%f", &pagamento.valor);

    printf("Insira a data do pagamento (DD/MM/AAAA): ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", pagamento.dataPagamento);

    cadastrarPagamentosFornecedorModel(listaPagamentosFornecedor, &pagamento, listaCaixas);
}
