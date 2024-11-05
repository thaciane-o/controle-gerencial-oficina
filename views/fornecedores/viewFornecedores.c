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
    setbuf(stdin, NULL);
    fgets(fornecedor.nomeFantasia, sizeof(fornecedor.nomeFantasia), stdin);

    printf("Insira a razão social do fornecedor: ");
    setbuf(stdin, NULL);
    fgets(fornecedor.razaoSocial, sizeof(fornecedor.razaoSocial), stdin);

    printf("Insira a inscrição estadual do fornecedor: ");
    setbuf(stdin, NULL);
    fgets(fornecedor.inscricaoEstadual, sizeof(fornecedor.inscricaoEstadual), stdin);

    printf("Insira o CNPJ do fornecedor: ");
    setbuf(stdin, NULL);
    fgets(fornecedor.cnpj, sizeof(fornecedor.cnpj), stdin);

    printf("Insira o endereço do fornecedor: ");
    setbuf(stdin, NULL);
    fgets(fornecedor.endereco, sizeof(fornecedor.endereco), stdin);

    printf("Insira o DDD do fornecedor: ");
    setbuf(stdin, NULL);
    fgets(fornecedor.ddd, sizeof(fornecedor.ddd), stdin);

    printf("Insira o telefone do fornecedor: ");
    setbuf(stdin, NULL);
    fgets(fornecedor.telefone, sizeof(fornecedor.telefone), stdin);

    printf("Insira o email do fornecedor: ");
    setbuf(stdin, NULL);
    fgets(fornecedor.email, sizeof(fornecedor.email), stdin);

    cadastrarFornecedoresModel(lista, &fornecedor);
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