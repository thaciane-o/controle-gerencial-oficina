#include "viewOficina.h"
#include "../../models/oficina/modelOficina.h"
#include <stdio.h>
#include <stdlib.h>

// Menu de funcionalidades para oficina
void gerenciarOficina(struct ListaOficinas *lista, int opcaoArmazenamento) {
    int opcaoSubmenus = 0;

    if (lista->qtdOficinas == 0 && opcaoArmazenamento != 3) {
        buscarDadosOficinaModel(lista, opcaoArmazenamento);
    }

    while (opcaoSubmenus != 5) {
        printf("\n=================================\n"
            "|      SUBMENU DE OFICINAS      |\n"
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
                cadastrarOficina(lista);
                break;
            case 2:
                atualizarOficina(lista);
                break;
            case 3:
                deletarOficina(lista);
                break;
            case 4:
                listarOficina(lista);
                break;
            case 5:
                if (opcaoArmazenamento != 3) {
                    armazenarDadosOficinaModel(lista, opcaoArmazenamento);
                }
                break;
            default: printf("Opção inválida!\n");
                break;
        }
    }
}

// Formulário de cadastro de oficinas
void cadastrarOficina(struct ListaOficinas *lista) {
    struct Oficinas oficinaCadastrando;

    printf("\n===============================\n"
        "|     CADASTRO DE OFICINA     |\n"
        "===============================\n");

    printf("Insira o nome da oficina: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]s", oficinaCadastrando.nome);

    printf("Insira o endereço da oficina: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]s", oficinaCadastrando.endereco);

    printf("Insira o DDD do telefone da oficina: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]s", &oficinaCadastrando.ddd);

    printf("Insira o telefone da oficina: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]s", &oficinaCadastrando.telefone);

    printf("Insira o email da oficina: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]s", oficinaCadastrando.email);

    cadastrarOficinaModel(lista, &oficinaCadastrando);
}

// Formulário de atualização de oficinas
void atualizarOficina(struct ListaOficinas *lista) {
    struct Oficinas oficinaAtualizando;
    int id;

    printf("\n==================================\n"
        "|     ATUALIZAÇÃO DE OFICINA     |\n"
        "==================================\n");

    printf("Insira o ID da oficina que deseja alterar: ");
    setbuf(stdin, NULL);
    scanf("%d", &id);

    // Verifica se o ID inserido existe
    int encontrado = verificarIDOficinaModel(lista, id);
    if (encontrado == 0) {
        return;
    }

    printf("Insira o nome da oficina: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]s", oficinaAtualizando.nome);

    printf("Insira o endereço da oficina: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]s", oficinaAtualizando.endereco);

    printf("Insira o DDD do telefone da oficina: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]s", oficinaAtualizando.ddd);

    printf("Insira o telefone da oficina: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]s", oficinaAtualizando.telefone);

    printf("Insira o email da oficina: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]s", oficinaAtualizando.email);

    atualizarOficinaModel(lista, id, &oficinaAtualizando);
}

// Formulário de deleção de oficina
void deletarOficina(struct ListaOficinas *lista) {
    int id;

    printf("\n==============================\n"
        "|     DELEÇÃO DE OFICINA     |\n"
        "==============================\n");

    printf("Insira o ID da oficina que deseja deletar: ");
    setbuf(stdin, NULL);
    scanf("%d", &id);

    deletarOficinaModel(lista, id);
}

// Listagem de oficinas
void listarOficina(struct ListaOficinas *lista) {
    // Pergunta se deseja listar todos, ou buscar por id
    int resp;
    printf("==================\n"
        "| 1 | Busca por ID\n"
        "| 2 | Listar todos\n"
        "| 3 | Voltar\n"
        "==================\n"
        "Opção desejada: ");
    setbuf(stdin, NULL);
    scanf("%d", &resp);

    // Verifica a opção de listagem
    int id = 0;
    switch (resp) {
        case 1:
            printf("Insira o ID desejado para a busca: ");
            setbuf(stdin, NULL);
            scanf("%d", &id);
            buscarIdOficinaModel(lista, id);
            break;
        case 2:
            listarTodosOficinaModel(lista);
            break;
        case 3:
            break;
        default:
            printf("Opção inválida, voltando ao menu principal.\n");
            break;
    }
}
