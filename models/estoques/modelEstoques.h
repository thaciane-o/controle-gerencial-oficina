//
// Created by ferna on 24/12/2024.
//

#ifndef MODELESTOQUES_H
#define MODELESTOQUES_H

struct Estoques {
    int id;
    int idPecas;
    int idFornecedor;
    int deletado;
};

struct ListaEstoques {
    int qtdEstoques;
    struct Estoques *listaEstoques;
};

void buscarDadosEstoquesModel(struct ListaEstoques *lista, int opcaoArmazenamento);

void armazenarDadosEstoquesModel(struct ListaEstoques *lista, int opcaoArmazenamento);

#endif //MODELESTOQUES_H
