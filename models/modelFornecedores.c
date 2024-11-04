#include "modelFornecedores.h"
#include "../views/viewFornecedores.h"
#include <stdio.h>
#include <stdlib.h>

int gerarIdUnico() {
    static int id = 0;
    return ++id;
}

void cadastrar(struct Fornecedores *fornecedor) {
    fornecedor->id = (int) malloc(sizeof(int));

    if (!fornecedor->id) {
        printf("Erro ao cadastrar fornecedor.");
        exit(1);
    }

    fornecedor->id = gerarIdUnico();

    printf("Fornecedor cadastrado com sucesso!\n");
    free(fornecedor);
}