#include "../../models/fornecedores/modelFornecedores.h"
#include "viewFornecedores.h"
#include <stdio.h>

void cadastrarFornecedor(struct ListaFornecedores *lista) {
    struct Fornecedores fornecedor;

    printf("\n=================================\n"
             "|     CADASTRO DE FORNECEDOR    |\n"
             "=================================\n");

    fornecedor.id = gerarIdUnico();

    printf("Insira o nome fantasia do fornecedor: ");
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

    printf("\n=================================\n"
          "|     ATUALIZAÇÃO DE FORNECEDOR    |\n"
          "=================================\n"
          "Insira o fornecedor que deseja atualizar: ");
    scanf("%d", &id);
    fornecedor = atualizarFornecedoresModel(lista, id);

    printf("Insira o nome fantasia do fornecedor: ");
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
}

void listarFornecedor(struct ListaFornecedores *lista) {
    int opcao, id;

    printf("\n=================================\n"
            "|     LISTAGEM DE FORNECEDOR    |\n"
            "=================================\n"
            "1. Listar um único fornecedor"
            "\n2. Listar todos\n");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            printf("Insira o fornecedor que deseja lista: ");
            scanf("%d", &id);
            listarFornecedoresModel(lista, id);
            break;
        case 2:
            listarTodosFornecedoresModel(lista);
            break;
        default: printf("Opção inválida!\n\n");
    }

}

void deletarFornecedor(struct ListaFornecedores *lista) {
    int id;

    printf("\n=================================\n"
             "|     DELEÇÃO DE FORNECEDOR    |\n"
             "=================================\n");
    printf("Insira o fornecedor que deseja deletar:");
    scanf("%d", &id);
    deletarFornecedoresModel(lista, id);
}