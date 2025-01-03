//
// Created by ferna on 24/12/2024.
//

#ifndef MODELESTOQUES_H
#define MODELESTOQUES_H

#include "..\..\models\estoques\modelEstoques.h"
#include "..\..\models\pecas\modelPecas.h"
#include "..\..\models\notasFiscais\modelNotasFiscais.h"

void verificarEstoqueMinimo(struct ListaPecas *lista);

char *ordenarListaPecas(struct ListaNotasFiscais *lista, int tamLista, int posicaoLista, int tipo);

#endif //MODELESTOQUES_H
