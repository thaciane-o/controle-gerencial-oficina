#include "../models/modelFornecedores.h"
#include "viewFornecedores.h"
#include <stdio.h>
#include <stdlib.h>


void cadastrarFornecedor() {
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

    printf("Insira o telefone do fornecedor: ");
    setbuf(stdin, NULL);
    fgets(fornecedor.telefone, sizeof(fornecedor.telefone), stdin);

    printf("Insira o email do fornecedor: ");
    setbuf(stdin, NULL);
    fgets(fornecedor.email, sizeof(fornecedor.email), stdin);

    printf("Escreva o relatório a respeito desse fornecedor: ");
    setbuf(stdin, NULL);
    fgets(fornecedor.relatorio, sizeof(fornecedor.relatorio), stdin);

    cadastrar(&fornecedor);
}