#include "../../models/caixas/modelCaixa.h"
#include "../../models/oficina/modelOficina.h"
#include "../../models/pagamentoCliente/modelPagamentoCliente.h"

#include "viewFinanceiro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Menu de funcionalidades do módulo financeiro
void gerenciarFinanceiro(struct ListaCaixas *listaCaixas, struct ListaOficinas *listaOficinas,
                         struct ListaClientes *listaClientes, struct ListaPagamentosCliente *listaPagamentosCliente,
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
        if (listaCaixas->qtdCaixas > 0) {
            buscarDadosPagamentosClienteModel(listaPagamentosCliente, opcaoArmazenamento);
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
                consultarValorCaixa(listaCaixas);
                break;
            case 2:
                consultarContasAReceber(listaPagamentosCliente, listaCaixas);
                break;
            case 3:
                printf("Consultando contas a pagar");
                break;
            case 4:
                registrarRecebimentoCliente(listaClientes, listaCaixas, listaPagamentosCliente);
                break;
            case 5:
                printf("Efetuar pagamento a fornecedor");
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
                }
                return;
            default:
                printf("Opção inválida!\n\n");
                break;
        }
    } while (opcaoSubmenus != 5);
}

// Busca de valor de caixa de oficina
void consultarValorCaixa(struct ListaCaixas *lista) {
    int idOficina;

    printf("\n======================================\n"
        "|     CONSULTA DE VALOR DE CAIXA     |\n"
        "======================================\n");

    printf("Insira o ID da oficina que deseja consultar: ");
    setbuf(stdin, NULL);
    scanf("%d", &idOficina);

    mostrarCaixasModel(lista, idOficina);
}

// Busca por contas a receber
void consultarContasAReceber(struct ListaPagamentosCliente *listaPagamentosCliente, struct ListaCaixas *listaCaixas) {
    int opcaoSubmenu;
    int id;

    printf("\n========================================\n"
        "|     CONSULTA DE CONTAS A RECEBER     |\n"
        "========================================\n"
        "|  1  | Buscar contas de cliente       |\n"
        "|  2  | Listar todas as contas         |\n"
        "|  3  | Listar contas recebidas        |\n"
        "|  4  | Listar contas não recebidas    |\n"
        "|  5  | Voltar                         |\n"
        "========================================\n"
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
            printf("\n==================================\n"
                "|     LISTAR TODAS AS CONTAS     |\n"
                "==================================\n");
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
            break;

        case 4:
            printf("\n=======================================\n"
                "|     LISTAR CONTAS NÃO RECEBIDAS     |\n"
                "=======================================\n");
            printf("Insira o ID da oficina que deseja consultar: ");
            setbuf(stdin, NULL);
            scanf("%d", &id);
            break;

        case 5:
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
    idCaixa = getIdCaixaModel(listaCaixas, idOficina);
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

    printf("Insira a data do pagamento (dd/mm/yyyy): ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", pagamento.dataPagamento);

    if (pagamento.tipoPagamento == 1) {
        strcpy(pagamento.dataAReceber, pagamento.dataPagamento);
        strcpy(pagamento.dataRecebimento, pagamento.dataPagamento);
    } else {
        printf("Insira a data de vencimento do cartão (dd/mm/yyyy): ");
        setbuf(stdin, NULL);
        scanf(" %[^\n]", &pagamento.dataAReceber);

        strcpy(pagamento.dataRecebimento, "Não pago");
    }

    cadastrarPagamentosClienteModel(listaPagamentosCliente, &pagamento);
}
