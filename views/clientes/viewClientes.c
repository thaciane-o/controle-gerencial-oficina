#include "../../models/clientes/modelClientes.h"
#include "viewClientes.h"
#include <stdio.h>
#include "../../models/veiculos/modelVeiculos.h"

void gerenciarClientes(struct ListaClientes *lista, struct ListaVeiculos *listaVeiculos, int opcaoArmazenamento) {
    int opcaoSubmenus;

    if (opcaoArmazenamento != 3) {
        if (lista->qtdClientes == 0) {
            buscarDadosClientesModel(lista, opcaoArmazenamento);
        }
        if (lista->qtdClientes > 0) {
            buscarDadosVeiculosModel(listaVeiculos, opcaoArmazenamento);
        }
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
                cadastrarCliente(lista);
                break;
            case 2:
                atualizarCliente(lista);
                break;
            case 3:
                deletarCliente(lista, listaVeiculos);
                break;
            case 4:
                listarClientes(lista);
                break;
            case 5:
                if (opcaoArmazenamento != 3) {
                    if (lista->qtdClientes > 0) {
                        armazenarDadosClienteModel(lista, opcaoArmazenamento);
                    }
                }
                return;
            default:
                printf("\nOpção inválida!");
                break;
        }
    } while (opcaoSubmenus != 5);
}

void cadastrarCliente(struct ListaClientes *lista) {
    struct Clientes cliente;

    printf("\n=================================\n"
        "|     CADASTRO DE CLIENTE    |\n"
        "=================================\n");


    printf("Insira o nome do cliente: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", cliente.nome);

    printf("Insira o DDD do cliente: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", cliente.ddd);

    printf("Insira número de telefone do cliente: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", cliente.telefone);

    printf("Insira o CPF do cliente: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", cliente.cpf);

    printf("Insira o email do cliente: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", cliente.email);

    printf("Insira o endereço do cliente: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", cliente.endereco);

    cadastrarClientesModel(lista, &cliente);
}

void atualizarCliente(struct ListaClientes *lista) {
    int id;
    struct Clientes cliente;

    printf("\n=================================\n"
        "|     ATUALIZAÇÃO DE CLIENTE    |\n"
        "=================================\n"
        "Insira o cliente que deseja atualizar: ");
    scanf("%d", &id);

    int encontrado = verificarIDClienteModel(lista, id);
    if (encontrado == 0) {
        return;
    }

    printf("Insira o nome do cliente: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", cliente.nome);

    printf("Insira o DDD do cliente: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", cliente.ddd);

    printf("Insira número de telefone do cliente: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", cliente.telefone);

    printf("Insira o CPF do cliente: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", cliente.cpf);

    printf("Insira o email do cliente: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", cliente.email);

    printf("Insira o endereço do cliente: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", cliente.endereco);

    atualizarClientesModel(lista, id, &cliente);
}

void listarClientes(struct ListaClientes *lista) {
    int opcao, id;

    printf("==================\n"
        "| 1 | Busca por ID\n"
        "| 2 | Listar todos\n"
        "| 3 | Voltar\n"
        "==================\n"
        "Opção desejada: ");
    setbuf(stdin, NULL);
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            printf("Insira o cliente que deseja lista: ");
            scanf("%d", &id);
            listarClienteModel(lista, id);
            break;
        case 2:
            listarTodosClientesModel(lista);
            break;
        case 3:
            break;
        default:
            printf("Opção inválida, voltando ao menu principal.\n");
            break;
    }
}

void deletarCliente(struct ListaClientes *lista, struct ListaVeiculos *listaVeiculos) {
    int id;

    printf("\n=================================\n"
        "|     DELEÇÃO DE CLIENTE    |\n"
        "=================================\n");
    printf("Insira o cliente que deseja deletar:");
    scanf("%d", &id);
    deletarClientesModel(lista, listaVeiculos, id);
}
