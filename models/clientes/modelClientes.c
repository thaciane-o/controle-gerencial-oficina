#include "modelClientes.h"
#include "C:/TrabalhoAlg2/controle-gerencial-oficina/views/clientes/viewClientes.h"
#include <stdio.h>
#include <stdlib.h>

int gerarIdUnico() {
    static int id = 0;
    return ++id;
}

void cadastrar(struct clientes *cliente) {

    FILE *dados;
    dados = fopen("DadosClientes.bin", "rb+");

    if (dados == NULL) {
        dados = fopen("DadosClientes.bin", "wb");
        if (dados == NULL) {
            printf("Erro ao cadastrar cliente\n");
            exit(1);
        }
    }

    fseek(dados, 0, SEEK_END);

    fprintf(dados, "%d\n%s%s%s%s%s", cliente->id, cliente->nome, cliente->telefone, cliente->CPF_CNPJ, cliente->email, cliente->endereco);

    printf("Cliente cadastrado com sucesso!\n");
    fclose(dados);
}