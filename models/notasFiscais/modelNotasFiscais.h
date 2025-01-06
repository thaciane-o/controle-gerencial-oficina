
#ifndef MODELNOTASFISCAIS_H
#define MODELNOTASFISCAIS_H

#include "modelNotasFiscais.h"
#include "../../models/pecasNotas/modelPecasNotas.h"
#include "../../models/pecas/modelPecas.h"
#include "../../models/fornecedores/modelFornecedores.h"
#include "../../models/oficina/modelOficina.h"

struct NotasFiscais {
    int id;
    float frete;
    float imposto;
    float totalNota;
    int idOficina;
    int idFornecedor;
    int deletado;
};

struct ListaNotasFiscais {
    int qtdNotas;
    struct NotasFiscais *listaNotas;
};

void buscarDadosNotasFiscaisModel(struct ListaNotasFiscais *lista,  int opcaoArmazenamento);

void armazenarDadosNotasFiscaisModel(struct ListaNotasFiscais *lista, int opcaoArmazenamento);

int alocarMemoriaNotasFiscaisModel(struct ListaNotasFiscais *lista);

int realocarMemoriaNotasFiscaisModel(struct ListaNotasFiscais *lista, int qtdAloca);

void cadastrarNotasFiscaisModel(struct ListaNotasFiscais *lista, struct NotasFiscais *novaNotaFiscal,
                                struct ListaPecas *listaPecas, struct ListaOficinas *listaOficinas,
                                struct ListaPecasNotas *listaPecasNotas, int totalPecas);


void listarTodasNotasFiscaisModel(struct ListaNotasFiscais *lista, struct ListaPecasNotas *listaPecasNotas,
                                  struct ListaPecas *listaPecas,
                                  struct ListaFornecedores *listaFornecedores);

void listarNotaFiscalModel(struct ListaNotasFiscais *lista, struct ListaPecasNotas *listaPecasNotas,
                           struct ListaPecas *listaPecas,
                           struct ListaFornecedores *listaFornecedores, int id);

void buscarNotasFiscaisPorFornecedorModel(struct ListaNotasFiscais *lista, struct ListaPecasNotas *listaPecasNotas,
                                          struct ListaPecas *listaPecas,
                                          struct ListaFornecedores *listaFornecedores, int idFornecedor);

void deletarNotaModel(struct ListaNotasFiscais *lista, struct ListaPecasNotas *listaPecasNotas, int id);

int verificarRelacaoFornecedorModel(struct ListaPecas *listaPecas,
                                    struct NotasFiscais *notaFiscal, int idPeca);




#endif //MODELNOTASFISCAIS_H
