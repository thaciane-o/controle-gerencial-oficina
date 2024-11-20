#include "../../models/veiculos/modelVeiculos.h"
#include "../../models/clientes/modelClientes.h"
#include "viewVeiculos.h"
#include <stdio.h>
#include <stdlib.h>

void gerenciarVeiculos(struct ListaClientes *listaProprietarios, struct ListaVeiculos *lista, int opcaoArmazenamento) {
    int opcaoSubmenus;

    if (lista->qtdVeiculos == 0 && opcaoArmazenamento != 3) {
        buscarDadosVeiculosModel(lista, opcaoArmazenamento);
    }

    do {
        printf("=================================\n"
            "|        MENU PRINCIPAL         |\n"
            "=================================\n"
            "|  1  | Cadastrar               |\n"
            "|  2  | Atualizar               |\n"
            "|  3  | Deletar                 |\n"
            "|  4  | Listar                  |\n"
            "|  5  | Voltar                  |\n"
            "=================================\n"
            "Escolha uma opção: ");
        scanf("%d", &opcaoSubmenus);

        switch (opcaoSubmenus) {
            case 1:
                cadastrarVeiculo(listaProprietarios, lista, opcaoArmazenamento);
                break;
            case 2:
                atualizarVeiculo(lista);
                break;
            case 3:
                deletarVeiculo(lista);
                break;
            case 4:
                listarVeiculo(lista);
                break;
            case 5:
                if (opcaoArmazenamento != 3 && lista->listaVeiculos != NULL) {
                    armazenarDadosVeiculosModel(lista, opcaoArmazenamento);
                }
                return;
            default:
                printf("\nOpção inválida!");
                break;
        }
    } while (opcaoSubmenus != 5);
}

void cadastrarVeiculo(struct ListaClientes *listaProprietarios, struct ListaVeiculos *lista, int opcaoArmazenamento) {
    struct Veiculos veiculo;

    printf("\n=================================\n"
        "|     CADASTRO DE VEICULO    |\n"
        "=================================\n");

    printf("Qual o ID do proprietario?");
    setbuf(stdin, NULL);
    scanf("%d", &veiculo.idProprietario);

    if (listaProprietarios->qtdClientes == 0 && opcaoArmazenamento != 3) {
        buscarDadosClientesModel(listaProprietarios, opcaoArmazenamento);
    }

    if (verificarIDClienteModel(listaProprietarios, veiculo.idProprietario) == 0) {
        if (opcaoArmazenamento != 3) {
            free(listaProprietarios->listaClientes);
        }
        return;
    }


    printf("Insira o modelo do veiculo: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", veiculo.modelo);

    printf("Insira a marca do veiculo: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", veiculo.marca);

    printf("Insira a placa do veiculo: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", veiculo.placa);

    printf("Insira o chassi do veiculo: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", veiculo.chassi);

    printf("Insira o ano de fabricação do veiculo: ");
    setbuf(stdin, NULL);
    scanf(" %d", &veiculo.anoFabricacao);


    cadastrarVeiculosModel(lista, &veiculo);
}

void atualizarVeiculo(struct ListaVeiculos *lista) {
    int id;
    struct Veiculos veiculo;

    printf("\n=================================\n"
        "|     ATUALIZAÇÃO DE VEICULO    |\n"
        "=================================\n"
        "Insira o veiculo que deseja atualizar: ");
    scanf("%d", &id);

    int encontrado = verificarIDVeiculoModel(lista, id);
    if (encontrado == 0) {
        return;
    }

    printf("Insira o modelo do veiculo: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", veiculo.modelo);

    printf("Insira a marca do veiculo: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", veiculo.marca);

    printf("Insira a placa do veiculo: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", veiculo.placa);

    printf("Insira o chassi do veiculo: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", veiculo.chassi);

    printf("Insira o ano de fabricação do veiculo: ");
    setbuf(stdin, NULL);
    scanf(" %d", &veiculo.anoFabricacao);


    atualizarVeiculosModel(lista, id, &veiculo);
}

void listarVeiculo(struct ListaVeiculos *lista) {
    int opcao, id;

    printf("==================\n"
        "| 1 | Busca por ID\n"
        "| 2 | Listar todos\n"
        "| 3 | Listar por cliente\n"
        "| 4 | Voltar\n"
        "==================\n"
        "Opção desejada: ");
    setbuf(stdin, NULL);
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            printf("Insira o veiculo que deseja lista: ");
            scanf("%d", &id);
            listarVeiculoModel(lista, id);
            break;
        case 2:
            listarTodosVeiculosModel(lista);
            break;
        case 3:
            printf("Insira o ID do proprietario dos veiculos: ");
            scanf("%d", &id);
            listarVeiculosPorClienteModel(lista, id);
            break;
        case 4:
            break;
        default:
            printf("Opção inválida, voltando ao menu principal.\n");
            break;
    }
}

void deletarVeiculo(struct ListaVeiculos *lista) {
    int id;

    printf("\n=================================\n"
        "|     DELEÇÃO DE VEICULO    |\n"
        "=================================\n");
    printf("Insira o veiculo que deseja deletar:");
    scanf("%d", &id);
    deletarVeiculosModel(lista, id);
}
