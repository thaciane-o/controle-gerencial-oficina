#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "modelEstoques.h"
#include "../../models/oficina/modelOficina.h"
#include "..\..\models\pecas\modelPecas.h"
#include "..\..\models\fornecedores\modelFornecedores.h"
#include "..\..\models\notasFiscais\modelNotasFiscais.h"

void verificarEstoqueMinimo(struct ListaPecas *lista) {
    for (int i = 0; i < lista->qtdPecas; i++) {
        if (lista->listaPecas[i].qtdEstoque < lista->listaPecas[i].estoqueMinimo) {
            printf("\nESTOQUE ABAIXO DO MÍNIMO NA PEÇA: %d\n"
                   "FORNECEDOR: %d\n\n", lista->listaPecas[i].id, lista->listaPecas[i].idFornecedor);
        }
    }
}


char *ordenarListaPecas(struct ListaNotasFiscais *lista, int tamLista, int posicaoLista, int tipo) {
    char *token;
    token = malloc(sizeof (int) * tamLista);

    for (int i = 0; i < tamLista; i++) {
        char aux[sizeof(int)*2];
        if (tipo == 0) {
            if (i==0) {
                sprintf(aux, "%d", lista->listaNotas[posicaoLista].idPecas[i]);
                strcpy(token, aux);
                strcat(token, ",");
            } else {
                sprintf(aux, "%d", lista->listaNotas[posicaoLista].idPecas[i]);
                strcat(token, aux);
                strcat(token, ",");
            }
        }
        if (tipo == 1) {
            if (i==0) {
                sprintf(aux, "%d", lista->listaNotas[posicaoLista].qtdPecas[i]);
                strcpy(token, aux);
                strcat(token, ",");
            } else {
                sprintf(aux, "%d", lista->listaNotas[posicaoLista].qtdPecas[i]);
                strcat(token, aux);
                strcat(token, ",");
            }
        }
    }
    return token;
}

