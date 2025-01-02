#include "../../models/agendamentos/modelAgendamentos.h"
#include "../../models/veiculos/modelVeiculos.h"
#include "../../models/funcionarios/modelFuncionarios.h"
#include "../../models/servicos/modelServicos.h"
#include "../../models/ordensServico/modelOrdensServico.h"
#include "../../models/pecas/modelPecas.h"
#include "../../models/clientes/modelClientes.h"
#include "../../models/caixas/modelCaixa.h"
#include "../../models/pagamentoCliente/modelPagamentoCliente.h"
#include "viewAgendamentos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Menu de funcionalidades de agentamentos
void gerenciarAgendamentos(struct ListaAgendamentos *lista, struct ListaFuncionarios *listaFuncionarios,
                           struct ListaServicos *listaServicos, struct ListaVeiculos *listaVeiculos,
                           struct ListaOrdensServico *listaOrdensServico, struct ListaPecas *listaPecas,
                           struct ListaClientes *listaClientes, struct ListaCaixas *listaCaixas,
                           struct ListaPagamentosCliente *listaPagamentosCliente, int opcaoArmazenamento) {
    int opcaoSubmenus;
    //Verifica se o programa esta rodando apenas em memória
    if (opcaoArmazenamento != 3) {
        // Busca os dados armazenados em arquivos
        if (lista->qtdAgendamentos == 0) {
            buscarDadosAgendamentosModel(lista, opcaoArmazenamento);
        }

        // Busca os dados em arquivos das tabelas relacionadas
        if (listaVeiculos->qtdVeiculos == 0) {
            buscarDadosVeiculosModel(listaVeiculos, opcaoArmazenamento);
        }

        if (listaFuncionarios->qtdFuncionarios == 0) {
            buscarDadosFuncionariosModel(listaFuncionarios, opcaoArmazenamento);
        }

        if (listaServicos->qtdServicos == 0) {
            buscarDadosServicoModel(listaServicos, opcaoArmazenamento);
        }

        if (listaOrdensServico->qtdOrdensServico == 0) {
            buscarDadosOrdensServicoModel(listaOrdensServico, opcaoArmazenamento);
        }

        if (listaPecas->qtdPecas == 0) {
            buscarDadosPecaModel(listaPecas, opcaoArmazenamento);
        }

        if (listaClientes->qtdClientes == 0) {
            buscarDadosClientesModel(listaClientes, opcaoArmazenamento);
        }

        if (listaCaixas->qtdCaixas == 0) {
            buscarDadosCaixasModel(listaCaixas, opcaoArmazenamento);
        }

        if (listaPagamentosCliente->qtdPagamentosCliente == 0) {
            buscarDadosPagamentosClienteModel(listaPagamentosCliente, opcaoArmazenamento);
        }
    }

    do {
        printf("\n==================================\n"
            "|      MENU DE AGENDAMENTOS      |\n"
            "==================================\n"
            "|  1  | Agendar                  |\n"
            "|  2  | Atualizar agendamento    |\n"
            "|  3  | Cancelar agendamento     |\n"
            "|  4  | Listar agendamento       |\n"
            "|  5  | Finalizar agendamento    |\n"
            "|  6  | Voltar                   |\n"
            "==================================\n"
            "Escolha uma opção: ");
        scanf("%d", &opcaoSubmenus);

        switch (opcaoSubmenus) {
            case 1:
                cadastrarAgendamentos(lista, listaFuncionarios, listaServicos, listaVeiculos, listaOrdensServico,
                                      listaPecas, listaClientes, listaCaixas, listaPagamentosCliente);
                break;
            case 2:
                atualizarAgendamento(lista, listaFuncionarios, listaServicos, listaVeiculos);
                break;
            case 3:
                deletarAgendamento(lista, listaOrdensServico);
                break;
            case 4:
                listarAgendamentos(lista, listaOrdensServico);
                break;
            case 5:
                finalizarAgendamento(lista);
                break;
            case 6:
                if (opcaoArmazenamento != 3 && lista->listaAgendamentos != NULL) {
                    if (lista->qtdAgendamentos > 0) {
                        armazenarDadosAgendamentosModel(lista, opcaoArmazenamento);
                        armazenarDadosOrdensServicoModel(listaOrdensServico, opcaoArmazenamento);
                    }

                    if (listaVeiculos->qtdVeiculos > 0) {
                        listaVeiculos->listaVeiculos = NULL;
                        free(listaVeiculos->listaVeiculos);
                        listaVeiculos->qtdVeiculos = 0;
                    }

                    if (listaServicos->qtdServicos > 0) {
                        listaServicos->listaServicos = NULL;
                        free(listaServicos->listaServicos);
                        listaServicos->qtdServicos = 0;
                    }

                    if (listaFuncionarios->qtdFuncionarios > 0) {
                        listaFuncionarios->listaFuncionarios = NULL;
                        free(listaFuncionarios->listaFuncionarios);
                        listaFuncionarios->qtdFuncionarios = 0;
                    }

                    if (listaOrdensServico->qtdOrdensServico > 0) {
                        listaOrdensServico->listaOrdensServico = NULL;
                        free(listaOrdensServico->listaOrdensServico);
                        listaOrdensServico->qtdOrdensServico = 0;
                    }

                    if (listaPecas->qtdPecas > 0) {
                        listaPecas->listaPecas = NULL;
                        free(listaPecas->listaPecas);
                        listaPecas->qtdPecas = 0;
                    }

                    if (listaClientes->qtdClientes > 0) {
                        listaClientes->listaClientes = NULL;
                        free(listaClientes->listaClientes);
                        listaClientes->qtdClientes = 0;
                    }

                    // Armazena caixas alterados (Com novo saldo de pagamentos)
                    if (listaCaixas->qtdCaixas > 0) {
                        armazenarDadosCaixasModel(listaCaixas, opcaoArmazenamento);
                    }

                    // Armazena pagamentos realizados
                    if (listaPagamentosCliente->qtdPagamentosCliente > 0) {
                        armazenarDadosPagamentosClienteModel(listaPagamentosCliente, opcaoArmazenamento);
                    }
                }
                return;
            default:
                printf("Opção inválida!\n\n");
                break;
        }
    } while (opcaoSubmenus != 6);
}

