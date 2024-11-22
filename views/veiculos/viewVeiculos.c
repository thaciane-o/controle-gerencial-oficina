#include "../../models/veiculos/modelVeiculos.h"
#include "../../models/clientes/modelClientes.h"
#include "viewVeiculos.h"
#include <stdio.h>
#include <stdlib.h>

void gerenciarVeiculos(struct ListaClientes *listaProprietarios, struct ListaVeiculos *lista, int opcaoArmazenamento) {
    int opcaoSubmenus;

    if (opcaoArmazenamento != 3) {
        if (lista->qtdVeiculos == 0){
            buscarDadosVeiculosModel(lista, opcaoArmazenamento);
        }
        if (listaProprietarios->qtdClientes == 0) {
            buscarDadosClientesModel(listaProprietarios, opcaoArmazenamento);
        }
    }

    do {
        printf("==================================\n"
            "|       SUBMENU DE VEÍCULO       |\n"
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
                cadastrarVeiculo(listaProprietarios, lista, opcaoArmazenamento);
                break;
            case 2:
                atualizarVeiculo(listaProprietarios, lista, opcaoArmazenamento);
                break;
            case 3:
                deletarVeiculo(lista);
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

void cadastrarVeiculo(struct ListaClientes *listaProprietarios, struct ListaVeiculos *lista, int opcaoArmazenamento) {
    struct Veiculos veiculo;
    int idProprietario;

    printf("\n==============================\n"
        "|     CADASTRO DE VEÍCULO    |\n"
        "==============================\n");

    printf("Qual o ID do proprietário?");
    setbuf(stdin, NULL);
    scanf("%d", &veiculo.idProprietario);


    //Verifica se o ID é válido
    if (idProprietario <= 0) {
        printf("ID de proprietário invalido!\n");
        return;
    }


    //verificando existencia de cliente
    if (verificarIDClienteModel(listaProprietarios, idProprietario) == 0) {
        return;
    }

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

void atualizarVeiculo(struct ListaClientes *listaProprietarios, struct ListaVeiculos *lista, int opcaoArmazenamento) {
    struct Veiculos veiculo;
    int id, idProprietario;

    printf("\n=================================\n"
        "|     ATUALIZAÇÃO DE VEÍCULO    |\n"
        "=================================\n"
        "Insira o veículo que deseja atualizar: ");
    scanf("%d", &id);

    printf("\nQual o ID do proprietário? ");
    setbuf(stdin, NULL);
    scanf("%d", &idProprietario);

    //Verifica se o ID é válido
    if (idProprietario <= 0) {
        printf("ID de proprietario invalido!\n");
        return;
    }


    if (verificarIDClienteModel(listaProprietarios, idProprietario) == 0) {
        return;
    }

    veiculo.idProprietario = idProprietario;

    int encontrado = verificarIDVeiculoModel(lista, id);
    if (encontrado == 0) {
        return;
    }

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


    atualizarVeiculosModel(lista, id, &veiculo);
}

void listarVeiculo(struct ListaVeiculos *lista) {
    int opcao, id;

    printf("\n===============================\n"
        "|     LISTAGEM DE VEÍCULO     |\n"
        "===============================\n"
        "| 1 | Busca por ID            |\n"
        "| 2 | Listar todos            |\n"
        "| 3 | Listar por proprietário |\n"
        "| 4 | Voltar                  |\n"
        "===============================\n"
        "Opção desejada: ");
    setbuf(stdin, NULL);
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            printf("Insira o veículo que deseja lista: ");
            scanf("%d", &id);
            buscarIdClienteModel(lista, id);
            break;
        case 2:
            listarTodosVeiculosModel(lista);
            break;
        case 3:
            printf("Insira o ID do proprietário dos veículos: ");
            scanf("%d", &id);
            listarVeiculosPorClienteModel(lista, id);
            break;
        case 4:
            break;
        default:
            printf("Opção inválida, voltando ao menu principal.\n\n");
            break;
    }
}

void deletarVeiculo(struct ListaVeiculos *lista) {
    int id;

    printf("\n=================================\n"
        "|       DELEÇÃO DE VEÍCULO      |\n"
        "=================================\n");
    printf("Insira o veículo que deseja deletar:");
    scanf("%d", &id);
    deletarVeiculosModel(lista, id);
}
