#ifndef MODELVEICULOS_H
#define MODELVEICULOS_H

#include "../../models/agendamentos/modelAgendamentos.h"

struct Veiculos {
    int id;
    int idProprietario;
    char modelo[255];
    char marca[255];
    char chassi[18];
    char placa[8];
    int anoFabricacao;
    int deletado;
};

struct ListaVeiculos {
    int qtdVeiculos;
    struct Veiculos *listaVeiculos;
};

void buscarDadosVeiculosModel(struct ListaVeiculos *lista, int opcaoArmazenamento);

void armazenarDadosVeiculosModel(struct ListaVeiculos *lista, int opcaoArmazenamento);

int alocarVeiculosModel(struct ListaVeiculos *lista);

int realocarVeiculosModel(struct ListaVeiculos *lista, int qtdAlocada);

void cadastrarVeiculosModel(struct ListaVeiculos *lista, struct Veiculos *veiculo, int autoId);

void deletarVeiculosModel(struct ListaVeiculos *lista, struct ListaAgendamentos *listaAgendamentos, int id);

void atualizarVeiculosModel(struct ListaVeiculos *lista, int id, struct Veiculos *veiculo);

int verificarIDVeiculoModel(struct ListaVeiculos *lista, int id);

void listarTodosVeiculosModel(struct ListaVeiculos *lista);

void listarVeiculoModel(struct ListaVeiculos *lista, int id);

void buscarVeiculosPorClienteModel(struct ListaVeiculos *lista, int idCliente);

int getIdClientePorVeiculoModel(struct ListaVeiculos *lista, int idVeiculo);

int verificarRelacaoVeiculoComClienteModel(struct ListaVeiculos *listaVeiculos,
                                 int idCliente, int idVeiculo);

#endif //MODELVEICULOS_H
