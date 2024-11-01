#include "C:/TrabalhoAlg2/controle-gerencial-oficina/models/clientes/modelClientes.h"
#include "viewClientes.h"
#include <stdio.h>
#include <stdlib.h>


void cadastrarCliente() {
    struct clientes cliente;

    printf("\n=================================\n"
             "|     CADASTRO DE CLIENTE    |\n"
             "=================================\n");

    cliente.id = gerarIdUnico();

    printf("Insira o nome do cliente: ");
    setbuf(stdin, NULL);
    fgets(cliente.nome, sizeof(cliente.nome), stdin);

    printf("Insira o telefone do cliente: ");
    scanf("%d", &cliente.telefone);

    printf("Insira o cpf/cnpj do cliente: ");
    scanf("%d", &cliente.CPF_CNPJ);

    printf("Insira o email do cliente: ");
    setbuf(stdin, NULL);
    fgets(cliente.email, sizeof(cliente.email), stdin);

    printf("Insira o endereço do cliente: ");
    setbuf(stdin, NULL);
    fgets(cliente.endereco, sizeof(cliente.endereco), stdin);

    cadastrar(&cliente);
}
