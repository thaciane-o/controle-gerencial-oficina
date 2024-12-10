#include "../../models/fornecedores/modelFornecedores.h"
#include "viewFornecedores.h"
#include <stdio.h>
#include <stdlib.h>
#include "../../models/pecas/modelPecas.h"

// Menu de funcionalidades de fornecedores
void gerenciarFornecedor(struct ListaFornecedores *lista, struct ListaPecas *listaPecas,
                         int opcaoArmazenamento) {
    int opcaoSubmenus;
    //Verifica se o programa esta rodando apenas em memória
    if (opcaoArmazenamento != 3) {
        // Busca os dados armazenados em arquivos
        if (lista->qtdFornecedores == 0) {
            buscarDadosFornecedoresModel(lista, opcaoArmazenamento);
        }
        // Busca os dados em arquivos das tabelas relacionadas
        if (lista->qtdFornecedores > 0) {
            buscarDadosPecaModel(listaPecas, opcaoArmazenamento);
        }
    }

    do {
        printf("\n================================\n"
            "|     MENU DE FORNECEDORES     |\n"
            "================================\n"
            "|  1  | Cadastrar              |\n"
            "|  2  | Atualizar              |\n"
            "|  3  | Deletar                |\n"
            "|  4  | Listar                 |\n"
            "|  5  | Voltar                 |\n"
            "================================\n"
            "Escolha uma opção: \n");
        scanf("%d", &opcaoSubmenus);

        switch (opcaoSubmenus) {
            case 1:
                cadastrarFornecedor(lista);
                break;
            case 2:
                atualizarFornecedor(lista);
                break;
            case 3:
                deletarFornecedor(lista, listaPecas);
                break;
            case 4:
                listarFornecedor(lista);
                break;
            case 5:
                if (opcaoArmazenamento != 3) {
                    if (lista->qtdFornecedores > 0) {
                        armazenarDadosFornecedoresModel(lista, opcaoArmazenamento);
                    }

                    if (listaPecas->qtdPecas) {
                        free(listaPecas->listaPecas);
                        listaPecas->qtdPecas = 0;
                        listaPecas->listaPecas = NULL;
                    }
                }
                break;
            default: printf("\nOpção inválida!");
                break;
        };
    } while (opcaoSubmenus != 5);
}

// Formulário de cadastro de fornecedores
void cadastrarFornecedor(struct ListaFornecedores *lista) {
    struct Fornecedores fornecedor;

    printf("\n=================================\n"
        "|     CADASTRO DE FORNECEDOR    |\n"
        "=================================\n");

    // Preenchimento dos dados
    printf("Insira o nome fantasia do fornecedor: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", fornecedor.nomeFantasia);

    printf("Insira a razão social do fornecedor: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", fornecedor.razaoSocial);

    printf("Insira a inscrição estadual do fornecedor: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", fornecedor.inscricaoEstadual);

    printf("Insira o CNPJ do fornecedor: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", fornecedor.cnpj);

    printf("Insira o endereço completo do fornecedor: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", fornecedor.endereco);

    printf("Insira o DDD do fornecedor: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", fornecedor.ddd);

    printf("Insira o telefone do fornecedor: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", fornecedor.telefone);

    printf("Insira o email do fornecedor: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", fornecedor.email);

    cadastrarFornecedoresModel(lista, &fornecedor);
}

// Formulário de atualização de fornecedores
void atualizarFornecedor(struct ListaFornecedores *lista) {
    int id;
    struct Fornecedores fornecedor;

    // Pede o Id do fornecedor que será atualizado
    printf("\n====================================\n"
        "|     ATUALIZAÇÃO DE FORNECEDOR    |\n"
        "====================================\n"
        "Insira o fornecedor que deseja atualizar:\n");
    setbuf(stdin, NULL);
    scanf("%d", &id);

    // Verifica se o ID inserido existe
    int encontrado = verificarIDFornecedoresModel(lista, id);
    if (encontrado == 0) {
        return;
    }

    //Preenchimento dos dados
    printf("Insira o nome fantasia do fornecedor: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", fornecedor.nomeFantasia);

    printf("Insira a razão social do fornecedor: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", fornecedor.razaoSocial);

    printf("Insira a inscrição estadual do fornecedor: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", fornecedor.inscricaoEstadual);

    printf("Insira o CNPJ do fornecedor: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", fornecedor.cnpj);

    printf("Insira o endereço completo do fornecedor: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", fornecedor.endereco);

    printf("Insira o DDD do fornecedor: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", fornecedor.ddd);

    printf("Insira o telefone do fornecedor: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", fornecedor.telefone);

    printf("Insira o email do fornecedor: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", fornecedor.email);

    atualizarFornecedoresModel(lista, id, &fornecedor);
}

// Listagem de fornecedores
void listarFornecedor(struct ListaFornecedores *lista) {
    int opcao, id;
    // Pergunta o tipo de listagem
    printf("\n==================================\n"
        "|     LISTAGEM DE FORNECEDOR     |\n"
        "==================================\n"
        "| 1 | Busca por ID               |\n"
        "| 2 | Listar todos               |\n"
        "| 3 | Voltar                     |\n"
        "==================================\n"
        "Opção desejada: ");
    setbuf(stdin, NULL);
    scanf("%d", &opcao);

    // Verifica a opção de listagem
    switch (opcao) {
        // Listagem de um único fornecedor
        case 1:
            printf("Insira o ID do fornecedor que deseja listar: ");
            setbuf(stdin, NULL);
            scanf("%d", &id);
            listarFornecedoresModel(lista, id);
            break;
        // Listagem de todos os fornecedores
        case 2:
            listarTodosFornecedoresModel(lista);
            break;
        case 3:
            return;
            break;
        default: printf("Opção inválida!\n\n");
    }
}

// Formulário de deleção de fornecedores
void deletarFornecedor(struct ListaFornecedores *lista, struct ListaPecas *listaPecas) {
    int id;

    // Pede o Id do fornecedor que será deletada
    printf("\n===============================\n"
        "|    DELEÇÃO DE FORNECEDOR    |\n"
        "===============================\n");
    printf("Insira o ID do fornecedor que deseja deletar: ");
    setbuf(stdin, NULL);
    scanf("%d", &id);
    deletarFornecedoresModel(lista, listaPecas, id);
}
