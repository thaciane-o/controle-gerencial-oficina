//
// Created by ferna on 24/12/2024.
//

#ifndef VIEWESTOQUES_H
#define VIEWESTOQUES_H

void gerenciarEstoques(struct ListaPecas *lista, struct ListaFornecedores *listaFornecedores, struct ListaNotasFiscais *listaNotas, int opcaoArmazenamento);

void realizarPedidoEstoque(struct ListaPecas *lista, struct ListaFornecedores *listaFornecedores, struct ListaNotasFiscais *listaNotas);



#endif //VIEWESTOQUES_H
