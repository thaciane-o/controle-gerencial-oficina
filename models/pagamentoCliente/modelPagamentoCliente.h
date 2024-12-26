#ifndef MODELPAGAMENTOCLIENTE_H
#define MODELPAGAMENTOCLIENTE_H

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

void cadastrarPagamentosClienteModel(struct ListaPagamentosCliente *lista, struct PagamentosCliente *pagamento);



#endif //MODELPAGAMENTOCLIENTE_H