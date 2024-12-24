#include "viewOficina.h"
#include "../../models/oficina/modelOficina.h"
#include "../../models/funcionarios/modelFuncionarios.h"
#include "../../models/servicos/modelServicos.h"
#include "../../models/clientes/modelClientes.h"
#include "../../models/caixas/modelCaixa.h"
#include <stdio.h>
#include <stdlib.h>

// Menu de funcionalidades de oficinas
void gerenciarOficina(struct ListaOficinas *lista, struct ListaFuncionarios *listaFuncionarios,
                      struct ListaServicos *listaServicos, struct ListaClientes *listaClientes,
                      struct ListaCaixas *listaCaixas, int opcaoArmazenamento) {
    int opcaoSubmenus = 0;
    //Verifica se o programa esta rodando apenas em memória
    if (opcaoArmazenamento != 3) {
        // Busca os dados armazenados em arquivos
        if (lista->qtdOficinas == 0) {
            buscarDadosOficinaModel(lista, opcaoArmazenamento);
        }
        // Busca os dados em arquivos das tabelas relacionadas
        if (lista->qtdOficinas > 0) {
            buscarDadosFuncionariosModel(listaFuncionarios, opcaoArmazenamento);
            buscarDadosClientesModel(listaClientes, opcaoArmazenamento);
            buscarDadosServicoModel(listaServicos, opcaoArmazenamento);
            buscarDadosCaixasModel(listaCaixas, opcaoArmazenamento);
        }
    }

    while (opcaoSubmenus != 5) {
        printf("\n================================\n"
            "|       MENU DE OFICINAS       |\n"
            "================================\n"
            "|  1  | Cadastrar              |\n"
            "|  2  | Atualizar              |\n"
            "|  3  | Deletar                |\n"
            "|  4  | Listar                 |\n"
            "|  5  | Voltar                 |\n"
            "================================\n"
            "Escolha uma opção: ");
        scanf("%d", &opcaoSubmenus);

        switch (opcaoSubmenus) {
            case 1:
                cadastrarOficina(lista, listaCaixas);
                break;
            case 2:
                atualizarOficina(lista);
                break;
            case 3:
                deletarOficina(lista, listaFuncionarios, listaServicos, listaClientes, listaCaixas);
                break;
            case 4:
                listarOficina(lista);
                break;
            case 5:
                if (opcaoArmazenamento != 3) {
                    if (lista->qtdOficinas) {
                        armazenarDadosOficinaModel(lista, opcaoArmazenamento);
                    }
                    if (listaFuncionarios->qtdFuncionarios) {
                        free(listaFuncionarios->listaFuncionarios);
                        listaFuncionarios->listaFuncionarios = NULL;
                        listaFuncionarios->qtdFuncionarios = 0;
                    }
                    if (listaClientes->qtdClientes) {
                        free(listaClientes->listaClientes);
                        listaClientes->listaClientes = NULL;
                        listaClientes->qtdClientes = 0;
                    }
                    if (listaServicos->qtdServicos) {
                        free(listaServicos->listaServicos);
                        listaServicos->listaServicos = NULL;
                        listaServicos->qtdServicos = 0;
                    }

                    // Armazena os caixas
                    if (listaCaixas->qtdCaixas) {
                        armazenarDadosCaixasModel(listaCaixas, opcaoArmazenamento);
                        free(listaCaixas->listaCaixas);
                        listaCaixas->listaCaixas = NULL;
                        listaCaixas->qtdCaixas = 0;
                    }
                }
                break;
            default: printf("Opção inválida!\n\n");
                break;
        }
    }
}

// Formulário de cadastro de oficinas
void cadastrarOficina(struct ListaOficinas *lista, struct ListaCaixas *listaCaixas) {
    struct Oficinas oficinaCadastrando;

    printf("\n===============================\n"
        "|     CADASTRO DE OFICINA     |\n"
        "===============================\n");

    // Preenchimento dos dados
    printf("Insira o nome da oficina: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]s", oficinaCadastrando.nome);

    printf("Insira o endereço da oficina: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]s", oficinaCadastrando.endereco);

    printf("Insira o DDD do telefone da oficina: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]s", oficinaCadastrando.ddd);

    printf("Insira o telefone da oficina: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]s", oficinaCadastrando.telefone);

    printf("Insira o email da oficina: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]s", oficinaCadastrando.email);

    printf("Insira a porcentagem de lucro: %");
    setbuf(stdin, NULL);
    scanf("%f", &oficinaCadastrando.porcentagemLucro);

    cadastrarOficinaModel(lista, &oficinaCadastrando, listaCaixas);
}

// Formulário de atualização de oficinas
void atualizarOficina(struct ListaOficinas *lista) {
    struct Oficinas oficinaAtualizando;
    int id;
    // Pede o Id da oficina que será atualizada
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

    //Preenchimento dos dados
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

    printf("Insira a porcentagem de lucro: %");
    setbuf(stdin, NULL);
    scanf("%f", &oficinaAtualizando.porcentagemLucro);

    atualizarOficinaModel(lista, id, &oficinaAtualizando);
}

// Listagem de oficinas
void listarOficina(struct ListaOficinas *lista) {
    int resp;
    // Pergunta o tipo de listagem
    printf("\n===============================\n"
        "|     LISTAGEM DE OFICINA     |\n"
        "===============================\n"
        "| 1 | Busca por ID            |\n"
        "| 2 | Listar todos            |\n"
        "| 3 | Voltar                  |\n"
        "===============================\n"
        "Opção desejada: ");
    setbuf(stdin, NULL);
    scanf("%d", &resp);

    // Verifica a opção de listagem
    int id = 0;
    switch (resp) {
        // Listagem de uma única Oficina
        case 1:
            printf("Insira o ID desejado para a busca: ");
            setbuf(stdin, NULL);
            scanf("%d", &id);
            listarOficinaModel(lista, id);
            break;
        // Listagem de todas as Oficinas
        case 2:
            listarTodosOficinaModel(lista);
            break;
        case 3:
            break;
        default:
            printf("Opção inválida, voltando ao menu principal.\n\n");
            break;
    }
}

// Formulário de deleção de oficinas
void deletarOficina(struct ListaOficinas *lista, struct ListaFuncionarios *listaFuncionarios,
                    struct ListaServicos *listaServicos, struct ListaClientes *listaClientes,
                    struct ListaCaixas *listaCaixas) {
    int id;
    // Pede o Id da oficina que será deletada
    printf("\n==============================\n"
        "|     DELEÇÃO DE OFICINA     |\n"
        "==============================\n");

    printf("Insira o ID da oficina que deseja deletar: ");
    setbuf(stdin, NULL);
    scanf("%d", &id);

    deletarOficinaModel(lista, listaFuncionarios, listaServicos, listaClientes, id);
}
