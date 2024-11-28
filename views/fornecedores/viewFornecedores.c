#include "../../models/fornecedores/modelFornecedores.h"
#include "viewFornecedores.h"
#include <stdio.h>
#include <stdlib.h>
#include "../../models/pecas/modelPecas.h"

void gerenciarFornecedor(struct ListaFornecedores *lista, struct ListaPecas *pecasRelacionadas,
                         int opcaoArmazenamento) {
    int opcaoSubmenus;

    if (opcaoArmazenamento != 3) {
        if (lista->qtdFornecedores == 0) {
            buscarDadosFornecedoresModel(lista, opcaoArmazenamento);
        }
        if (lista->qtdFornecedores > 0) {
            buscarDadosPecaModel(pecasRelacionadas, opcaoArmazenamento);
        }
    }

    do {
        printf("\n=================================\n"
            "|    SUBMENU DE FORNECEDORES    |\n"
            "=================================\n"
            "|  1  | Cadastrar               |\n"
            "|  2  | Atualizar               |\n"
            "|  3  | Deletar                 |\n"
            "|  4  | Listar                  |\n"
            "|  5  | Voltar                  |\n"
            "=================================\n"
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
                deletarFornecedor(lista, pecasRelacionadas);
                break;
            case 4:
                listarFornecedor(lista);
                break;
            case 5:
                if (opcaoArmazenamento != 3) {
                    if (lista->qtdFornecedores > 0) {
                        armazenarDadosFornecedoresModel(lista, opcaoArmazenamento);
                    }

                    if (pecasRelacionadas->qtdPecas > 0) {
                        free(pecasRelacionadas->listaPecas);
                        pecasRelacionadas->qtdPecas = 0;
                        pecasRelacionadas = NULL;
                    }
                }
                break;
            default: printf("\nOpção inválida!");
                break;
        };
    } while (opcaoSubmenus != 5);
}

void cadastrarFornecedor(struct ListaFornecedores *lista) {
    struct Fornecedores fornecedor;

    printf("\n=================================\n"
        "|     CADASTRO DE FORNECEDOR    |\n"
        "=================================\n");

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

void atualizarFornecedor(struct ListaFornecedores *lista) {
    int id;
    struct Fornecedores fornecedor;

    printf("\n====================================\n"
        "|     ATUALIZAÇÃO DE FORNECEDOR    |\n"
        "====================================\n"
        "Insira o fornecedor que deseja atualizar:\n");
    setbuf(stdin, NULL);
    scanf("%d", &id);

    int encontrado = verificarIDFornecedoresModel(lista, id);
    if (encontrado == 0) {
        return;
    }

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

void listarFornecedor(struct ListaFornecedores *lista) {
    int opcao, id;

    printf("\n==================================\n"
        "|     LISTAGEM DE FORNECEDOR     |\n"
        "==================================\n"
        "| 1 | Listar um único fornecedor |\n"
        "| 2 | Listar todos               |\n"
        "| 3 | Voltar                     |\n"
        "==================================\n"
        "Opção desejada: ");
    setbuf(stdin, NULL);
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            printf("Insira o ID do fornecedor que deseja listar: ");
            setbuf(stdin, NULL);
            scanf("%d", &id);
            listarFornecedoresModel(lista, id);
            break;
        case 2:
            listarTodosFornecedoresModel(lista);
            break;
        case 3:
            return;
            break;
        default: printf("Opção inválida!\n\n");
    }
}

void deletarFornecedor(struct ListaFornecedores *lista, struct ListaPecas *pecasRelacionadas) {
    int id;

    printf("\n===============================\n"
        "|    DELEÇÃO DE FORNECEDOR    |\n"
        "===============================\n");
    printf("Insira o ID do fornecedor que deseja deletar: ");
    setbuf(stdin, NULL);
    scanf("%d", &id);
    deletarFornecedoresModel(lista, pecasRelacionadas, id);
}