// Formulário de cadastro de agendamentos
void cadastrarAgendamentos(struct ListaAgendamentos *lista, struct ListaFuncionarios *listaFuncionarios,
                           struct ListaServicos *listaServicos, struct ListaVeiculos *listaVeiculos,
                           struct ListaOrdensServico *listaOrdensServico, struct ListaPecas *listaPecas,
                           struct ListaClientes *listaClientes, struct ListaCaixas *listaCaixas,
                           struct ListaPagamentosCliente *listaPagamentosCliente) {
    struct Agendamentos agendamento;
    struct OrdensServico ordensServico;
    int idFuncionarios, idVeiculos, qtdServicos = 0, idInputServico, qtdPecas = 0, idInputPecas;
    int *idServicos = malloc(sizeof(int));
    int *idPecas = malloc(sizeof(int));
    struct PagamentosCliente pagamento;
    pagamento.valor = 0;

    printf("\n======================\n"
        "|     AGENDAMENTO    |\n"
        "======================\n");

    do {
        // Agendando 1 ou mais serviços
        qtdServicos++;
        if (qtdServicos > 1) {
            idServicos = realloc(idServicos, qtdServicos * sizeof(int));
        }

        printf("Insira o ID do serviço que será agendado (0 para finalizar): ");
        setbuf(stdin, NULL);
        scanf("%d", &idInputServico);

        // Verificando existência do item relacionado
        if (idInputServico != 0) {
            idServicos[qtdServicos - 1] = idInputServico;
            verificarIDServicoModel(listaServicos, idServicos[qtdServicos - 1]);

            do {
                // Inserindo 1 ou mais peças por serviço
                qtdPecas++;
                if (qtdPecas > 1) {
                    idPecas = realloc(idPecas, qtdPecas * sizeof(int));
                }

                printf("Insira o ID da peça que será necessária para realizar esse serviço (0 para finalizar): ");
                setbuf(stdin, NULL);
                scanf("%d", &idInputPecas);

                // Verificando existência do item relacionado
                if (idInputPecas != 0) {
                    idPecas[qtdPecas - 1] = idInputPecas;
                    verificarIDPecaModel(listaPecas, idPecas[qtdPecas - 1]);
                }
            } while (idInputPecas != 0);
        }
    } while (idInputServico != 0);

    if (qtdServicos > 1) {
        printf("Insira o ID do funcionário que fará o serviço: ");
        setbuf(stdin, NULL);
        scanf("%d", &idFuncionarios);

        printf("Insira o ID do veículo a receber o serviço: ");
        setbuf(stdin, NULL);
        scanf("%d", &idVeiculos);

        // Verificando existência do item relacionado
        if (verificarIDFuncionariosModel(listaFuncionarios, idFuncionarios) == 0) {
            return;
        }

        if (verificarIDVeiculoModel(listaVeiculos, idVeiculos) == 0) {
            return;
        }

        agendamento.idFuncionario = idFuncionarios;
        agendamento.idVeiculo = idVeiculos;

        // Preenchimento dos dados
        printf("Insira a data desejada para realizar o serviço (DD/MM/AAAA): ");
        setbuf(stdin, NULL);
        scanf(" %[^\n]", agendamento.data);

        printf("Insira a hora desejada para realizar o serviço (HH:MM): ");
        setbuf(stdin, NULL);
        scanf(" %[^\n]", agendamento.hora);

        // Verificando se um funcionário já possui um serviço na data e hora inserida
        for (int i = 0; i < lista->qtdAgendamentos; i++) {
            if (lista->listaAgendamentos[i].idFuncionario == idFuncionarios &&
                strcmp(lista->listaAgendamentos[i].data, agendamento.data) == 0 &&
                strcmp(lista->listaAgendamentos[i].hora, agendamento.hora) == 0) {
                printf("Não é possível agendar um serviço com esse funcionário.\n\n");

                // Limpando os ponteiros
                idPecas = NULL;
                free(idPecas);

                idServicos = NULL;
                free(idServicos);
                return;
            }
        }

        /*
         *  Dados para realizar o cadastro de pagamento do cliente
         */

        // Pegando o valor total do serviço: serviços + peças
        for (int i = 0; i < (qtdServicos - 1); i++) {
            pagamento.valor += listaServicos->listaServicos[i].preco;

            // Pegando o valor total das peças
            for (int j = 0; j < (qtdPecas - 1); j++) {
                pagamento.valor += listaPecas->listaPecas[j].precoVenda;
            }
        }

        // Pegando o tipo de pagamento do cliente, e mostrando o valor total do serviço
        do {
            printf("\nValor total do serviço e peças usadas: R$%.2f", pagamento.valor);
            printf("\n========================="
                "\n| 1 | Dinheiro          |"
                "\n| 2 | Cartão de crédito |"
                "\n| 3 | Cartão de débito  |"
                "\n=========================");
            printf("\nInsira tipo de pagamento: ");
            setbuf(stdin, NULL);
            scanf("%d", &pagamento.tipoPagamento);
        } while (pagamento.tipoPagamento < 1 || pagamento.tipoPagamento > 3);

        // Pegando a data que foi realizado o pagamento
        printf("Insira a data do pagamento (DD/MM/AAAA): ");
        setbuf(stdin, NULL);
        scanf(" %[^\n]", pagamento.dataPagamento);

        // Ajustando data de recebimento, caso dinheiro, ou pedindo a data, caso cartão
        if (pagamento.tipoPagamento == 1) {
            strcpy(pagamento.dataAReceber, pagamento.dataPagamento);
            strcpy(pagamento.dataRecebimento, pagamento.dataPagamento);
        } else {
            printf("Insira a data de vencimento do cartão (DD/MM/AAAA): ");
            setbuf(stdin, NULL);
            scanf(" %[^\n]", &pagamento.dataAReceber);
            strcpy(pagamento.dataRecebimento, "Não pago");
        }

        // Pegando ID do cliente que faz o pagamento
        int idClientePagando = getIdClientePorVeiculoModel(listaVeiculos, idVeiculos);
        if (idClientePagando == -1) {
            // Não encontrou, então cancela a operação
            idPecas = NULL;
            free(idPecas);

            idServicos = NULL;
            free(idServicos);
            return;
        }

        // Pegando ID da oficina e do seu caixa para receber o pagamento
        int getIdOficina = getIdOficinaClientesModel(listaClientes, idClientePagando);
        int idCaixaRecebe = getIdCaixaPorOficinaModel(listaCaixas, getIdOficina);
        if (idCaixaRecebe == -1) {
            // Não encontrou, então cancela a operação
            idPecas = NULL;
            free(idPecas);

            idServicos = NULL;
            free(idServicos);
            return;
        }

        // Atribui os IDs ao pagamento
        pagamento.idCaixa = idCaixaRecebe;
        pagamento.idCliente = idClientePagando;

        // Cadastra o pagamento
        cadastrarPagamentosClienteModel(listaPagamentosCliente, &pagamento, listaCaixas);

        /*
         *   Fim de cadastro de pagamentos do cliente
         */

        // Cadastrando agendamentos de cada serviço inserido
        for (int i = 0; i < (qtdServicos - 1); i++) {
            agendamento.idServico = idServicos[i];
            cadastrarAgendamentosModel(lista, &agendamento);

            strcpy(ordensServico.descricao, listaServicos->listaServicos[i].descricao);
            ordensServico.idAgendamentos = lista->qtdAgendamentos;
            ordensServico.valorTotal = listaServicos->listaServicos[i].preco;

            // Cadastrando ordens de serviço de cada peça inserida
            for (int j = 0; j < (qtdPecas - 1); j++) {
                ordensServico.valorTotal += listaPecas->listaPecas[j].precoVenda;
                ordensServico.idPecas = idPecas[j];
                cadastrarOrdensServicoModel(listaOrdensServico, &ordensServico);
            }
        }

        printf("Agendamento realizado com sucesso para a data %s às %s!\n\n", agendamento.data, agendamento.hora);
        printf("Ordem de serviço emitida com sucesso!\n\n");
    } else {
        printf("Nenhum serviço agendado!\n\n");
    }

    // Limpando os ponteiros
    idPecas = NULL;
    free(idPecas);

    idServicos = NULL;
    free(idServicos);
}

