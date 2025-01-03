
#ifndef MODELNOTASFISCAIS_H
#define MODELNOTASFISCAIS_H

#include "modelNotasFiscais.h"
#include "..\..\models\estoques\modelEstoques.h"
#include "..\..\models\pecas\modelPecas.h"
#include "..\..\models\fornecedores\modelFornecedores.h"
#include "..\..\models\oficina\modelOficina.h"

struct notasFiscais {
    int id;
    int *idPecas;
    int *qtdPecas;
    float frete;
    float imposto;
    float precoVendaTotal;
    int tamListaPecas;
    int idOficina;
    int idFornecedor;
    int deletado;
};

struct ListaNotasFiscais {
    int qtdNotas;
    struct notasFiscais *listaNotas;
};

void buscarDadosNotasFiscaisModel(struct ListaNotasFiscais *lista, struct ListaPecas *listaPecas,  int opcaoArmazenamento);

void armazenarDadosNotasFiscaisModel(struct ListaNotasFiscais *lista, int opcaoArmazenamento);

int alocarMemoriaNotasFiscaisModel(struct ListaNotasFiscais *lista, int qtdPecas);

int realocarMemoriaNotasFiscaisModel(struct ListaNotasFiscais *lista, int qtdAloca, int qtdPecas);

void cadastrarNotasFiscaisModel(struct ListaNotasFiscais *lista, struct notasFiscais *novaNotaFiscal,
                                struct ListaPecas *listaPecas, struct ListaOficinas *listaOficinas, int qtdPecas);

    int verificarRelacaoFornecedorModel(struct ListaPecas *listaPecas, struct ListaFornecedores *listaFornecedores,
                                        struct notasFiscais *notaFiscal, int idPeca);

    void listarTodasNotasFiscaisModel(struct ListaNotasFiscais *lista, struct ListaPecas *listaPecas,
                                      struct ListaFornecedores *listaFornecedores);

    void listarNotaFiscalModel(struct ListaNotasFiscais *lista, struct ListaPecas *listaPecas,
                               struct ListaFornecedores *listaFornecedores, int id);

    void buscarNotasFiscaisPorFornecedorModel(struct ListaNotasFiscais *lista, struct ListaPecas *listaPecas,
                                              struct ListaFornecedores *listaFornecedores, int idFornecedor);

#endif //MODELNOTASFISCAIS_H
