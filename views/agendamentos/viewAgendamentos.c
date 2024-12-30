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
                           struct ListaOrdensServico *listaOrdensServico, struct ListaPecas *listaPecas,
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

        if (listaOrdensServico->qtdOrdensServico == 0) {
            buscarDadosOrdensServicoModel(listaOrdensServico, opcaoArmazenamento);
        }

        if (listaPecas->qtdPecas == 0) {
            buscarDadosPecaModel(listaPecas, opcaoArmazenamento);
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
                cadastrarAgendamentos(lista, listaFuncionarios, listaServicos, listaVeiculos, listaOrdensServico, listaPecas);
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
                           struct ListaServicos *listaServicos, struct ListaVeiculos *listaVeiculos,
                           struct ListaOrdensServico *listaOrdensServico, struct ListaPecas *listaPecas) {
    struct Agendamentos agendamento;
    struct OrdensServico ordensServico;
    int idFuncionarios, idVeiculos, qtdServicos = 0, idInputServico, qtdPecas = 0, idInputPecas;
    int *idServicos = malloc(sizeof(int));
    int *idPecas = malloc(sizeof(int));

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
        printf("Insira a data prevista para realizar o serviço (DD/MM/YYYY): ");
        setbuf(stdin, NULL);
        scanf(" %[^\n]", agendamento.data);

        printf("Insira a hora prevista para realizar o serviço (HH:MM): ");
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
