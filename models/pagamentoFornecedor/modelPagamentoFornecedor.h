#ifndef MODELPAGAMENTOFORNECEDOR_H
#define MODELPAGAMENTOFORNECEDOR_H

#include "../../models/caixas/modelCaixa.h"

struct PagamentosFornecedor {
    int id;
    int tipoPagamento;
    float valor;
    char dataPagamento[11];
    int idCaixa;
    int idFornecedor;
    int deletado;
};

struct ListaPagamentosFornecedor {
    int qtdPagamentosFornecedor;
    struct PagamentosFornecedor *listaPagamentosFornecedor;
};

void buscarDadosPagamentosFornecedorModel(struct ListaPagamentosFornecedor *lista, int opcaoArmazenamento);

void armazenarDadosPagamentosFornecedorModel(struct ListaPagamentosFornecedor *lista, int opcaoArmazenamento);

int alocarPagamentosFornecedorModel(struct ListaPagamentosFornecedor *lista);

int realocarPagamentosFornecedorModel(struct ListaPagamentosFornecedor *lista, int qtdAlocada);

int cadastrarPagamentosFornecedorModel(struct ListaPagamentosFornecedor *lista, struct PagamentosFornecedor *pagamento,
                                       struct ListaCaixas *listaCaixas, int autoId);

void listaPagamentosFornecedorPorOficinaModel(struct ListaPagamentosFornecedor *lista, struct ListaCaixas *listaCaixas,
                                              int idOficina);

void listaPagamentosFornecedorPorFornecedorModel(struct ListaPagamentosFornecedor *lista,
                                                 struct ListaCaixas *listaCaixas, int idFornecedor);

#endif //MODELPAGAMENTOFORNECEDOR_H
