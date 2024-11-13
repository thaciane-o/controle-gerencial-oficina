#include "../../models/clientes/modelClientes.h"
#include "viewClientes.h"
#include <stdio.h>
#include <stdlib.h>

void gerenciarClientes(struct ListaClientes *lista) {
    int opcaoSubmenus;
    lista->qtdClientes = 0;

    do {
        if (lista->qtdClientes == 0) {
            buscarDadosClientesModel(lista);
        }
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
                deletarCliente(lista);
            break;
            case 4:
                listarClientes(lista);
            break;
            case 5:
                armazenarDadosClienteModel(lista);
            break;
            default: printf("\nOpção inválida!");
            break;
        }
    }while (opcaoSubmenus != 5);
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
    scanf(" %[^\n]", cliente.DDD);

    printf("Insira número de telefone do cliente: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", cliente.telefone);

    printf("Insira o CPF do cliente: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", cliente.CPF);

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

    printf("Insira o nome do cliente: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", cliente.nome);

    printf("Insira o DDD do cliente: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", cliente.DDD);

    printf("Insira número de telefone do cliente: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", cliente.telefone);

    printf("Insira o CPF do cliente: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", cliente.CPF);

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

    printf("\n=================================\n"
            "|     LISTAGEM DE CLIENTE    |\n"
            "=================================\n"
            "1. Listar um único cliente"
            "\n2. Listar todos\n");
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
        default: printf("Opção inválida!\n\n");
    }

}

void deletarCliente(struct ListaClientes *lista) {
    int id;

    printf("\n=================================\n"
             "|     DELEÇÃO DE CLIENTE    |\n"
             "=================================\n");
    printf("Insira o cliente que deseja deletar:");
    scanf("%d", &id);
    deletarClientesModel(lista, id);
}