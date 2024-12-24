#include "../../models/agendamentos/modelAgendamentos.h"
#include "../../models/veiculos/modelVeiculos.h"
#include "../../models/funcionarios/modelFuncionarios.h"
#include "../../models/servicos/modelServicos.h"
#include "viewAgendamentos.h"
#include <stdio.h>
#include <stdlib.h>

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
                //atualizarCliente(lista, listaOficinas);
                break;
            case 3:
                //deletarCliente(lista, listaVeiculos);
                break;
            case 4:
                //listarClientes(lista);
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

    printf("\n==================\n"
        "|     AGENDAR    |\n"
        "==================\n");

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

    cadastrarAgendamentosModel(lista, &agendamento);
}