// Formulário de atualização de agendamentos
void atualizarAgendamento(struct ListaAgendamentos *lista, struct ListaFuncionarios *listaFuncionarios,
                          struct ListaServicos *listaServicos, struct ListaVeiculos *listaVeiculos) {
    int id, idFuncionario, idVeiculo, idServico;
    struct Agendamentos agendamento;

    // Pede o ID do agendamento que será atualizado
    printf("\n=====================================\n"
        "|     ATUALIZAÇÃO DE AGENDAMENTO    |\n"
        "=====================================\n"
        "Insira o ID do agendamento que deseja atualizar: ");
    scanf("%d", &id);

    // Verifica se o ID inserido existe
    int encontrado = verificarIDAgendamentoModel(lista, id);
    if (encontrado == 0) {
        return;
    }

    printf("Insira o ID do serviço que será agendado: ");
    setbuf(stdin, NULL);
    scanf("%d", &idServico);

    printf("Insira o ID do funcionário que fará o serviço: ");
    setbuf(stdin, NULL);
    scanf("%d", &idFuncionario);

    printf("Insira o ID do veículo a receber o serviço: ");
    setbuf(stdin, NULL);
    scanf("%d", &idVeiculo);

    // Verificando existência do item relacionado
    if (verificarIDServicoModel(listaServicos, idServico) == 0) {
        return;
    }

    if (verificarIDFuncionariosModel(listaFuncionarios, idFuncionario) == 0) {
        return;
    }

    if (verificarIDVeiculoModel(listaVeiculos, idVeiculo) == 0) {
        return;
    }

    agendamento.idFuncionario = idFuncionario;
    agendamento.idServico = idServico;
    agendamento.idVeiculo = idServico;

    // Preenchimento dos dados
    printf("Insira a data prevista para realizar o serviço (DD/MM/YYYY): ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", agendamento.data);

    printf("Insira a hora prevista para realizar o serviço (HH:MM): ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", agendamento.hora);

    for (int i = 0; i < lista->qtdAgendamentos; i++) {
        if (lista->listaAgendamentos[i].idFuncionario == idFuncionario &&
            strcmp(lista->listaAgendamentos[i].data, agendamento.data) == 0 &&
            strcmp(lista->listaAgendamentos[i].hora, agendamento.hora) == 0) {
            printf("Não é possível agendar um serviço com esse funcionário.\n\n");
            return;
        }
    }

    atualizarAgendamentosModel(lista, id, &agendamento);
}

