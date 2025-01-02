#ifndef MODELPECAS_H
#define MODELPECAS_H
#include "../../models/ordensServico/modelOrdensServico.h"

struct Pecas {
    int id;
    char descricao[255];
    char fabricante[255];
    float precoCusto;
    float precoVenda;
    int qtdEstoque;
    int estoqueMinimo;
    int idFornecedor;
    int deletado;
};

struct ListaPecas {
    int qtdPecas;
    struct Pecas *listaPecas;
};

void buscarDadosPecaModel(struct ListaPecas *lista, int opcaoArmazenamento);

void armazenarDadosPecaModel(struct ListaPecas *lista, int opcaoArmazenamento);

int alocarMemoriaPecaModel(struct ListaPecas *lista);

int realocarMemoriaPecaModel(struct ListaPecas *lista, int qtdAloca);

void cadastrarPecaModel(struct ListaPecas *lista, struct Pecas *pecaCadastrando);

void deletarPecaModel(struct ListaPecas *lista, int id, struct ListaOrdensServico *listaOrdensServico);

void atualizarPecaModel(struct ListaPecas *lista, int id, struct Pecas *pecaAlterando);

int verificarIDPecaModel(struct ListaPecas *lista, int id);

void listarTodosPecaModel(struct ListaPecas *lista);

void listarPecaModel(struct ListaPecas *lista, int id);

void buscarPecasPorFornecedorModel(struct ListaPecas *lista, int idFornecedor);

#endif //MODELPECAS_H
