
#ifndef VIEWESTOQUES_H
#define VIEWESTOQUES_H

#include "../../models/oficina/modelOficina.h"
#include "../../models/pecas/modelPecas.h"
#include "../../models/fornecedores/modelFornecedores.h"
#include "../../models/notasFiscais/modelNotasFiscais.h"
#include "../../models/pagamentoFornecedor/modelPagamentoFornecedor.h"
#include "../../models/caixas/modelCaixa.h"

void gerenciarEstoques(struct ListaPecas *listaPecas, struct ListaPecasNotas *listaPecasNotas,
                       struct ListaFornecedores *listaFornecedores,
                       struct ListaNotasFiscais *listaNotas, struct ListaOficinas *listaOficinas,
                       struct ListaPagamentosFornecedor *listaPagamentosFornecedor, struct ListaCaixas *listaCaixas,
                       int opcaoArmazenamento);

void realizarPedidoEstoque(struct ListaNotasFiscais *lista, struct ListaPecasNotas *listaPecasNotas,
                           struct ListaPecas *listaPecas, struct ListaFornecedores *listaFornecedores,
                           struct ListaOficinas *listaOficinas,
                           struct ListaPagamentosFornecedor *listaPagamentosFornecedor,
                           struct ListaCaixas *listaCaixas);

void listarNotasFiscais(struct ListaPecas *lista, struct ListaPecasNotas *listaPecasNotas,
                        struct ListaNotasFiscais *listaNotasFiscais, struct ListaFornecedores *listaFornecedores);

void deletarNotaFiscal(struct ListaNotasFiscais *lista, struct ListaPecasNotas *listaPecasNotas);

int cadastrarPagamentoFornecedorEstoque(struct ListaPagamentosFornecedor *listaPagamentosFornecedor,
                                        struct ListaCaixas *listaCaixas, float valorNota, int idFornecedor,
                                        int idOficina);


#endif //VIEWESTOQUES_H