// Listagem de agendamentos
void listarAgendamentos(struct ListaAgendamentos *lista, struct ListaOrdensServico *listaOrdensServico) {
    int opcao, id;

    // Pergunta o tipo de listagem
    printf("\n====================================\n"
        "|    LISTAGEM DE AGENDAMENTOS      |\n"
        "====================================\n"
        "| 1 | Busca por ID                 |\n"
        "| 2 | Busca por ID do funcionário  |\n"
        "| 3 | Busca por ID do veículo      |\n"
        "| 4 | Busca por ID do serviço      |\n"
        "| 5 | Listar todos                 |\n"
        "| 6 | Voltar                       |\n"
        "====================================\n"
        "Escolha uma opção: ");
    setbuf(stdin, NULL);
    scanf("%d", &opcao);

    // Verifica a opção de listagem
    switch (opcao) {
        // Listagem de um único agendamento
        case 1:
            printf("Insira o ID do agendamento que deseja listar: ");
            setbuf(stdin, NULL);
            scanf("%d", &id);
            listarAgendamentoModel(lista, id, listaOrdensServico);
            break;
        // Listagem por relação
        case 2:
            printf("Insira o ID do funcionário desejado para a busca: ");
            setbuf(stdin, NULL);
            scanf("%d", &id);
            buscarAgendamentosPorFuncionarioModel(lista, id, listaOrdensServico);
            break;
        case 3:
            printf("Insira o ID do veículo desejado para a busca: ");
            setbuf(stdin, NULL);
            scanf("%d", &id);
            buscarAgendamentosPorVeiculoModel(lista, id, listaOrdensServico);
            break;
        case 4:
            printf("Insira o ID do serviço desejado para a busca: ");
            setbuf(stdin, NULL);
            scanf("%d", &id);
            buscarAgendamentosPorServicoModel(lista, id, listaOrdensServico);
            break;
        // Listagem de todos os agendamentos
        case 5:
            listarTodosAgendamentosModel(lista, listaOrdensServico);
            break;
        case 6:
            break;
        default: printf("Opção inválida!\n\n");
    }
}

// Formulário de deleção de agendamentos
void deletarAgendamento(struct ListaAgendamentos *lista, struct ListaOrdensServico *listaOrdensServico) {
    int id;

    // Pede o ID do agendamento que será deletada
    printf("\n====================================\n"
        "|     CANCELAMENTO DE AGENDAMENTO   |\n"
        "====================================\n");
    printf("Insira o ID do agendamento que deseja cancelar:");
    scanf("%d", &id);
    deletarAgendamentosModel(lista, id, listaOrdensServico);
}

void finalizarAgendamento(struct ListaAgendamentos *lista) {
    int id;

    printf("\n===================================\n"
       "|       FINALIZAR AGENDAMENTO     |\n"
       "===================================\n");
    printf("Qual agendamento deseja finalizar?");
    scanf("%d", &id);

    finalizarAgendamentoModel(lista, id);
}