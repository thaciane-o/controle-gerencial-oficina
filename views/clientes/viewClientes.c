#include "../../models/clientes/modelClientes.h"
#include "viewClientes.h"
#include <stdio.h>
#include <stdlib.h>


void cadastrarCliente() {
    struct clientes cliente;

    printf("\n=================================\n"
             "|     CADASTRO DE CLIENTE    |\n"
             "=================================\n");


    printf("Insira o nome do cliente: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]", &cliente.nome);

    printf("Insira o telefone do cliente: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]", &cliente.telefone);


    printf("Insira o cpf/cnpj do cliente: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]", &cliente.CPF_CNPJ);


    printf("Insira o email do cliente: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]", &cliente.email);


    printf("Insira o endereço do cliente: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]", &cliente.endereco);

    cadastrar(&cliente);
}

void listarClientes() {
    struct clientes *cliente;

    FILE *dados;
    dados = fopen("DadosClientes.bin", "rb");

    if (dados == NULL) {
        printf("Erro ao listar Clientes");
        exit(1);
    }

    printf("\n===================================\n");
    printf("|     LISTA DE CLIENTES    |\n");
    printf("===================================\n");

    while (ftell(dados) != EOF) {

        fscanf_s(dados, "%d", &cliente);
    }

    printf("===================================\n");

    fclose(dados);
    free(cliente);
}
