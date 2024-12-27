#ifndef MODELPAGAMENTOFORNECEDOR_H
#define MODELPAGAMENTOFORNECEDOR_H

#include "../caixas/modelCaixa.h"

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


#endif //MODELPAGAMENTOFORNECEDOR_H