#include "../../models/clientes/modelClientes.h"
#include "../../models/oficina/modelOficina.h"
#include "viewClientes.h"
#include <stdio.h>
#include <stdlib.h>

#include "../../models/veiculos/modelVeiculos.h"

// Menu de funcionalidades de clientes
void gerenciarClientes(struct ListaClientes *lista, struct ListaVeiculos *listaVeiculos,
                       struct ListaOficinas *listaOficinas, int opcaoArmazenamento) {
    int opcaoSubmenus;
    //Verifica se o programa esta rodando apenas em memória
    if (opcaoArmazenamento != 3) {
        // Busca os dados armazenados em arquivos
        if (lista->qtdClientes == 0) {
            buscarDadosClientesModel(lista, opcaoArmazenamento);
        }
        // Busca os dados em arquivos das tabelas relacionadas
        if (lista->qtdClientes > 0) {
            buscarDadosVeiculosModel(listaVeiculos, opcaoArmazenamento);
        }
        if (listaOficinas->qtdOficinas == 0) {
            buscarDadosOficinaModel(listaOficinas, opcaoArmazenamento);
        }
    }

    do {
        printf("\n==================================\n"
            "|        MENU DE CLIENTES        |\n"
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
                cadastrarCliente(lista, listaOficinas);
                break;
            case 2:
                atualizarCliente(lista, listaOficinas);
                break;
            case 3:
                deletarCliente(lista, listaVeiculos);
                break;
            case 4:
                listarClientes(lista);
                break;
            case 5:
                if (opcaoArmazenamento != 3 && lista->listaClientes != NULL) {
                    if (lista->qtdClientes > 0) {
                        armazenarDadosClienteModel(lista, opcaoArmazenamento);
                    }
                    if (listaOficinas->qtdOficinas > 0) {
                        free(listaOficinas->listaOficinas);
                        listaOficinas->listaOficinas = NULL;
                        listaOficinas->qtdOficinas = 0;
                    }
                    if (listaVeiculos->qtdVeiculos > 0) {
                        free(listaVeiculos->listaVeiculos);
                        listaVeiculos->listaVeiculos = NULL;
                        listaVeiculos->qtdVeiculos = 0;
                    }
                }
                return;
            default:
                printf("Opção inválida!\n\n");
                break;
        }
    } while (opcaoSubmenus != 5);
}

// Formulário de cadastro de clientes
void cadastrarCliente(struct ListaClientes *lista, struct ListaOficinas *listaOficinas) {
    struct Clientes cliente;
    int idOficina;

    printf("\n===============================\n"
        "|     CADASTRO DE CLIENTE     |\n"
        "===============================\n");

    printf("Insira o ID da oficina que atende este cliente: ");
    setbuf(stdin, NULL);
    scanf("%d", &idOficina);

    // Verificando existência do item relacionado
    if (verificarIDOficinaModel(listaOficinas, idOficina) == 0) {
        return;
    }

    cliente.idOficina = idOficina;

    // Preenchimento dos dados
    printf("Insira o nome do cliente: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", cliente.nome);

    printf("Insira o DDD do cliente: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", cliente.ddd);

    printf("Insira número de telefone do cliente: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", cliente.telefone);

    printf("Insira o CPF/CNPJ do cliente: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", cliente.cpf_cnpj);

    printf("Insira o email do cliente: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", cliente.email);

    printf("Insira o endereço do cliente: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", cliente.endereco);

    cadastrarClientesModel(lista, &cliente, 1);
}

// Formulário de atualização de clientes
void atualizarCliente(struct ListaClientes *lista, struct ListaOficinas *listaOficinas) {
    int id, idOficina;
    struct Clientes cliente;

    // Pede o Id do cliente que será atualizado
    printf("\n=================================\n"
        "|     ATUALIZAÇÃO DE CLIENTE    |\n"
        "=================================\n"
        "Insira o ID do cliente que deseja atualizar: ");
    scanf("%d", &id);

    // Verifica se o ID inserido existe
    int encontrado = verificarIDClienteModel(lista, id);
    if (encontrado == 0) {
        return;
    }

    printf("Insira o ID da oficina que atende este cliente: ");
    setbuf(stdin, NULL);
    scanf("%d", &idOficina);

    if (verificarIDOficinaModel(listaOficinas, idOficina) == 0) {
        return;
    }

    cliente.idOficina = idOficina;

    //Preenchimento dos dados
    printf("Insira o nome do cliente: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", cliente.nome);

    printf("Insira o DDD do cliente: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", cliente.ddd);

    printf("Insira número de telefone do cliente: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", cliente.telefone);

    printf("Insira o CPF/CNPJ do cliente: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", cliente.cpf_cnpj);

    printf("Insira o email do cliente: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", cliente.email);

    printf("Insira o endereço do cliente: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", cliente.endereco);

    atualizarClientesModel(lista, id, &cliente);
}

// Listagem de clientes
void listarClientes(struct ListaClientes *lista) {
    int opcao, id;
    // Pergunta o tipo de listagem
    printf("\n=================================\n"
        "|    LISTAGEM DE CLIENTES      |\n"
        "=================================\n"
        "| 1 | Busca por ID              |\n"
        "| 2 | Busca por ID da oficina   |\n"
        "| 3 | Listar todos              |\n"
        "| 4 | Voltar                    |\n"
        "=================================\n"
        "Escolha uma opção: ");
    setbuf(stdin, NULL);
    scanf("%d", &opcao);

    // Verifica a opção de listagem
    switch (opcao) {
        // Listagem de um único cliente
        case 1:
            printf("Insira o ID do cliente que deseja listar: ");
            setbuf(stdin, NULL);
            scanf("%d", &id);
            listarClienteModel(lista, id);
            break;
        // Listagem por relação
        case 2:
            printf("Insira o ID da oficina desejada para a busca: ");
            setbuf(stdin, NULL);
            scanf("%d", &id);
            buscarClientesPorOficinaModel(lista, id);
            break;
        // Listagem de todos os clientes
        case 3:
            listarTodosClientesModel(lista);
            break;
        case 4:
            break;
        default: printf("Opção inválida!\n\n");
    }
}

// Formulário de deleção de clientes
void deletarCliente(struct ListaClientes *lista, struct ListaVeiculos *listaVeiculos) {
    int id;

    // Pede o Id do cliente que será deletada
    printf("\n=============================\n"
        "|     DELEÇÃO DE CLIENTE    |\n"
        "=============================\n");
    printf("Insira o ID do cliente que deseja deletar:");
    scanf("%d", &id);
    deletarClientesModel(lista, listaVeiculos, id);
}
