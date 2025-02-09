#ifndef MODELPECASNOTAS_H
#define MODELPECASNOTAS_H

#include "../../models/pecas/modelPecas.h"
#include "../../models/notasFiscais/modelNotasFiscais.h"

struct PecasNotas {
    int id;
    int idNota;
    int idPeca;
    int qtdPecas;
    int deletado;
};

struct ListaPecasNotas {
    int qtdPecasNotas;
    struct PecasNotas *listaPecasNotas;
};

void buscarDadosPecaNotaModel(struct ListaPecasNotas *lista, int opcaoArmazenamento);

void armazenarDadosPecaNotaModel(struct ListaPecasNotas *lista, int opcaoArmazenamento);

int alocarMemoriaPecaNotaModel(struct ListaPecasNotas *lista);

int realocarMemoriaPecaNotaModel(struct ListaPecasNotas *lista, int qtdAloca);

void cadastrarPecaNotaModel(struct ListaPecasNotas *lista, struct PecasNotas *pecaNotaCadastrando, int autoId);

void deletarPecaNotaModel(struct ListaPecasNotas *lista, int id);

void cadastrarNovaPecaModel(struct ListaPecas *listaPecas, struct NotasFiscais *notaFiscal,
                            struct PecasNotas *pecaNota);

#endif //MODELPECASNOTAS_H
