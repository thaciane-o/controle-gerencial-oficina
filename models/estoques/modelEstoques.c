#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "modelEstoques.h"
#include "..\..\models\pecas\modelPecas.h"
#include "..\..\models\fornecedores\modelFornecedores.h"
#include "..\..\models\notasFiscais\modelNotasFiscais.h"

void verificarEstoqueMinimo(struct ListaPecas *lista) {
    for (int i = 0; i < lista->qtdPecas; i++) {
        if (lista->listaPecas[i].qtdEstoque < lista->listaPecas[i].estoqueMinimo) {
            printf("\nESTOQUE ABAIXO DO MÍNIMO NA PEÇA: %d");
        }
    }
}

// void listarEstoquesModel(struct Pecas *lista) {
//
//
// }