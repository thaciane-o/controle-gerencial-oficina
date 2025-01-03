//
// Created by ferna on 24/12/2024.
//

#ifndef VIEWESTOQUES_H
#define VIEWESTOQUES_H

#include "../../models/oficina/modelOficina.h"
#include "..\..\models\pecas\modelPecas.h"
#include "..\..\models\fornecedores\modelFornecedores.h"
#include "..\..\models\notasFiscais\modelNotasFiscais.h"

void gerenciarEstoques(struct ListaPecas *lista, struct ListaFornecedores *listaFornecedores,
                       struct ListaNotasFiscais *listaNotas, struct ListaOficinas *listaOficinas, int opcaoArmazenamento);

void realizarPedidoEstoque(struct ListaNotasFiscais *lista, struct ListaPecas *listaPecas, struct ListaFornecedores *listaFornecedores, struct ListaOficinas *listaOficinas);


void listarNotasFiscais(struct ListaPecas *lista, struct ListaNotasFiscais *listaNotasFiscais, struct ListaFornecedores *listaFornecedores);

#endif //VIEWESTOQUES_H
