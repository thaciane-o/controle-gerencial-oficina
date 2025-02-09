#ifndef MODELPAGAMENTOCLIENTE_H
#define MODELPAGAMENTOCLIENTE_H

#include "../../models/caixas/modelCaixa.h"

struct PagamentosCliente {
    int id;
    int tipoPagamento;
    float valor;
    char dataPagamento[11];
    char dataAReceber[11];
    char dataRecebimento[11];
    int idCaixa;
    int idCliente;
    int deletado;
};

struct ListaPagamentosCliente {
    int qtdPagamentosCliente;
    struct PagamentosCliente *listaPagamentosCliente;
};

void buscarDadosPagamentosClienteModel(struct ListaPagamentosCliente *lista, int opcaoArmazenamento);

void armazenarDadosPagamentosClienteModel(struct ListaPagamentosCliente *lista, int opcaoArmazenamento);

int alocarPagamentosClienteModel(struct ListaPagamentosCliente *lista);

int realocarPagamentosClienteModel(struct ListaPagamentosCliente *lista, int qtdAlocada);

void cadastrarPagamentosClienteModel(struct ListaPagamentosCliente *lista, struct PagamentosCliente *pagamento,
                                     struct ListaCaixas *listaCaixas, int autoId);

void atualizarFormaPagamentoClienteModel(struct ListaPagamentosCliente *lista, int idPagamento,
    int tipoPagamento, char dataPagamento[11], char dataRecebimento[11], char dataAReceber[11]);

void listarPagamentosDeClienteModel(struct ListaPagamentosCliente *lista, int idCliente);

void listarTodosPagamentosClienteDeOficinaModel(struct ListaPagamentosCliente *lista, struct ListaCaixas *listaCaixas,
                                                int idOficina);

void listaPagamentosRecebidosClienteModel(struct ListaPagamentosCliente *lista, struct ListaCaixas *listaCaixas,
                                          int idOficina);

void listaPagamentosNaoRecebidosClienteModel(struct ListaPagamentosCliente *lista, struct ListaCaixas *listaCaixas,
                                             int idOficina);

int verificarClienteEmPagamentoCliente(struct ListaPagamentosCliente *lista, int idCliente, int idPagamento);

#endif //MODELPAGAMENTOCLIENTE_H
