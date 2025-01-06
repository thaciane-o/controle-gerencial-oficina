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
#include <time.h>

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
            "|  5  | Finalizar serviço        |\n"
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
                atualizarAgendamento(lista, listaFuncionarios, listaServicos, listaVeiculos, listaPecas,
                                     listaOrdensServico);
                break;
            case 3:
                deletarAgendamento(lista, listaOrdensServico);
                break;
            case 4:
                listarAgendamentos(lista, listaOrdensServico);
                break;
            case 5:
                finalizarOrdemServico(lista, listaOrdensServico);
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
    int idFuncionario, idVeiculo, qtdServicos = 0, idInputServico, qtdPecas = 0, idInputPecas, dia, mes, ano, hora,
            minuto;
    int *idServicos = malloc(sizeof(int));
    int *idPecas = malloc(sizeof(int));
    int *idPecaDoServico = malloc(sizeof(int));
    struct PagamentosCliente pagamento;
    pagamento.valor = 0;
    struct tm dataHora = {0};

    printf("\n======================\n"
        "|     AGENDAMENTO    |\n"
        "======================\n");

    do {
        // Agendando 1 ou mais serviços
        if (qtdServicos > 1) {
            idServicos = realloc(idServicos, qtdServicos * sizeof(int));
        }
        qtdServicos++;
        printf("Insira o ID do serviço que será agendado (0 para finalizar): ");
        setbuf(stdin, NULL);
        scanf("%d", &idInputServico);

        // Verificando existência do item relacionado
        if (idInputServico != 0) {
            idServicos[qtdServicos - 1] = idInputServico;
            verificarIDServicoModel(listaServicos, idServicos[qtdServicos - 1]);

            do {
                // Inserindo 1 ou mais peças por serviço
                if (qtdPecas > 1) {
                    idPecas = realloc(idPecas, qtdPecas * sizeof(int));
                    idPecaDoServico = realloc(idPecaDoServico, qtdPecas * sizeof(int));
                }
                qtdPecas++;

                printf("Insira o ID da peça que será necessária para realizar esse serviço (0 para finalizar): ");
                setbuf(stdin, NULL);
                scanf("%d", &idInputPecas);

                // Verificando existência do item relacionado
                if (idInputPecas != 0) {
                    idPecas[qtdPecas - 1] = idInputPecas;
                    verificarIDPecaModel(listaPecas, idPecas[qtdPecas - 1]);
                    idPecaDoServico[qtdPecas - 1] = idInputServico;
                } else {
                    qtdPecas--;
                }
            } while (idInputPecas != 0);
        } else {
            qtdServicos--;
        }
    } while (idInputServico != 0);

    if (qtdServicos >= 1 && qtdPecas >= 1) {
        printf("Insira o ID do funcionário que fará o serviço: ");
        setbuf(stdin, NULL);
        scanf("%d", &idFuncionario);

        printf("Insira o ID do veículo a receber o serviço: ");
        setbuf(stdin, NULL);
        scanf("%d", &idVeiculo);

        // Verificando existência do item relacionado
        if (verificarIDFuncionariosModel(listaFuncionarios, idFuncionario) == 0) {
            return;
        }

        if (verificarIDVeiculoModel(listaVeiculos, idVeiculo) == 0) {
            return;
        }

        agendamento.idFuncionario = idFuncionario;
        agendamento.idVeiculo = idVeiculo;

        // Preenchimento dos dados
        printf("Insira a data desejada para realizar o serviço (DD/MM/AAAA): ");
        setbuf(stdin, NULL);
        scanf("%d/%d/%d", &dia, &mes, &ano);

        printf("Insira a hora desejada para realizar o serviço (HH:MM): ");
        setbuf(stdin, NULL);
        scanf("%d:%d", &hora, &minuto);

        dataHora.tm_mday = dia;
        dataHora.tm_mon = mes - 1;
        dataHora.tm_year = ano - 1900;
        dataHora.tm_hour = hora;
        dataHora.tm_min = minuto;
        dataHora.tm_sec = 0;

        time_t tempo = mktime(&dataHora);

        if (tempo == -1) {
            printf("Erro ao converter a data e hora.\n");
            return;
        }

        // Verificando se um funcionário já possui um serviço na data e hora inserida
        for (int i = 0; i < lista->qtdAgendamentos; i++) {
            sscanf(lista->listaAgendamentos[i].datahoraInicial, "%d/%d/%d %d:%d",
                   &dataHora.tm_mday, &dataHora.tm_mon, &dataHora.tm_year,
                   &dataHora.tm_hour, &dataHora.tm_min);

            dataHora.tm_year -= 1900;
            dataHora.tm_mon -= 1;
            time_t tempoExistente = mktime(&dataHora);

            if (tempoExistente == -1) {
                printf("Erro ao converter a data e hora.\n");
                return;
            }

            if (lista->listaAgendamentos[i].idFuncionario == idFuncionario && tempoExistente == tempo) {
                printf("Não é possível agendar um serviço com esse funcionário.\n\n");

                // Limpando os ponteiros
                idPecas = NULL;
                idPecaDoServico = NULL;
                free(idPecas);
                free(idPecaDoServico);

                idServicos = NULL;
                free(idServicos);
                return;
            }
        }

        strftime(agendamento.datahoraInicial, sizeof(agendamento.datahoraInicial), "%d/%m/%Y %H:%M", &dataHora);

        // Cadastrando agendamentos de cada serviço inserido
        for (int i = 0; i < qtdServicos; i++) {
            agendamento.idServico = idServicos[i];
            cadastrarAgendamentosModel(lista, &agendamento);

            strcpy(ordensServico.descricao, listaServicos->listaServicos[i].descricao);
            ordensServico.idAgendamentos = lista->qtdAgendamentos;
            ordensServico.valorTotal = listaServicos->listaServicos[i].preco;

            // Cadastrando ordens de serviço de cada peça inserida
            for (int j = 0; j < qtdPecas; j++) {
                if (idPecaDoServico[j] == idServicos[i]) {
                    ordensServico.valorTotal += listaPecas->listaPecas[j].precoVenda;
                    ordensServico.idPecas = idPecas[j];
                    cadastrarOrdensServicoModel(listaOrdensServico, &ordensServico);
                }
            }
        }

        printf("Agendamento realizado com sucesso para a data %s!\n\n", agendamento.datahoraInicial);
        printf("Ordem de serviço emitida com sucesso!\n\n");
    } else {
        printf("Nenhum serviço agendado!\n\n");
    }

    // Limpando os ponteiros
    idPecas = NULL;
    idPecaDoServico = NULL;
    free(idPecas);
    free(idPecaDoServico);

    idServicos = NULL;
    free(idServicos);
}

