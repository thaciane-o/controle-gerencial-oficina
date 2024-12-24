#include "../../models/agendamentos/modelAgendamentos.h"
#include "../../models/veiculos/modelVeiculos.h"
#include "../../models/funcionarios/modelFuncionarios.h"
#include "../../models/servicos/modelServicos.h"
#include "viewAgendamentos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Menu de funcionalidades de agentamentos
void gerenciarAgendamentos(struct ListaAgendamentos *lista, struct ListaFuncionarios *listaFuncionarios,
                           struct ListaServicos *listaServicos, struct ListaVeiculos *listaVeiculos,
                           int opcaoArmazenamento) {
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
    }

    do {
        printf("\n==================================\n"
            "|      MENU DE AGENDAMENTOS      |\n"
            "==================================\n"
            "|  1  | Agendar                  |\n"
            "|  2  | Atualizar agendamento    |\n"
            "|  3  | Cancelar agendamento     |\n"
            "|  4  | Listar agendamento       |\n"
            "|  5  | Voltar                   |\n"
            "==================================\n"
            "Escolha uma opção: ");
        scanf("%d", &opcaoSubmenus);

        switch (opcaoSubmenus) {
            case 1:
                cadastrarAgendamentos(lista, listaFuncionarios, listaServicos, listaVeiculos);
                break;
            case 2:
                atualizarAgendamento(lista, listaFuncionarios, listaServicos, listaVeiculos);
                break;
            case 3:
                deletarAgendamento(lista);
                break;
            case 4:
                listarAgendamentos(lista);
                break;
            case 5:
                if (opcaoArmazenamento != 3 && lista->listaAgendamentos != NULL) {
                    if (lista->qtdAgendamentos > 0) {
                        armazenarDadosAgendamentosModel(lista, opcaoArmazenamento);
                    }

                    if (listaVeiculos->qtdVeiculos > 0) {
                        free(listaVeiculos->listaVeiculos);
                        listaVeiculos->listaVeiculos = NULL;
                        listaVeiculos->qtdVeiculos = 0;
                    }

                    if (listaServicos->qtdServicos > 0) {
                        free(listaServicos->listaServicos);
                        listaServicos->listaServicos = NULL;
                        listaServicos->qtdServicos = 0;
                    }

                    if (listaFuncionarios->qtdFuncionarios > 0) {
                        free(listaFuncionarios->listaFuncionarios);
                        listaFuncionarios->listaFuncionarios = NULL;
                        listaFuncionarios->qtdFuncionarios = 0;
                    }
                }
                return;
            default:
                printf("Opção inválida!\n\n");
                break;
        }
    } while (opcaoSubmenus != 5);
}

// Formulário de cadastro de agendamentos
void cadastrarAgendamentos(struct ListaAgendamentos *lista, struct ListaFuncionarios *listaFuncionarios,
                           struct ListaServicos *listaServicos, struct ListaVeiculos *listaVeiculos) {
    struct Agendamentos agendamento;
    int idFuncionarios, idServicos, idVeiculos;

    printf("\n=====================\n"
        "|     AGENDAMENTO    |\n"
        "=====================\n");

    printf("Insira o ID do serviço que será agendado: ");
    setbuf(stdin, NULL);
    scanf("%d", &idServicos);

    printf("Insira o ID do funcionário que fará o serviço: ");
    setbuf(stdin, NULL);
    scanf("%d", &idFuncionarios);

    printf("Insira o ID do veículo a receber o serviço: ");
    setbuf(stdin, NULL);
    scanf("%d", &idVeiculos);

    // Verificando existência do item relacionado
    if (verificarIDServicoModel(listaServicos, idServicos) == 0) {
        return;
    }

    if (verificarIDFuncionariosModel(listaFuncionarios, idFuncionarios) == 0) {
        return;
    }

    if (verificarIDVeiculoModel(listaVeiculos, idVeiculos) == 0) {
        return;
    }

    agendamento.idFuncionario = idFuncionarios;
    agendamento.idServico = idServicos;
    agendamento.idVeiculo = idServicos;

    // Preenchimento dos dados
    printf("Insira a data prevista para realizar o serviço (DD/MM/YYYY): ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", agendamento.data);

    printf("Insira a hora prevista para realizar o serviço (HH:MM): ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", agendamento.hora);

    for (int i = 0; i < lista->qtdAgendamentos; i++) {
        if (lista->listaAgendamentos[i].idFuncionario == idFuncionarios &&
            strcmp(lista->listaAgendamentos[i].data, agendamento.data) == 0 &&
            strcmp(lista->listaAgendamentos[i].hora, agendamento.hora) == 0) {
            printf("Não é possível agendar um serviço com esse funcionário.\n\n");
            return;
        }
    }

    cadastrarAgendamentosModel(lista, &agendamento);
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
void listarAgendamentos(struct ListaAgendamentos *lista) {
    int opcao, id;

    // Pergunta o tipo de listagem
    printf("\n=================================\n"
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
            listarAgendamentoModel(lista, id);
            break;
        // Listagem por relação
        case 2:
            printf("Insira o ID do funcionário desejado para a busca: ");
            setbuf(stdin, NULL);
            scanf("%d", &id);
            buscarAgendamentosPorFuncionarioModel(lista, id);
            break;
        case 3:
            printf("Insira o ID do veículo desejado para a busca: ");
            setbuf(stdin, NULL);
            scanf("%d", &id);
            buscarAgendamentosPorVeiculoModel(lista, id);
            break;
        case 4:
            printf("Insira o ID do serviço desejado para a busca: ");
            setbuf(stdin, NULL);
            scanf("%d", &id);
            buscarAgendamentosPorServicoModel(lista, id);
            break;
        // Listagem de todos os agendamentos
        case 5:
            listarTodosAgendamentosModel(lista);
            break;
        case 6:
            break;
        default: printf("Opção inválida!\n\n");
    }
}

// Formulário de deleção de agendamentos
void deletarAgendamento(struct ListaAgendamentos *lista) {
    int id;

    // Pede o ID do agendamento que será deletada
    printf("\n====================================\n"
        "|     CANCELAMENTO DE AGENDAMENTO   |\n"
        "====================================\n");
    printf("Insira o ID do agendamento que deseja cancelar:");
    scanf("%d", &id);
    deletarAgendamentosModel(lista, id);
}
