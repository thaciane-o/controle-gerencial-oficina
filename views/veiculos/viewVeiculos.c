#include "../../models/veiculos/modelVeiculos.h"
#include "../../models/clientes/modelClientes.h"
#include "../../models/agendamentos/modelAgendamentos.h"
#include "viewVeiculos.h"
#include <stdio.h>
#include <stdlib.h>

// Menu de funcionalidades de veículos
void gerenciarVeiculos(struct ListaClientes *listaProprietarios, struct ListaVeiculos *lista,
                       struct ListaAgendamentos *listaAgendamentos, int opcaoArmazenamento) {
    int opcaoSubmenus;
    //Verifica se o programa esta rodando apenas em memória
    if (opcaoArmazenamento != 3) {
        // Busca os dados armazenados em arquivos
        if (lista->qtdVeiculos == 0) {
            buscarDadosVeiculosModel(lista, opcaoArmazenamento);
        }
        // Busca os dados em arquivos das tabelas relacionadas
        if (listaProprietarios->qtdClientes == 0) {
            buscarDadosClientesModel(listaProprietarios, opcaoArmazenamento);
        }

        if (lista->qtdVeiculos > 0) {
            buscarDadosAgendamentosModel(listaAgendamentos, opcaoArmazenamento);
        }
    }

    do {
        printf("\n==================================\n"
            "|        MENU DE VEÍCULOS        |\n"
            "==================================\n"
            "|  1  | Cadastrar                |\n"
            "|  2  | Atualizar                |\n"
            "|  3  | Deletar                  |\n"
            "|  4  | Listar                   |\n"
            "|  5  | Voltar                   |\n"
            "==================================\n"
            "Escolha uma opção: ");
        scanf("%d", &opcaoSubmenus);

        switch (opcaoSubmenus) {
            case 1:
                cadastrarVeiculo(listaProprietarios, lista);
                break;
            case 2:
                atualizarVeiculo(listaProprietarios, lista);
                break;
            case 3:
                deletarVeiculo(lista, listaAgendamentos);
                break;
            case 4:
                listarVeiculo(lista);
                break;
            case 5:
                if (opcaoArmazenamento != 3) {
                    if (lista->qtdVeiculos > 0) {
                        armazenarDadosVeiculosModel(lista, opcaoArmazenamento);
                    }
                    if (listaProprietarios->qtdClientes > 0) {
                        free(listaProprietarios->listaClientes);
                        listaProprietarios->listaClientes = NULL;
                        listaProprietarios->qtdClientes = 0;
                    }
                }
                return;
            default:
                printf("Opção inválida.\n\n");
                break;
        }
    } while (opcaoSubmenus != 5);
}

// Formulário de cadastro de veículos
void cadastrarVeiculo(struct ListaClientes *listaProprietarios, struct ListaVeiculos *lista) {
    struct Veiculos veiculo;
    int idProprietario;

    printf("\n==============================\n"
        "|     CADASTRO DE VEÍCULO    |\n"
        "==============================\n");

    printf("Insira o ID do proprietário: ");
    setbuf(stdin, NULL);
    scanf("%d", &idProprietario);


    // Verificando existência do item relacionado
    if (verificarIDClienteModel(listaProprietarios, idProprietario) == 0) {
        return;
    }

    veiculo.idProprietario = idProprietario;

    // Preenchimento dos dados
    printf("Insira o modelo do veículo: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", veiculo.modelo);

    printf("Insira a marca do veículo: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", veiculo.marca);

    printf("Insira a placa do veículo: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", veiculo.placa);

    printf("Insira o chassi do veículo: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", veiculo.chassi);

    printf("Insira o ano de fabricação do veículo: ");
    setbuf(stdin, NULL);
    scanf(" %d", &veiculo.anoFabricacao);


    cadastrarVeiculosModel(lista, &veiculo);
}

// Formulário de atualização de veículos
void atualizarVeiculo(struct ListaClientes *listaProprietarios, struct ListaVeiculos *lista) {
    struct Veiculos veiculo;
    int idVeiculo, idProprietario;

    // Pede o Id do veículo que será atualizado
    printf("\n=================================\n"
        "|     ATUALIZAÇÃO DE VEÍCULO    |\n"
        "=================================\n"
        "Insira o veículo que deseja atualizar: ");
    scanf("%d", &idVeiculo);

    // Verifica se o ID inserido existe
    if (verificarIDVeiculoModel(lista, idVeiculo) == 0) {
        return;
    }

    printf("Insira o ID do proprietário:  ");
    setbuf(stdin, NULL);
    scanf("%d", &idProprietario);


    if (verificarIDClienteModel(listaProprietarios, idProprietario) == 0) {
        return;
    }

    veiculo.idProprietario = idProprietario;

    //Preenchimento dos dados
    printf("Insira o modelo do veículo: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", veiculo.modelo);

    printf("Insira a marca do veículo: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", veiculo.marca);

    printf("Insira a placa do veículo: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", veiculo.placa);

    printf("Insira o chassi do veículo: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", veiculo.chassi);

    printf("Insira o ano de fabricação do veículo: ");
    setbuf(stdin, NULL);
    scanf(" %d", &veiculo.anoFabricacao);


    atualizarVeiculosModel(lista, idVeiculo, &veiculo);
}

// Listagem de veículos
void listarVeiculo(struct ListaVeiculos *lista) {
    int opcao, id;
    // Pergunta o tipo de listagem
    printf("\n=====================================\n"
        "|        LISTAGEM DE VEÍCULO        |\n"
        "=====================================\n"
        "| 1 | Busca por ID                  |\n"
        "| 2 | Listar por ID do proprietário |\n"
        "| 3 | Listar todos                  |\n"
        "| 4 | Voltar                        |\n"
        "=====================================\n"
        "Opção desejada: ");
    setbuf(stdin, NULL);
    scanf("%d", &opcao);

    // Verifica a opção de listagem
    switch (opcao) {
        // Listagem de um único veículo
        case 1:
            printf("Insira o veículo que deseja lista: ");
            scanf("%d", &id);
            listarVeiculoModel(lista, id);
            break;
        // Listagem por relação
        case 2:
            printf("Insira o ID do proprietário dos veículos: ");
            scanf("%d", &id);
            buscarVeiculosPorClienteModel(lista, id);
            break;
        // Listagem de todos os veículos
        case 3:
            listarTodosVeiculosModel(lista);
            break;
        case 4:
            break;
        default:
            printf("Opção inválida, voltando ao menu principal.\n\n");
            break;
    }
}

// Formulário de deleção de veículos
void deletarVeiculo(struct ListaVeiculos *lista, struct ListaAgendamentos *listaAgendamentos) {
    int id;
    // Pede o Id do veículo que será deletada
    printf("\n=================================\n"
        "|       DELEÇÃO DE VEÍCULO      |\n"
        "=================================\n");
    printf("Insira o ID veículo que deseja deletar:");
    scanf("%d", &id);
    deletarVeiculosModel(lista, listaAgendamentos, id);
}