// Formulário de atualização de agendamentos
void atualizarAgendamento(struct ListaAgendamentos *lista, struct ListaFuncionarios *listaFuncionarios,
                          struct ListaServicos *listaServicos, struct ListaVeiculos *listaVeiculos,
                          struct ListaPecas *listaPecas, struct ListaOrdensServico *listaOrdensServico) {
    int id, idFuncionario, idVeiculo, idServico, dia, mes, ano, hora, minuto, idInputPecas, qtdPecas = 0;
    struct Agendamentos agendamento;
    struct OrdensServico ordensServico;
    int *idPecas = malloc(sizeof(int));
    struct tm dataHora = {0};

    // Pede o ID do agendamento que será atualizado
    printf("\n=====================================\n"
        "|     ATUALIZAÇÃO DE AGENDAMENTO    |\n"
        "=====================================\n"
        "Insira o ID do agendamento que deseja atualizar: ");
    scanf("%d", &id);

    deletarOrdensServicoModel(listaOrdensServico, id);

    // Verifica se o ID inserido existe
    int encontrado = verificarIDAgendamentoModel(lista, id);
    if (encontrado == 0) {
        return;
    }

    printf("Insira o ID do serviço que será agendado: ");
    setbuf(stdin, NULL);
    scanf("%d", &idServico);

    do {
        // Inserindo 1 ou mais peças por serviço
        if (qtdPecas > 1) {
            idPecas = realloc(idPecas, qtdPecas * sizeof(int));
        }
        qtdPecas++;

        printf("Insira o ID da peça que será necessária para realizar esse serviço (0 para finalizar): ");
        setbuf(stdin, NULL);
        scanf("%d", &idInputPecas);

        // Verificando existência do item relacionado
        if (idInputPecas != 0) {
            idPecas[qtdPecas - 1] = idInputPecas;
            verificarIDPecaModel(listaPecas, idInputPecas);
        } else {
            qtdPecas--;
        }
    } while (idInputPecas != 0);

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
    agendamento.idVeiculo = idVeiculo;

    // Preenchimento dos dados
    printf("Insira a data desejada para realizar o serviço (DD/MM/AAAA): ");
    setbuf(stdin, NULL);
    scanf("%d/%d/%d", &dia, &mes, &ano);

    printf("Insira a hora desejada para realizar o serviço (HH:MM): ");
    setbuf(stdin, NULL);
    scanf("%d:%d", &hora, &minuto);

    // Convertendo data e hora em struct tm
    dataHora.tm_mday = dia;
    dataHora.tm_mon = mes - 1;
    dataHora.tm_year = ano - 1900;
    dataHora.tm_hour = hora;
    dataHora.tm_min = minuto;
    dataHora.tm_sec = 0;

    // Convertendo struct tm em string
    strftime(agendamento.datahoraInicial, sizeof(agendamento.datahoraInicial), "%d/%m/%Y %H:%M", &dataHora);

    atualizarAgendamentosModel(lista, id, &agendamento);

    // Cadastrando ordens de serviço de cada peça inserida
    for (int i = 0; i < qtdPecas; i++) {
        strcpy(ordensServico.descricao, listaServicos->listaServicos[idServico].descricao);
        ordensServico.idAgendamentos = id;
        ordensServico.valorTotal = listaServicos->listaServicos[idServico].preco;
        ordensServico.valorTotal += listaPecas->listaPecas[i].precoVenda;
        ordensServico.idPecas = idPecas[i];
        cadastrarOrdensServicoModel(listaOrdensServico, &ordensServico);
    }

    idPecas = NULL;
    free(idPecas);
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

void finalizarOrdemServico(struct ListaAgendamentos *lista, struct ListaOrdensServico *listaOrdensServico) {
    int idAgendamento, idServico;

    printf("\n==================================\n"
        "|   FINALIZAR ORDEM DE SERVIÇO   |\n"
        "==================================\n");
    printf("Insira o ID do agendamento:");
    scanf("%d", &idAgendamento);

    printf("Qual serviço deseja finalizar:");
    scanf("%d", &idServico);

    finalizarOrdemServicoModel(listaOrdensServico, lista, idAgendamento, idServico);
}
