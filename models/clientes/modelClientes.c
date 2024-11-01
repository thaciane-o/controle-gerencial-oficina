#include "modelClientes.h"
#include "C:/TrabalhoAlg2/controle-gerencial-oficina/views/clientes/viewClientes.h"
#include <stdio.h>
#include <stdlib.h>

int gerarIdUnico() {
    static int id = 0;
    return ++id;
}

void cadastrar(struct clientes *cliente) {
    cliente->id = (int) malloc(sizeof(int));

    if (!cliente->id) {
        printf("Erro ao cadastrar fornecedor");
        exit(1);
    }

    cliente->id = gerarIdUnico();

    printf("Cliente cadastrado com sucesso!\n");
    printf("%d \n%s \n%d \n%d \n%s \n%s", cliente->id, cliente->nome, cliente->telefone, cliente->CPF_CNPJ, cliente->email, cliente->endereco);
    free(cliente);
}