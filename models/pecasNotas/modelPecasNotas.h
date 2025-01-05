//
// Created by ferna on 05/01/2025.
//

#ifndef MODELPECASNOTAS_H
#define MODELPECASNOTAS_H

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

void cadastrarPecaNotaModel(struct ListaPecasNotas *lista, struct PecasNotas *pecaNotaCadastrando);

int verificarIDPecaNotaModel(struct ListaPecasNotas *lista, int id);

void deletarPecaNotaModel(struct ListaPecasNotas *lista, int id);

#endif //MODELPECASNOTAS_H
