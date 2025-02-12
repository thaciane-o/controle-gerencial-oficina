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
    int idOficina;
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

void cadastrarPecaModel(struct ListaPecas *lista, struct Pecas *pecaCadastrando, int autoId);

void deletarPecaModel(struct ListaPecas *lista, int id, struct ListaOrdensServico *listaOrdensServico);

void atualizarPecaModel(struct ListaPecas *lista, int id, struct Pecas *pecaAlterando);

int verificarIDPecaModel(struct ListaPecas *lista, int id);

void listarTodosPecaModel(struct ListaPecas *lista);

void listarPecaModel(struct ListaPecas *lista, int id);

void buscarPecasPorFornecedorModel(struct ListaPecas *lista, int idFornecedor);

float getValorPecaPorIdModel(struct ListaPecas *lista, int id);

int getIndiceVetorPorIdPecaModel(struct ListaPecas *listaPecas, int id);

int debitarPecaEstoqueModel(struct ListaPecas *listaPecas, int idPeca, int qtdPecasRequisitadas);

void verificarEstoqueMinimo(struct ListaPecas *lista);

int verificarRelacaoPecaComFornecedorModel(struct ListaPecas *listaPecas,
                                    int idFornecedor, int idPeca);

int verificarRelacaoPecaComOficinaModel(struct ListaPecas *listaPecas,
                                 int idOficina, int idPeca);

int getQtdEstoquePecaModel(struct ListaPecas *lista, int id);

int getQtdEstoqueMinimoPecaModel(struct ListaPecas *lista, int id);

#endif //MODELPECAS_H
